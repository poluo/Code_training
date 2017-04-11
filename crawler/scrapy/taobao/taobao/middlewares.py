from scrapy.http import HtmlResponse
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
import time


class DownloaderMiddleware(object):
    def __init__(self):
        path = "C:\Program Files (x86)\Google\Chrome\chromedriver"
        self.driver = webdriver.Chrome(executable_path=path)  # your chosen driver

    def process_request(self, request, spider):
        # only process tagged request or delete this if you want all
        if request.meta.get('send_keyword'):
            self.driver.get(request.url)
            WebDriverWait(self.driver, 5).until(

                EC.presence_of_element_located(
                    (By.CSS_SELECTOR, 'div.search-combobox > div.search-combobox-input-wrap'))
            )
            element = self.driver.find_element_by_css_selector(request.meta.get('selector'))
            element.clear()
            element.send_keys(request.meta.get('content'))
            element.send_keys(Keys.RETURN)
            body = self.driver.page_source
            response = HtmlResponse(url=self.driver.current_url, body=body, request=request, encoding='utf8')
            return response
        elif request.meta.get('click'):
            self.driver.get(request.url)
            WebDriverWait(self.driver, 5).until(

                EC.presence_of_element_located(
                    (By.CSS_SELECTOR, request.meta.get('selector')))
            )
            element = self.driver.find_element_by_css_selector(request.meta.get('selector'))
            element.click()
            time.sleep(2)
            body = self.driver.page_source
            response = HtmlResponse(url=self.driver.current_url, body=body, request=request, encoding='utf8')
            return response
        elif request.meta.get('selenium'):
            self.driver.get(request.url)
            WebDriverWait(self.driver, 5).until(

                EC.presence_of_element_located(
                    (By.CSS_SELECTOR, "div.search-combobox > div.search-combobox-input-wrap"))
            )
            body = self.driver.page_source
            response = HtmlResponse(url=self.driver.current_url, body=body, request=request, encoding='utf8')
            return response
        else:
            return
