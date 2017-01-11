from bs4 import BeautifulSoup
from config import HEADER,TIMEOUT
import multiprocessing
import requests
import json

def get_palylist_overall_info(orginal_url):

    playlists_overall_info=[]

    try:
        web=requests.get(orginal_url, timeout=400)
    except Exception as e:
        print("get_palylist_overall_info failed, {0} {1} url passed".format(orginal_url,e))
        return
    if web.status_code!=200:
        print("get_palylist_overall_info, stauts code don\'t match {0} ".format(orginal_url))
        return
    web.encoding='utf-8'
    soup=BeautifulSoup(web.text,'lxml')
    playlists_row_data=soup.select('ul > li')
    for one in playlists_row_data:
        try:
            tmp={
            'img':one.select('div.u-cover.u-cover-1 > img')[0]['src'],
            'title':one.select('div.u-cover.u-cover-1 > a')[0]['title'],
            'href':one.select('div.u-cover.u-cover-1 > a')[0]['href'],
            'play_num':one.select('div.u-cover.u-cover-1 > div.bottom > span.nb')[0].text,
            }
        except IndexError as e:
            continue
        try:
           tmp['author']=one.select('p:nth-of-type(2) > a')[0].text
        except Exception as e:
            print(e)
            pass
        playlists_overall_info.append(tmp)
    print(playlists_overall_info)
def get_palylist_detail_info(offset):
    palylist_detail_info=[]
    orginal_url="http://music.163.com/api/playlist/detail?id="+offset+"&updateTime=-1"
    try:
        web=requests.get(orginal_url,headers = HEADER, timeout = TIMEOUT)
    except Exception as e:
        print("get movie info failed ,{0} {1} url passed".format(orginal_url,e))
        return
    if web.status_code!=200:
        print("get movie info failed ,stauts code don\'t match {0} ".format(orginal_url))
        return
    web.encoding='utf-8'
    #print(web.text)
    info = json.loads(web.text)
    song_lists = info["result"]["tracks"]
    for one in song_lists:
        print(one)
        break


if __name__ == '__main__':
    # url="http://music.163.com/discover"
    # get_movie_info(url)
    # playlist_id="549789053"
    # get_palylist_detail_info(playlist_id)
