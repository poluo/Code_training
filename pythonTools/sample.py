from bs4 import BeautifulSoup
import requests
import logging

movie_info=[]
base_url="http://www.80s.tw"
def get_movie_info(orginal_url):
    web=requests.get(orginal_url)
    web.encoding='utf-8'
    soup=BeautifulSoup(web.text,'lxml')
    movie=soup.select("body > div > div > div > ul.me1.clearfix > li")
    for i in movie:
        try:
            tmp_dict={}
            tmp=i.select('a')
            tmp_url=tmp[0]['href']
            tmp_dict['url']=tmp_url
            tmp_name=tmp[1].text.strip()
            tmp_dict['name']=tmp_name
            tmp_score=i.select('a > span.poster_score')[0].text
            tmp_dict['score']=tmp_score
            movie_info.append(tmp_dict)
            logging.debug(tmp_dict)
        except Exception as e:
            logging.warning(e)
            logging.warning('{0}'.format(tmp))
        
def print_info():
    for i in range(len(movie_info)):
        logging.info('name={0} url={1} score={2}'.\
            format(movie_info[i]['name'],movie_info[i]['score'],movie_info[i]['url']))

def get_page_length(orginal_url):
    web=requests.get(orginal_url)
    web.encoding='utf-8'
    soup=BeautifulSoup(web.text,'lxml')
    length=soup.select("body > div > div > div > div.pager > a")[-1]['href']
    length=length[length.find('p')+1:]
    return int(length)
    
def add_movie_download_url():
    #print(movie_info)
    for offset in movie_info:   
        orginal_url='http://www.80s.tw'+offset['url']
        web=requests.get(orginal_url)
        web.encoding='utf-8'
        soup=BeautifulSoup(web.text,'html.parser')
        try:
            download_link=soup.find("span",class_="xunlei dlbutton1").find('a')['href']
            offset['download_link']=download_link
        except AttributeError as e:
            logging.info('AttributeError url={0}'.format(orginal_url))
        
if __name__ == '__main__':
    
    #日志级别大小关系为：CRITICAL > ERROR > WARNING > INFO > DEBUG > NOTSET
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

    fist_url="http://www.80s.tw/movie/list/2----"

    page_len=get_page_length(fist_url)
    get_movie_info(fist_url)
    for i in range(2,page_len+1):
        next_url="http://www.80s.tw/movie/list/2-----p"+str(i)
        logging.info(next_url)
        get_movie_info(next_url)
        try:
            get_movie_info(next_url)
        except Exception as e:
            logging.info(e)
    
    add_movie_download_url()
    logging.debug(movie_info)

    
