from bs4 import BeautifulSoup
import requests
import struct

name=[]
url=[]
score=[]
base_url="http://www.80s.tw"
def get_movie_info(orginal_url):
	web=requests.get(orginal_url)
	web.encoding='utf-8'
	soup=BeautifulSoup(web.text,'lxml')
	movie=soup.select("body > div > div > div > ul.me1.clearfix > li")
	for i in movie:
		tmp=i.select('a')
		url.append(tmp[0]['href'])
		name.append(tmp[1].text.strip())
		score.append(i.select('a > span.poster_score')[0].text)

	

def print_info():
	for i in range(len(name)):
		print('name={0} url={1} score={2}'.format(name[i],url[i],score[i]))

def get_page_length(orginal_url):
	web=requests.get(orginal_url)
	web.encoding='utf-8'
	soup=BeautifulSoup(web.text,'lxml')
	length=soup.select("body > div > div > div > div.pager > a")[-1]['href']
	length=length[length.find('p')+1:]
	return int(length)
	
def get_movie_download_url(orginal_url):
	web=requests.get(orginal_url)
	web.encoding='utf-8'
	print(web)
	print(web.text)
	'''soup=BeautifulSoup(web.text,'lxml')

	tmp_link1=soup.selcet('ul.dllist1 > li.clearfix.dlurlelement.backcolor1 > span.xunlei.dlbutton1 > a')
	tmp_link2=soup.selcet('ul.dllist1 > li.clearfix.dlurlelement.backcolor1 > span.xunlei.dlbutton2 > a')
	print(tmp_link1)
	print(tmp_link2)'''

if __name__ == '__main__':
	fist_url="http://www.80s.tw/movie/list/4----"
	get_movie_download_url('http://www.80s.tw/movie/19359')

	'''page_len=get_page_length(fist_url)
	get_movie_info(fist_url)
	for i in range(2,page_len+1):
		next_url="http://www.80s.tw/movie/list/4-----p"+str(i)
		get_movie_info(next_url)
		

	print_info()'''

	
