from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import logging as log
from bs4 import BeautifulSoup
from scrapy.http import HtmlResponse


class CustomsSleniumMiddleware(object):
    def __init__(self):
        # Do not load images
        cap = webdriver.DesiredCapabilities.PHANTOMJS
        cap["phantomjs.page.settings.loadImages"] = False
        self.driver = webdriver.PhantomJS(desired_capabilities=cap)
        self.driver.set_page_load_timeout(5)

    def process_request(self, request, spider):
        if self.use_selenium(request.url):
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
