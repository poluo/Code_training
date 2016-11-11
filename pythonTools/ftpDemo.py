'''
ftp登陆连接
from ftplib import FTP            #加载ftp模块
ftp=FTP()                         #设置变量
ftp.set_debuglevel(2)             #打开调试级别2，显示详细信息
ftp.connect("IP","port")          #连接的ftp sever和端口
ftp.login("user","password")      #连接的用户名，密码
print ftp.getwelcome()            #打印出欢迎信息
ftp.cmd("xxx/xxx")                #进入远程目录
bufsize=1024                      #设置的缓冲区大小
filename="filename.txt"           #需要下载的文件
file_handle=open(filename,"wb").write #以写模式在本地打开文件
ftp.retrbinaly("RETR filename.txt",file_handle,bufsize) #接收服务器上文件并写入本地文件
ftp.set_debuglevel(0)             #关闭调试模式
ftp.quit()                        #退出ftp
 
ftp相关命令操作
ftp.cwd(pathname)                 #设置FTP当前操作的路径
ftp.dir()                         #显示目录下所有目录信息
ftp.nlst()                        #获取目录下的文件
ftp.mkd(pathname)                 #新建远程目录
ftp.pwd()                         #返回当前所在位置
ftp.rmd(dirname)                  #删除远程目录
ftp.delete(filename)              #删除远程文件
ftp.rename(fromname, toname)#将fromname修改名称为toname。
ftp.storbinaly("STOR filename.txt",file_handel,bufsize)  #上传目标文件
ftp.retrbinary("RETR filename.txt",file_handel,bufsize)  #下载FTP文件
'''
from ftplib import FTP
class myftp():
    ftp=FTP()
    ftp.set_debuglevel(2)
    def __init__(self,host='115.28.36.253',port=21):
        self.ftp.connect('115.28.36.253',21)
    def login(self,user='test',passwd='poluo123'):
        self.ftp.login('test','poluo123')
        print(self.ftp.getwelcome())
    def DownloadFile(self, LocalFile='test.txt', RemoteFile='test.txt'):
        file_handler = open(LocalFile, 'wb' )
        self.ftp.retrbinary("RETR %s" %( RemoteFile ), file_handler.write ) 
        file_handler.close()
    def uploadfile(self, remotepath='ftpDemo.py', localpath='ftpDemo.py'):
        bufsize = 1024
        fp = open(localpath, 'rb')
        self.ftp.storbinary('STOR '+ remotepath , fp, bufsize) #上传文件
        fp.close()
    def close(self):
        self.ftp.quit()
        

def main():
    ftp=myftp()
    ftp.login()
    ftp.DownloadFile()
    ftp.uploadfile()
    ftp.close()

if __name__ == "__main__":
    main()

