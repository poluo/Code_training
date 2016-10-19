import random
def multiply(a,b):
    if isinstance(a,int) and isinstance(b,int):
        return a*b
    elif isinstance(a,float) and isinstance(b,float):
        return a*b
    else:
        return 0

def scores_to_grade(a):
    if isinstance(a,int):
        if a>100:
            return '0'
        elif a>=90:
            return 'A'
        elif a>=80:
            return 'B'
        elif a>=70:
            return 'C'
        elif a>=60:
            return 'D'
        else:
            return 'F'
    else:
        return '0'


def judge_leap_year(a):
    if (a%4==0 and a%100!=0) or a%400==0:
        return True
    else:
        return False


def C_F(a):
    return (a-32)*(5/9)


#最大公约数
#1.辗转相除
#2.相减法
#3.穷举法
def max_common1(a,b):
    if a<b:
        a,b=b,a
    while(a%b!=0):
        c=a%b
        a=b
        b=c    
    return b

def max_common2(a,b):
    if a<b:
        a,b=b,a
    while(a!=b):
        if a>b:
            a=a-b
        elif a<b:
            b=b-a
    return a

def max_common3(a,b):
    if a<b:
        a,b=b,a
    i=1
    ret=0
    while(i<=b):
        if a%i==0 and b%i==0:
            ret=i
    return ret

def min_multi(a,b):
    return (a*b)/(max_common1(a,b))


def rand():
    N=random.randint(1,101)
    alist=[]
    i=N
    while i:
        n=random.randint(1,100)
        alist.append(n)
        i=i-1
    N=random.randint(0,101)
    bList=[]
    i=N
    while i:
        bList.append(random.choice(alist))
        i=i-1
    i=0
    j=0
    while i<N:
        j=i
        while j<N:
            if bList[i]>bList[j]:
                bList[i],bList[j]=bList[j],bList[i]
            j+=1
        i=i+1


    print(bList)
