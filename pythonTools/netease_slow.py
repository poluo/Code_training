# -*- coding: utf-8 -*-  
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import multiprocessing
import logging
import json
import sys
from bs4 import BeautifulSoup


class NeteaseMusic(object):
    """docstring for NeteaseMusic"""

    def __init__(self):
        # path = "C:\Program Files (x86)\Google\Chrome\chromedriver"
        # self.driver = webdriver.Chrome(executable_path=path)

        cap = webdriver.DesiredCapabilities.PHANTOMJS
        cap["phantomjs.page.settings.loadImages"] = False
        self.driver = webdriver.PhantomJS(desired_capabilities=cap)
        self.driver.set_page_load_timeout(5)
        self.offset_list = []
        self.data = []
        '''logging module'''

        self.logger = logging.getLogger('mylogger')
        self.logger.setLevel(logging.DEBUG)

        fh = logging.FileHandler('debug.log')
        ch = logging.StreamHandler()
        ch.setLevel(logging.INFO)
        formatter = logging.Formatter("%(message)s")
        fh.setFormatter(formatter)
        formatter = logging.Formatter("%(module)s:%(lineno)s %(funcName)s %(message)s")
        ch.setFormatter(formatter)

        self.logger.addHandler(fh)
        self.logger.addHandler(ch)

        logging.getLogger("requests").setLevel(logging.WARNING)

    def get_detail_info(self, url):

        try:
            self.driver.get(url)
            # self.logger.info(self.driver.title)
            self.driver.switch_to.frame("g_iframe")
            WebDriverWait(self.driver, 5).until(
                EC.presence_of_element_located(
                    (By.CSS_SELECTOR, "#song-list-pre-cache > div > div > table > tbody > tr"))
            )
        except Exception as e:
            self.logger.info("serious error happened {0}".format(e))
            return

        while 1:
            web = self.driver.page_source
            soup = BeautifulSoup(web, 'lxml')
            element = soup.select("#song-list-pre-cache > div > div > table > tbody > tr")
            if len(element):
                break

        for one in element:
            try:
                tmp_a = one.select("span.txt > a")[0]
                tmp_span = one.select("td:nth-of-type(4) > div > span > a")[0]
                tmp_div = one.select("td:nth-of-type(5) > div > a")[0]
                temp_data = {
                    'song_id': tmp_a['href'],
                    'song_name': tmp_a.text,
                    'song_length': one.select("span.u-dur")[0].text,
                    'singer_name': tmp_span.text,
                    'singer_id': tmp_span['href'],
                    'album_name': tmp_div.text,
                    'album_id': tmp_div['href']
                }
                self.data.append(temp_data)
            except IndexError as e:
                pass
                # self.logger.info("{0} {1}".format(e, url))

    def import_offset(self):
        with open('..\json\\result{0}.json'.format(0), 'r') as fobj:
            self.offset_list = json.load(fobj)
        self.offset_list = self.offset_list[0:20]
        self.logger.info(len(self.offset_list))
        self.logger.info('load json success')

    def grasp_main(self):
        base_url = "http://music.163.com"
        self.import_offset()
        for offset in self.offset_list:
            self.get_detail_info(base_url + offset['href'])
            name = offset['href'][offset['href'].find('=') + 1:]
            self.data.append(offset)
            with open('{0}.json'.format(name), 'w') as fobj:
                json.dump(self.data, fobj)
                self.data = []
                self.logger.info('{0} process finish'.format(name))


def test_json():
    with open('572217819.json', 'r') as fobj:
        offset = json.load(fobj)
    print(offset)


if __name__ == '__main__':
    start = time.time()
    mymusic = NeteaseMusic()
    mymusic.grasp_main()
    end = time.time()
    print(end - start)
