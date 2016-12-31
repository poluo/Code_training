from bs4 import BeautifulSoup
from pymongo import *
import requests
import logging
import time

#数据库模块


def get_movie_info(db,orginal_url):
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
            tmp_dict['download_link']=get_movie_download_url(tmp_dict['offset'])
            db.insert(tmp_dict)
            logging.debug(tmp_dict)
        except Exception as e:
            logging.warning("{0} {1}".format(e,tmp))
  
def get_movie_download_url(url):
    orginal_url='http://www.80s.tw'+url
    web=requests.get(orginal_url)
    web.encoding='utf-8'
    soup=BeautifulSoup(web.text,'html.parser')
    try:
        download_link=soup.find("span",class_="xunlei dlbutton1").find('a')['href']
        return download_link
    except AttributeError as e:
        logging.warning('AttributeError url={0}'.format(orginal_url))

def get_page_length(orginal_url):
    web=requests.get(orginal_url)
    web.encoding='utf-8'
    soup=BeautifulSoup(web.text,'lxml')
    length=soup.select("body > div > div > div > div.pager > a")[-1]['href']
    length=length[length.find('p')+1:]
    return int(length)

if __name__ == '__main__':
    
    #日志模块初始化，日志级别大小关系为：CRITICAL > ERROR > WARNING > INFO > DEBUG > NOTSET
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
    
    client = MongoClient()
    client = MongoClient('localhost',27017)

    db = client.movie_datebase
    collection = db.movie_info

    fist_url="http://www.80s.tw/movie/list"

    page_len=get_page_length(fist_url)
    logging.info('{0} pages detected'.format(page_len))
    #get first page info
    get_movie_info(collection,fist_url)

    start=time.clock()
    for i in range(2,5):
        next_url="http://www.80s.tw/movie/list/-----p"+str(i)
        logging.info(next_url)
        try:
            get_movie_info(collection,next_url)
        except Exception as e:
            logging.info(e)
            
    end=time.clock()
    logging.info('cost {0}s'.format(end - start))
  
