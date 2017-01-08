from DataBase import DB_movie,DB_proxy
from web import web
import time

class spider_master(object):
    def __init__(self):
        self.spider = None
        self.movie_db().clear()

    def movie_db(self):
        tmp=DB_movie()
        return tmp.operator
    def scrapy_main(self):

        self.scrapy_slave("http://www.80s.tw/movie/list/-----p",1)
        time.sleep(30)
        self.scrapy_slave("http://www.80s.tw/ju/list/----0--p",1)
        time.sleep(30)
        self.scrapy_slave("http://www.80s.tw/dm/list/----14--p",1)
        time.sleep(30)
        self.scrapy_slave("http://www.80s.tw/zy/list/----4--p",1)
        time.sleep(30)
        self.scrapy_slave("http://www.80s.tw/mv/list/-----p",2)
        time.sleep(30)
        self.scrapy_slave("http://www.80s.tw/video/list/-----p",2)
        time.sleep(30)
        self.scrapy_slave("http://www.80s.tw/course/list/-----p",2)

    def scrapy_slave(self,other_url,mon):
        self.spider = web(35)
        length=self.spider.get_page_length(other_url+str(1))
        print("len={0}".format(length))
        count = 0
        step = 5
        while True:
            
            self.spider.get_overall_info(other_url,count,count+step,mon)
            self.spider.get_downlink()
            self.update_data()
            self.spider.reset()
            count = count + step
            if count + step > length:
                break
            time.sleep(30)
        self.spider.get_overall_info(other_url,count,length,mon)
        self.spider.get_downlink()
        self.update_data()
        self.spider.reset()
    

    def update_data(self):
        res=self.spider.return_result()
        for one in res:
            #print(one)
            self.movie_db().insert(one)

if __name__ == '__main__':
    my_spider=spider_master()
    my_spider.scrapy_main()
    
    
    
        
