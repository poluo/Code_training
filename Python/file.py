import os

def write_file1():
    filename=input("Enter file name:")
    if ".txt" not in filename:
        filename+=".txt"
    
    f=open(filename,'w+')
    while True:
        aline=input("Enter a line,\"quit\" to quit:\n")
        if aline!='quit':
            f.write("%s%s" % (aline,os.linesep))
        else:
            break
    f.close

def write_file2():
    filename=input("Enter file name:")
    if ".txt" not in filename:
        filename+=".txt"
    alist=[]
    while True:
        aline=input("Enter a line,\"quit\" to quit:\n")
        if aline!='quit':
            alist.append(aline)
        else:
            break

    #第一种写入文件的方法

    '''
    f=open(filename,'w+')
    for lines in alist:
        #print(lines)
        f.write("%s%s" % (lines,os.linesep))
    f.close
    '''
    #第二种写入文件的方法
    with open(filename,'w+') as f:
        '''
        for lines in alist:
            f.write("%s%s" % (lines,os.linesep))
        '''
        #注意这种方法不会加换行符
        f.writelines(alist)



def read_file():
    #read()方法，读取指定字节，如果未指定，读到文件尾，大文件读取使用
    #readline()读取文件的一行，包括换行符，返回字符串，也可以指定字节，但是行可能不完整
    #readlines()读取剩余所有行数，返回的是列表，小文件使用
    with open('test.txt','r') as f:
        #print(f.read(3))
        print(f.readline().strip())
        print(f.readlines())



import sys
print("you have entered",len(sys.argv),"arguments")
print("there are ",str(sys.argv))

#os模块相关操作
os.remove("C:\\Users\\poluo\\Desktop\\test.txt")
os.mkdir("C:\\Users\\poluo\\Desktop\\test")
os.rename("C:\\Users\\poluo\\Desktop\\test","C:\\Users\\poluo\\Desktop\\my")
os.listdir("C:\\Users\\poluo\\Desktop")
#.........



#永久存储模块
import pickle
f=open('H:\\p.txt','wb')
l=[1,2,3]  
pickle.dump(l, f)
f.close()
f=open('H:\\p.txt','rb')
ll=pickle.load(f)
f.close()

