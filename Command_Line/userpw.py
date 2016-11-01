import time
import os
dit={'admin':['passwd',time.localtime()]}
user_level=1
def adduser():
    while True:
        name=raw_input("enter your name:\n")
        name=name.lower()
        for i in name:
            if i in " .?,/\`<>(){}[]":
                print("name can not be symbol")
                continue
        if name in dit:
            print("name used ,try anoter name")
            continue
        else:
            c=raw_input("Do you want create a new user\n")
            if c in 'yY':
                passwd=raw_input("enter your password\n")
                dit[name]=[passwd,time.localtime()]
                break
            else:
                login()
            

def login():
    global user_level
    name=raw_input("Please enter your user name\n")
    name=name.lower()
    if name in dit:
        passwd=raw_input("Enter your password\n")
        if dit[name][0]==passwd:
            print("login success",name)
            if name=='admin':
            	user_level=2
            if time.localtime().tm_hour-dit[name][1].tm_hour>4:
                print("you have already loged in at ",dit[name][1])
            dit[name][1]=time.localtime()
            
        else:
            print("password is not correct")
    else:
        print("name not exited")

def deluser():
    name=raw_input("enter user name to delete\n")
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
    with open("user.csv",'w') as fobj:
        fobj.write('username,passwd\n')
        for k,v in dit.items():
            fobj.write("%s,%s" % (k,v[0]))
            fobj.write("\n")
    print('Data already saved!\n')


flag=True
while flag:
	print("Enter 'n' to add user,'l' to login,'e' to exit,'d' to delete user,'s' to show all username")
	choice=raw_input("Plese enter your choice\n")
	if choice not in  "dnles":
	    print("try again")
	else:
	    if choice=='n':
	        adduser()
	    elif choice=='e':
	        exitsys()
	        flag=False
	        print("Good Bye")
	    elif choice=='d':
	    	print("user_leavel",user_level)
	        if user_level==2:
	        	deluser()
	        else:
	        	print("Sorry,you don't have right to delete user")
	    elif choice=='s':
	        if user_level==2:
	        	showuser()
	        else:
	        	print("Sorry,you don't have right to delete user")
	    elif choice=='l':
	        login()




