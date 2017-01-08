from bs4 import BeautifulSoup
import multiprocessing
import requests

class web(object):
    """docstring for web"""
    def __init__(self, arg):
        self.data=[]
        self.result=[]
        self.pool_size=arg
        self.proxy=None

    def reset(self):
        self.data=[]
        self.result=[]

    def update_proxy(self):
        pass

    def return_data(self):
        return self.data
    def return_result(self):
        return self.result
    def log_result(self,arg):
        if isinstance(arg,list):
            for one in arg:
                self.data.append(one)
        elif isinstance(arg,dict):
            self.result.append(arg)


    def get_overall_info(self,other_url,start,end):
        pool=multiprocessing.Pool(processes=self.pool_size)
        for i in range(start,end):
            url=other_url+str(i)
            print(url)
            pool.apply_async(self.get_movie_info,args=(url,),callback=self.log_result)
        pool.close()
        pool.join()
        
    def get_downlink(self):

        count=0
        pool=multiprocessing.Pool(processes=self.pool_size)
        print("all movie nums={0}".format(len(self.data)))
        for one in self.data:
            count = count+1
            if count >= self.pool_size:
                pool.close()
                pool.join()
                pool = multiprocessing.Pool(processes=self.pool_size)
                count = 0
                self.update_proxy()
                print("new")
            pool.apply_async(self.get_movie_download_url,args=(one,),callback=self.log_result)
        pool.close()
        pool.join()

    def get_movie_info(self,orginal_url):
        try:
            web=requests.get(orginal_url, proxies=self.proxy, timeout=400)
        except Exception as e:
            self.update_proxy()
            print("get movie info failed ,{0} {1} url passed".format(orginal_url,e))
            return
        if web.status_code!=200:
            print("get movie info failed ,stauts code don\'t match {0} ".format(orginal_url))
            return
        web.encoding='utf-8'
        soup=BeautifulSoup(web.text,'lxml')
        tmp=[]
        movie=soup.select("body > div > div > div > ul.me1.clearfix > li")
        for i in movie:
            try:
                tmp_dict={
                'offset':i.select('a')[0]['href'],
                'name':i.select('a')[1].text.strip(),
                'score':i.select('a > span.poster_score')[0].text
                }
                #print(tmp_dict)
                tmp.append(tmp_dict)
            except Exception as e:
                print("{0} {1}".format(e,tmp))
        return tmp

    def get_movie_download_url(self,data):
        offset=data['offset']
        orginal_url='http://www.80s.tw'+offset
        try:
            web=requests.get(orginal_url,proxies=self.proxy,timeout=400)
        except Exception as e:
            data['download']="unknow"
            self.update_proxy()
            print('download url failed,offset passed {0} {1}'.format(offset,e))
            return data

        if web.status_code!=200:
            data['download']="unknow"
            print('download url status code don\'t match')
            return data
        web.encoding='utf-8'
        soup=BeautifulSoup(web.text,'html.parser')
        try:
            data['download']=soup.find("span",class_="xunlei dlbutton1").find('a')['href']
            #print(data)
            return data
        except AttributeError as e:
            print('AttributeError url={0}'.format(orginal_url))

    def get_page_length(self,orginal_url):
        try:
            web=requests.get(orginal_url,proxies=self.proxy, timeout=400)
        except Exception as e:
            self.update_proxy()
            print('get page length failed, passed {0} '.format(e))
            return 0
        if web.status_code!=200:
            print('get page length failed, status code don\'t match')
            return 0
        web.encoding='utf-8'
        soup=BeautifulSoup(web.text,'lxml')
        length=soup.select("body > div > div > div > div.pager > a")[-1]['href']
        length=length[length.find('p')+1:]
        return int(length)


def scrapy_slave_movie():
    spider = web(35)

    other_url="http://www.80s.tw/movie/list/-----p"
    length=10 #spider.get_page_length()
    print("len={0}".format(length))
    count = 0
    step = 4
    while True:
        spider.get_overall_info(other_url,count,count+step)
        spider.get_downlink()
        #my_spider.update_data()
        spider.reset()
        count = count + step
        if count + step > length:
            break

    spider.get_overall_info(other_url,count,length)
    spider.get_downlink()
    #my_spider.update_data()
    spider.reset()

    
if __name__ == '__main__':
  
    
    scrapy_slave_movie()
