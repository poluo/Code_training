
def permute(nums):
    res = [[nums[0]]]
    for one in nums[1:]:
        tmp = []
        for i in range(len(res)+1):
            for k in res:
                tmp.append(k[:i]+[one]+k[i:])    
        res = tmp
    return res

def groupAnagrams(strs):
    res = {}
    for one in strs:
        tmp = tuple(sorted(one))
        if tmp not in res.keys():
            res[tmp] = []
        res[tmp].append(one)
    r=[one for one in res.values()]
    return r
            
        

if __name__ == '__main__':
    a = ["eat", "tea", "tan", "ate", "nat", "bat"]
    print(groupAnagrams(a))
        