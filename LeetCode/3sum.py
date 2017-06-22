class Solution(object):

    def fourSum(self, nums):
        nums.sort()
        res = []
        for one in range(len(nums)):
            res 

    def threeSum(self, nums):
        nums.sort()
        min_abs= abs(nums[0]+nums[1]+nums[2])
        closet = []
        if min_abs==0:
            closet.append(nums[0],nums[1],nums[2])

        for i in range(len(nums)-2):
            print(i)
            j,k = i+1,len(nums)-1
            while j<k:
                n = nums[i]+nums[j]+nums[k]
                if n == 0:
                    closet.append([nums[i],nums[j],nums[k]])
                    j+=1
                if n > 0:
                    k-=1
                if n < 0:
                    j+=1
        return closet

    def threeSumClosest(self, nums, target):
        nums.sort()
        min_abs= abs(nums[0]+nums[1]+nums[2] - target)
        closet = nums[0]+nums[1]+nums[2]
        for i in range(len(nums)-2):
            j,k = i+1,len(nums)-1
            while j<k:
                n = nums[i]+nums[j]+nums[k]
                if n == target:
                    return target
                if abs(n-target) < min_abs:
                    min_abs = abs(n-target)
                    closet = nums[i]+nums[j]+nums[k]
                if n > target:
                    k-=1
                if n < target:
                    j+=1
        return closet

                    

if __name__ == '__main__':
    test = Solution()
    arr=[-1, 0, 1, 2, -4,4,-3]
    tar = 4
    # res = test.threeSumClosest(arr,tar)
    # print('closet res = {},target ={}'.format(res,tar))
    res = test.threeSum(arr)
    print('threeSum res = {}'.format(res))