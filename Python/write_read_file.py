##练习，新建一个文件，输入文件的内容，保存，打开，再逐行读取文件内容
import os

ls=os.linesep

def read_file(fname):
    
    try:
        fobj=open(fname,'r')
    except IOError:
        print('open failed')
    else:
        for i in fobj:
            print('%s' % (i.rstrip()))
        #print("%s" % i for i in fobj)
    print("Read Over")
    fobj.close()

    

while True:
    fname=input("please input a not exist name:\n")
    fname+='.txt'
    if os.path.exists(fname):
        print("%s already exsited ,try another name." % fname)
    else:
        print("%s created" % fname)
        break

all=[]
print("Please input line,'quit' to quit")
while True:
    s=input(">>>")
    if s=='quit':
        break
    else:
        all.append(s)


fobj=open(fname,'w')
for i in all:
    fobj.writelines("%s\n" % i.rstrip())

fobj.close()
print('Write Done!')

read_flag=input('do you want read your input')
if read_flag=='y'or read_flag=='Y':
    read_file(fname)
