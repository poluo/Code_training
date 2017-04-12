from scrapy.http import HtmlResponse
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
import time
from twisted.internet.error import TimeoutError, ConnectionRefusedError, ConnectError, ConnectionLost
from scrapy.core.downloader.handlers.http11 import TunnelError
import logging as log
import sys


class DownloaderMiddleware(object):
    def __init__(self):
        path = "C:\Program Files (x86)\Google\Chrome\chromedriver.exe"
        self.driver = webdriver.Chrome(executable_path=path)  # chrome not work in linux
        # self.driver = webdriver.PhantomJS()
        self.ERRORS = (TimeoutError, ConnectionRefusedError, ConnectError, ConnectionLost, TunnelError)

    def process_request(self, request, spider):
        if request.meta.get('send_keyword'):
            element = self.driver.find_element_by_css_selector(request.meta.get('selector'))
            element.clear()
            element.send_keys(request.meta.get('content'))
            element.send_keys(Keys.RETURN)

            body = self.driver.page_source
            response = HtmlResponse(url=self.driver.current_url, body=body, request=request, encoding='utf8')
            return response
        elif request.meta.get('click'):
            count = 0
            while True:
                count += 1
                try:
                    element = self.driver.find_element_by_css_selector(request.meta.get('selector'))
                    element.click()
                    WebDriverWait(self.driver, 10).until(
                        EC.presence_of_element_located(
                            (By.CSS_SELECTOR, request.meta.get('selector')))
                    )
                    time.sleep(0.5)
                except Exception as e:
                    log.info('WebDriverWait timeout {}'.format(e))
                    self.driver.get(request.url)
                    WebDriverWait(self.driver, 20).until(
                        EC.presence_of_element_located(
                            (By.CSS_SELECTOR, request.meta.get('selector')))
                    )
                    time.sleep(2)
                else:
                    if request.url != self.driver.current_url:
                        break
                    else:
                        log.info('same url in middleware,count = {}'.format(count))
                finally:
                    if count > 3:
                        break
            body = self.driver.page_source
            response = HtmlResponse(url=self.driver.current_url, body=body, request=request, encoding='utf8')
            return response
        else:
            self.driver.get(request.url)
            WebDriverWait(self.driver, 5).until(
                EC.presence_of_element_located(
                    (By.CSS_SELECTOR, "div.search-combobox > div.search-combobox-input-wrap"))
            )
            body = self.driver.page_source
            response = HtmlResponse(url=self.driver.current_url, body=body, request=request, encoding='utf8')
            return response

    def process_exception(self, request, exception, spider):
        if 'Unable to locate element' in str(exception):
            log.info('100 pages already crawled')
            sys.exit("SHUT DOWN EVERYTHING!")
        else:
            log.info('process exception {}'.format(exception))
            self.driver.get("https://www.taobao.com/")
            WebDriverWait(self.driver, 5).until(
                EC.presence_of_element_located(
                    (By.CSS_SELECTOR, 'div.search-combobox > div.search-combobox-input-wrap > input'))
            )
            time.sleep(1)
            num = request.url.split('=')[-1]
            request.url.replace(num, str(int(num) + 44))
            self.driver.get(request.url)

            if 'unknown error' in str(exception):
                log.info('exception {}'.format(exception))
            else:
                log.info('unexcepted exception {}'.format(exception))
