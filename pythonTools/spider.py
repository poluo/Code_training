from bs4 import BeautifulSoup
from pymongo import *
import requests
import time
import multiprocessing

        
class spider_80s(object):
    def __init__(self, pool_size):
        self.pool_size = pool_size
        self.proxy = None
        self.proxies= []
        self.get_proxy()
        self.update_proxy()
        res=self.db().find()
        for one in res:
            self.db().remove(one)
        '''database init mongodb'''
    def db(self):
        client = MongoClient()
        client = MongoClient('localhost',27017)

        db = client.movie_datebase
        collection = db.movie_info
        return collection
    def db_proxy(self):
        client = MongoClient()
        client = MongoClient('localhost',27017)
        db = client.proxies
        collection = db.proxies
        return collection
    def clear_db_proxy(self):
        res=self.db_proxy().find()
        for one in res:
            self.db_proxy().remove(one)
    def get_proxy(self):
        res=self.db_proxy().find()
        for one in res:
            self.proxies.append(one)
    def update_proxy(self):
        tmp=self.proxies.pop()
        self.proxy={"http":tmp['ip']+":"+tmp['port']}
        print(self.proxy)
    def get_movie_info(self,orginal_url):
        try:
            web=requests.get(orginal_url,proxies=self.proxy,timeout=20)
        except Exception as e:
            return
        if web.status_code!=200:
            return
        web.encoding='utf-8'
        soup=BeautifulSoup(web.text,'lxml')
        movie=soup.select("body > div > div > div > ul.me1.clearfix > li")
        for i in movie:
            try:
                tmp_dict={
                'offset':i.select('a')[0]['href'],
                'name':i.select('a')[1].text.strip(),
                'score':i.select('a > span.poster_score')[0].text
                }
                self.db().insert(tmp_dict)
                print(tmp_dict)
            except Exception as e:
                print("{0} {1}".format(e,tmp))
                # self.logging.info("{0} {1}".format(e,tmp))
    def get_movie_download_url(self,offset,return_dict):
        orginal_url='http://www.80s.tw'+offset
        try:
            web=requests.get(orginal_url,proxies=self.proxy,timeout=200)
        except Exception as e:
            self.update_proxy()
            print('offset passed {0}'.format(offset))
            return_dict[offset]=None
            pass
        web=requests.get(orginal_url,proxies=self.proxy,timeout=20)
        if web.status_code!=200:
            return_dict[offset]=None
            return
        web.encoding='utf-8'
        soup=BeautifulSoup(web.text,'html.parser')
        try:
            tmp=soup.find("span",class_="xunlei dlbutton1").find('a')['href']
            return_dict[offset]=tmp
        except AttributeError as e:
            self.logging.info('AttributeError url={0}'.format(orginal_url))
    def get_page_length(self,orginal_url):
        try:
            web=requests.get(orginal_url,proxies=self.proxy,timeout=20)
        except Exception as e:
            self.update_proxy()
            return 0

        if web.status_code!=200:
            return 0
        web.encoding='utf-8'
        soup=BeautifulSoup(web.text,'lxml')
        length=soup.select("body > div > div > div > div.pager > a")[-1]['href']
        length=length[length.find('p')+1:]
        return int(length)
    def spider_get_info(self,first_url,other_url):
        pool=multiprocessing.Pool(processes=self.pool_size)
        page_len=self.get_page_length(fist_url)
        print('{0} pages detected'.format(page_len))

        for i in range(1,10+1):
            if i==1:
                url=fist_url
            else:
                url=other_url+str(i)
            pool.apply_async(self.get_movie_info,(url,))
        pool.close()
        pool.join()
        
    def spider_get_downlink(self):
        pool=multiprocessing.Pool(processes=self.pool_size)
        manager = multiprocessing.Manager()
        return_dict = manager.dict()
        result=self.db().find()
        res=[]
        count=0
        print("all movie nums={0}".format(result.count()))
        for one in result:
            count=count+1
            if count>=self.pool_size:
                pool.close()
                pool.join()
                pool=multiprocessing.Pool(processes=self.pool_size)
                count=0
                self.update_proxy()
                print("new")
            offset=one['offset']
            pool.apply_async(self.get_movie_download_url,(offset,return_dict))
        print(len(return_dict))
        self.update_data(return_dict)
    def update_data(self,dic):
        res=self.db().find()
        for one in res:
            if one['offset'] in dic:
                self.db().remove(one)
                one['download'] = dic[one['offset']]
                print(res)
                self.db().insert(one)
    def get_all_data(self):
        res=self.db().find()
        for one in res:
            print(one)  

if __name__ == '__main__':
    myclass=spider_80s(35)
    fist_url="http://www.80s.tw/movie/list"
    other_url="http://www.80s.tw/movie/list/-----p"
    myclass.spider_get_info(fist_url,other_url)
    myclass.spider_get_downlink()
    myclass.get_all_data()
    
        
