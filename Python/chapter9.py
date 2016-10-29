import os
#9.1
def read_line():
    filename=input("Enter file name:\n")
    with open(filename,'rb') as fobj:
        for i in fobj:
            if i.isspace():
                print(i)
            elif i.strip()[0]!=ord('#') and ord('#') not in i:
                print(i)

#9.2
def showFN():
    filename=input("Enter file name:\n")
    num=input("Enter how many lines read:\n")
    num=int(num)
    i=0
    with open(filename,'rb') as fobj:
        while i<num:
            print(fobj.readline())
            i=i+1


#9.3
def count_line():
    filename=input("Enter file name:\n")
    n=0
    with open(filename,'rb') as fobj:
        for i in fobj:
            n=n+1
        print(n)


#9.4
def showbypage():
     filename=input("Enter file name:\n")
     
     with open(filename,'rb') as fobj:
         while True:
             flag=input("Do you want to read:y/n")
             if flag=='n' or flag=='N':
                 break
             n=0
             while n<25:
                 i=fobj.readline()
                 print(i)
                 n=n+1

#9.5
def cmpfile():
    fileone=input("Enter first file name:\n")
    filesec=input("Enter second file name:\n")
    n=0
    with open(fileone,'rb') as fobj1:
        with open(filesec,'rb') as fobj2:
            while True:
                i=fobj1.readline()
                j=fobj2.readline()
                n=n+1
                if i!=j:
                    w=len(i) if len(i)>len(j) else len(j)
                    y=0
                    while y<w:
                        if i[y]!=j[y]:
                            print("NO %d line No %d  char not same" % (n,y+1))
                            y=y+1
                            break
                    break
            
