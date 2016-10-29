import time
import os
dit={}
def adduser():
    while True:
        name=input("enter your name:")
        name=name.lower()
        for i in name:
            if i in " .?,/\`<>(){}[]":
                print("name can not be symbol")
                continue
        if name in dit:
            print("name used ,try anoter name")
            continue
        else:
            c=input("Do you want create a new user")
            if c in 'yY':
                passwd=input("enter your password")
                dit[name]=[passwd,time.localtime()]
                break
            else:
                login()
            

def login():
    name=input("Please enter your user name")
    name=name.lower()
    if name in dit:
        passwd=input("Enter your password")
        if dit[name][0]==passwd:
            print("login success")
            if time.localtime().tm_hour-dit[name][1].tm_hour>4:
                print("you have already loged in at ",dit[name][1])
            dit[name][1]=time.localtime()
            
        else:
            print("password is not correct")
    else:
        print("name not exited")

def deluser():
    name=input("enter user name to delete")
    if name in dit:
        del dit[name]
        print("del success")
    else:
        print("user not in")

def showuser():
    sort=sorted(dit.items(),key=lambda e:e[0],reverse=False)
    for i in sort:
        print(i)
def exitsys():
    with open("log.csv",'w') as fobj:
        fobj.write('username,passwd\n')
        for k,v in dit.items():
            fobj.write("%s,%s" % (k,v[0]))
            fobj.write("\n")
    print('Data already saved!\n')
flag=True
while flag:
    print("Enter 'n' to add user,'l' to login,'e' to exit,'d' to delete user,'s' to show all username")
    choice=input("Plese input your choice")
    if choice not in  "dnles":
        print("try again")
    else:
        if choice=='n':
            adduser()
        elif choice=='e':
            exitsys()
            flag=False
        elif choice=='d':
            deluser()
        elif choice=='s':
            showuser()
        else:
            login()

print("Good Bye")
