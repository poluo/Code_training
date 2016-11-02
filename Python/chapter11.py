def max2(a,b):
    a,b=int(a),int(b)
    return a if a>b else b
def min2(a,b):
    a,b=int(a),int(b)
    return a if a<b else b

def mymax(*nums):
    result=0
    tmp=0
    try:
        for num in range(len(nums)):
            tmp=max2(nums[num],nums[num-1])
            result=result if result>tmp else tmp
    except IndexError:
        print('Index error')`
        pass
    finally:
        return result
        
def mymin(*nums):
    result=int(nums[0])
    tmp=0
    try:
        for num in range(len(nums)):
            tmp=min2(nums[num],nums[num-1])
            result=result if result<tmp else tmp
    except IndexError:
        print('Index error')
        pass
    finally:
        return result
