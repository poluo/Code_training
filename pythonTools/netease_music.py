from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time


class Parser(object):
    """docstring for parser"""
    def __init__(self):
        path="C:\Program Files (x86)\Google\Chrome\chromedriver"
        self.driver = webdriver.Chrome(executable_path=path)
        # self.driver = webdriver.PhantomJS()
    def get_driver(self):
        return self.driver

    def close(self):
        #quit 将关闭整个浏览器，而close只会关闭一个标签页
        self.driver.close()

    def quit(self):
        self.driver.quit()

def get_detail_info(driver,url):
    '''get netease music playlist info'''
    driver.get(url)
    print(driver.title)
    driver.switch_to_frame("g_iframe")
    try:
        element = WebDriverWait(driver, 20).until(
            EC.presence_of_element_located((By.CSS_SELECTOR, "#song-list-pre-cache > div > div > table > tbody > tr"))
        )
        element = driver.find_elements_by_css_selector("#song-list-pre-cache > div > div > table > tbody > tr")
        for one in element:
            data={
            'song_id':one.find_elements_by_css_selector("span.txt > a")[0].get_attribute('href'),
            'song_name':one.find_elements_by_css_selector("span.txt > a")[0].text,
            'song_length':one.find_elements_by_css_selector("span.u-dur")[0].text,
            'singer_name':one.find_elements_by_css_selector("td:nth-child(4) > div > span > a")[0].text,
            'singer_id':one.find_elements_by_css_selector("td:nth-child(4) > div > span > a")[0].get_attribute('href'),
            'album_name':one.find_elements_by_css_selector("td:nth-child(5) > div > a")[0].text,
            'album_id':one.find_elements_by_css_selector("td:nth-child(5) > div > a")[0].get_attribute('href')
            }
            #print(data)
    except Exception as e:
        print("46",e)

if __name__ == '__main__':
    start = time.time()
    url = "http://music.163.com/#/my/m/music/playlist?id=311692545"
    netease_parser=Parser()

    netease_driver=netease_parser.get_driver()
    get_detail_info(netease_driver,url)

    get_detail_info(netease_driver,"http://music.163.com/#/playlist?id=556073939")
    get_detail_info(netease_driver,"http://music.163.com/#/playlist?id=502767290")
    netease_parser.quit()
    end = time.time()
    print(end-start)