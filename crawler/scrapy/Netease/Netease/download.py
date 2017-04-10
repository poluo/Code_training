from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import logging as log
from bs4 import BeautifulSoup
from scrapy.http import HtmlResponse
from .config.proxy_netease import Proxy
from .config.config import HEADER


class CustomNormalMiddleware(object):
    def __init__(self):
        self.proxy_spider = Proxy()
        self.proxies_list = []
        self.proxy = None
        self.count = 0
        # every 20 times change a proxy
        self.threshold = 20

    def process_request(self, request, spider):
        if self.use_proxy(request.url):
            request.meta['proxy'] = "http://{0}:{1}".format(self.proxy['ip'], self.proxy['port'])
            request = request.replace(url=request.url[:request.url.find('proxy')])
            return request
        else:
            return None

    def update_proxy(self):
        self.count += 1
        if self.count > 20:
            self.update_proxy()
            self.count = 0
        if len(self.proxies_list) < 1:
            self.proxies_list = self.proxy_spider.get_proxy()
            log.info('update proxy')
        self.proxy = self.proxies_list.pop()

    def use_proxy(self, url):
        if 'proxy' in url:
            self.update_proxy()
            return True
        else:
            return False


class CustomsSleniumMiddleware(object):
    def __init__(self):
        # Do not load images
        self.proxy_spider = Proxy()
        self.proxy_list = []
        self.update_proxy()
        self.count = 0
        cap = webdriver.DesiredCapabilities.PHANTOMJS
        cap["phantomjs.page.settings.loadImages"] = False
        self.driver = webdriver.PhantomJS(desired_capabilities=cap)
        self.driver.set_page_load_timeout(5)

    def update_driver(self):
        if len(self.proxy_list) == 0:
            self.update_proxy()
        proxy = self.proxy_list.pop()
        service_args = [
            '--proxy={0}:{1}'.format(proxy['ip'], proxy['port']),
            '--proxy-type={0}'.format(proxy['type']),
        ]
        for key, value in enumerate(HEADER):
            webdriver.DesiredCapabilities.PHANTOMJS['phantomjs.page.customHeaders.{}'.format(key)] = value
        cap = webdriver.DesiredCapabilities.PHANTOMJS
        cap["phantomjs.page.settings.loadImages"] = False
        self.driver = webdriver.PhantomJS(desired_capabilities=cap, service_args=service_args)
        self.driver.set_page_load_timeout(5)
        log.info('update driver, left {0} avaliable'.format(len(self.proxy_list)))

    def update_proxy(self):
        self.proxy_list = self.proxy_spider.get_proxy()
        log.info('update proxy')

    def process_request(self, request, spider):
        if self.use_selenium(request.url):
            self.count += 1
            if self.count > 20:
                self.update_driver()
                self.count = 0
                log.info('update driver')
            return HtmlResponse(request.url, encoding='utf-8', body=self.driver.page_source.encode('utf8'))

    def use_selenium(self, url):
        # only for netease music
        if 'ajax' in url:
            url = url[:url.find('ajax')]
            log.debug('use slenium')
            count = 0
            while True:
                try:
                    count += 1
                    self.driver.get(url)
                    # self.logger.info(self.driver.title)
                    self.driver.switch_to.frame("g_iframe")
                    WebDriverWait(self.driver, 5).until(
                        EC.presence_of_element_located(
                            (By.CSS_SELECTOR, "#song-list-pre-cache > div > div > table > tbody > tr"))
                    )
                except Exception as e:
                    self.update_driver()
                    log.info("selenium serious error happened {0}".format(e))
                else:
                    if self.source_code_ok():
                        return True
                    else:
                        return False
                finally:
                    if count >= 3:
                        log.info('selenium try three time,not again')
                        return None
        else:
            return False

    def use_proxy(self, url):
        if 'proxy' in url:
            pass

    def source_code_ok(self):
        count = 0
        while 1:
            count += 1
            try:
                web = self.driver.page_source
            except Exception as e:
                log.info("web page source error {0}".format(e))
            soup = BeautifulSoup(web, 'lxml')
            element = soup.select("#song-list-pre-cache > div > div > table > tbody > tr")
            if len(element):
                return True
            if count > 10:
                return False
