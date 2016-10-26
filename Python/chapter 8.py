def isprime(num):
    n=num//2
    while n>1:
        if num%n==0:
            return False
        n-=1
    return True


def getfactors(num):
    fac=[]
    n=num//2
    while n:
        if num%n==0:
            fac.append(n)
        n-=1
    fac.append(num)
    return fac


#素因子分解
#注意：这里所有的因子之积应该等于num，未实现
def return_prime_factors(num):
    f=getfactors(num)
    for i in f:
        if not isprime(i):
            f.remove(i)
    return f


def isperfect(num):
    f=getfactors(num)
    return 2*num==sum(i for i in f)



def nmul(num):
    s=1
    for i in range(1,num+1):
        s=s*i
    return s

def fib(n):
    l=[0,1]
    i=2
    while i<=n:
        l.append(l[i-1]+l[i-2])
        i+=1
    return l[n]



def printnum(n1,n2):
    print("DEC\tBIN\tOCT\t\HEX\tASCII")
    print("---------------------------------------")
    for i in range(n1,n2+1):
        if i<33:
            print(i,bin(i),oct(i),hex(i))
        else:
            print(i,bin(i),oct(i),hex(i),chr(i))


def myinput():
    list=[]
    n=input("Enter total name:")
    n=int(n)
    i=1
    wr_count=0
    while n:
        str=input("Please input name %d" % i)
        str=str.strip()
        if "," not in str:
            print("Wrong format...should be Last,First.")
            str.replace(' ',',')
            wr_count+=1
            print("YOU have done %d time(s)" % wr_count)
        list.append(str)
        i+=1
        n-=1
    print("the sorted list is:")
    for s in sorted(list):
        print(s)
