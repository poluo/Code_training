from scrapy.http import HtmlResponse
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
import time
import logging as log
import sys
from scrapy.exceptions import CloseSpider


class DownloaderMiddleware(object):
    def __init__(self):
        path = "C:\Program Files (x86)\Google\Chrome\chromedriver.exe"
        self.driver = webdriver.Chrome(executable_path=path)  # chrome not work in linux
        # self.driver = webdriver.PhantomJS()
        self.first_time = True

    def process_request(self, request, spider):
        if request.meta.get('send_keyword'):
            element = self.driver.find_element_by_css_selector(request.meta.get('selector'))
            element.clear()
            element.send_keys(request.meta.get('content'))
            element.send_keys(Keys.RETURN)
            WebDriverWait(self.driver, 10).until(
                EC.presence_of_element_located(
                    (By.CSS_SELECTOR, '#mainsrp-pager > div > div > div > ul > li.item.next > a'))
            )
            body = self.driver.page_source
            response = HtmlResponse(url=self.driver.current_url, body=body, request=request, encoding='utf8')
            return response
        elif request.meta.get('click'):
            if self.first_time:
                element = self.driver.find_element_by_css_selector(request.meta.get('selector'))
                element.click()
                WebDriverWait(self.driver, 10).until(
                    EC.presence_of_element_located(
                        (By.CSS_SELECTOR, '#mainsrp-itemlist > div > div > div:nth-child(1) > div'))
                )
                time.sleep(1)
                self.first_time = False
            else:
                url = self.get_next_page_url(request.url)
                if not url:
                    log.info('100 pages already crawled')
                    sys.exit("SHUT DOWN EVERYTHING!")
                count = 0
                while True:
                    try:
                        self.driver.get(url)
                        WebDriverWait(self.driver, 10).until(
                            EC.presence_of_element_located(
                                (By.CSS_SELECTOR, '#mainsrp-itemlist > div > div > div:nth-child(1) > div'))
                        )
                    except Exception as e:
                        if 'TimeoutException' in str(e):
                            count += 1
                            time.sleep(1)
                            log.info('TimeoutException in get next page')
                            pass
                        if count > 3:
                            break
                    else:
                        break
                # time.sleep(0.5)

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
        if 'timeout' in str(exception):
            log.info('process exception {}'.format(exception))
            self.driver.get(request.url)
            WebDriverWait(self.driver, 5).until(
                EC.presence_of_element_located(
                    (By.CSS_SELECTOR, 'div.search-combobox > div.search-combobox-input-wrap > input'))
            )
            time.sleep(1)
            request.url = self.get_next_page_url(request.url)
            self.driver.get(request.url)
            log.info('unexcepted exception {}'.format(exception))
        elif 'SHUT DOWN EVERYTHING':
            log.info('close spider')

    def get_next_page_url(self, url):
        num = url.split('=')[-1]
        if int(num) > 44*100:
            return None
        url = url.replace(num, str(int(num) + 44))
        return url
