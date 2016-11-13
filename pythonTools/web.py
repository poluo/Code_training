import webbrowser,sys,pyperclip,requests
import bs4
import re
def openurl(addr="www.baidu.com"):
    webbrowser.open(addr)
def geturl(addr="http://www.baidu.com"):
    if 'http' not in addr:
        addr='http://'+addr
    res=requests.get(addr)
    try:
        res.raise_for_status()
    except Execption as exc:
        print('There is a problem:%s' % exc)
    return res
def save_web(addr):
    ret=geturl(addr)
    print(ret.url)
    with open('web.html','wb')  as f:
        for i in ret.iter_lines():
            f.write(i)
def search():
    with open('web.html','rb') as f:
        soup=bs4.BeautifulSoup(f,"html.parser")
        time=soup.select('li h1')
        weather=soup.select('li p[title]')
        tem=soup.select('li p[class="tem"]')
        n=0
        for i in time:
            print(time[n].contents,weather[n].contents,tem[n].contents[0],tem[n].contents[2])
            n=n+1
        
def main():
    if len(sys.argv)>1:
        #将命令行参数从列表转为字符串
        address=''.join(sys.argv[1:])
        print(address)
        openurl(address)
    else:
        #获取剪切板上内容
        address=pyperclip.paste()
        openurl(address)
    
    
