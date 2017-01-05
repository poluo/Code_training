from bs4 import BeautifulSoup
# from pymongo import *
import requests
import logging
import time
import multiprocessing

class logger(object):
    """docstring for logger"""
    def __init__(self):
        super(logger, self).__init__()
        logging.basicConfig(level=logging.DEBUG,
                format='%(message)s',
                datefmt= '%S',
                filename='debug.log',
                filemode='w')
        console = logging.StreamHandler()
        console.setLevel(logging.INFO)
        formatter = logging.Formatter('%(message)s')
        console.setFormatter(formatter)
        logging.getLogger('').addHandler(console)
        logging.getLogger('requests').setLevel(logging.WARNING)
    def info(self,arg):
        logging.info(arg)  
        
class spider_80s(object):
    def __init__(self, pool_size):
        self.pool_size = pool_size
        '''log module init'''
        self.logging=logger()
        self.logging.info("spider ok")
        '''database init mongodb'''
        # client = MongoClient()
        # client = MongoClient('localhost',27017)

        # db = client.movie_datebase
        # self.collection = db.movie_info
    def spider_get_info(self,first_url,other_url):
        pool=multiprocessing.Pool(processes=self.pool_size)

        page_len=self.get_page_length(fist_url)
        self.logging.info('{0} pages detected'.format(page_len))

        for i in range(1,10+1):
            self.logging.info("i={0}".format(i))
            if i==1:
                url=fist_url
            else:
                url=other_url+str(i)
            pool.apply_async(self.get_movie_info,(url,))
        pool.close()
        pool.join()
    def spider_get_downlink(self):
        pool=multiprocessing.Pool(processes=self.pool_size)
        # res=self.collection.find()
        self.logging.info("all movie nums={0}".format(res.count()))
        for one in res:
            offset=one['offset']
            pool.apply_async(self.get_movie_download_url,(offset,))
        pool.close()
        pool.join()

    def get_movie_info(self,orginal_url):
        web=requests.get(orginal_url)
        web.encoding='utf-8'
        soup=BeautifulSoup(web.text,'lxml')
        movie=soup.select("body > div > div > div > ul.me1.clearfix > li")
        for i in movie:
            try:
                tmp_dict={}
                tmp=i.select('a')
                tmp_url=tmp[0]['href']
                tmp_dict['offset']=tmp_url
                tmp_name=tmp[1].text.strip()
                tmp_dict['name']=tmp_name
                tmp_score=i.select('a > span.poster_score')[0].text
                tmp_dict['score']=tmp_score
                # self.collection.insert(tmp_dict)
                print(tmp_dict)
                #self.logging.debug("tmp_dict")
            except Exception as e:
                print("{0} {1}".format(e,tmp))
                # self.logging.info("{0} {1}".format(e,tmp))
    def get_movie_download_url(self,offset):
        orginal_url='http://www.80s.tw'+offset
        web=requests.get(orginal_url)
        web.encoding='utf-8'
        soup=BeautifulSoup(web.text,'html.parser')
        try:
            download_link=soup.find("span",class_="xunlei dlbutton1").find('a')['href']
            return download_link
        except AttributeError as e:
            self.logging.info('AttributeError url={0}'.format(orginal_url))
    def get_page_length(self,orginal_url):
        web=requests.get(orginal_url)
        web.encoding='utf-8'
        soup=BeautifulSoup(web.text,'lxml')
        length=soup.select("body > div > div > div > div.pager > a")[-1]['href']
        length=length[length.find('p')+1:]
        return int(length)

if __name__ == '__main__':
    myclass=spider_80s(80)
    fist_url="http://www.80s.tw/movie/list"
    other_url="http://www.80s.tw/movie/list/-----p"
    myclass.spider_get_info(fist_url,other_url)
    # myclass.spider_get_downlink()
        