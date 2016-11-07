import webbrowser,sys,pyperclip,requests
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
        
    
if __name__=='__main__':
    sys.exit(main())
    
