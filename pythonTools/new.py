from bs4 import BeautifulSoup
import requests
url = "http://news.qq.com/"
web = requests.get(url)
web.enconding='utf-8'
soup = BeautifulSoup(web.text,'html.parser')
head_link={}
text=[]
for new in soup.select('.linkto'):
	head_link[new.text]=new['href']

for head,link in head_link.items():
	new_web=requests.get(link)
	new_web.enconding='utf-8'
	new_soup=BeautifulSoup(new_web.text,'html.parser')
	time =new_soup.select('.a_time')
	source_site=new_soup.select('.a_source')
	first=True
	with open('{0}.txt'.format(head),'a') as fobj:
		try:
			fobj.write(source_site[0].text)
			fobj.write(time[0].text)
		except Exception as e:
			pass
		for article in new_soup.select('.text')[1:]:
			if first:
				first=False
			else:
				fobj.write("{0}\n".format(article.text))
		

	