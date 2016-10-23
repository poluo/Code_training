import string
import keyword
alphas=string.ascii_letters
alphas+='_'
print(alphas)
num=string.digits
print(num)

print("Welcome to the Identifier Checker 1.0")
print("Plese input a strig ,at least 2 chars long")
myinput=input("Identifier to test?")
if len(myinput)>1:
    if myinput[0] not in alphas:
        print("Invalid :first symbol must be alphabetic")
    else:
        for onechar in myinput[1:]:
            if onechar not in alphas+num:
                print("Invalid :symbol must be alphabetic or num")

    if myinput in keyword.kwlist:
        print("can not be keyword")
    
else:
    print("two short")
#6.2
num_list=[]
while True:
    num=input("Plese input a number:")
    if num.isdigit:
        num=int(num)
    else:
        break
    num_list.append(num)
    flag=input("do you want continue,y/n?")
    if flag=='n' or flag=='N':
        break


print(num_list)
num_list.sort(reverse=True)
print(num_list)


#6.6
def mystrip(str):
    i=0
    while True:
        if ' '==str[i]:
            str=str[i+1:]
            continue
        else:
            break
    i=len(str)
    while True:
        if ' '==str[i-1]:
            str=str[0:i-1]
            i=len(str)
            continue
        else:
            break

    print(str)
    return str

#6.10
def upto(str):
    i=0
    s=""
    while i<len(str):
        if str[i].isupper():
            s+=str[i].lower()
        elif str[i].islower():
            s+=str[i].upper()
        else:
            s+=str[i]
        i+=1
    return s

#sort_dict

a=[1,2,3,4,5]
b=['a','b','c','d','e']
d=dict(zip(a,b))

#其中e表示dict.items()中的一个元素，e[1]则表示按 值排序如果把e[1]改成e[0]，
#那么则是按键排序，reverse=False可以省略，默认为升序排列。一个经过排序的可迭代类型
sort=sorted(d.items(),key=lambda e:e[0],reverse=True)
for i in sort:
    print(i)



#reverse a list

#First method,alist not change!
alist=[0,1,2,3]
for i in reversed(alist):
    print(i)
print(alist)
alist=list(reversed(alist))
print(alist)

#Second method alist reversed
alist=list("abc")
alist.reverse()
for i in alist:
    print(i)
print(alist)

#Third method alist not change
alist=list("xyz")
for i in alist[::-1]:
    print(i)

print(alist)
blist=alist[::-1]
print(blist)
