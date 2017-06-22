# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

def create_list_by_array(a):
    a_list=ListNode(a[0])
    for i in a[1:]:
        if not a_list.next:
            a_list.next=ListNode(i)
            now_list = a_list.next
        else:
            now_list.next=ListNode(i)
            now_list = now_list.next
    return a_list
def print_list(a):
    now_list = a
    while now_list:
        print(now_list.val)
        now_list=now_list.next
        
# class Solution(object):
def mergeTwoLists(l1, l2):
    a_list = l1
    b_list = l2
    now=new_list = ListNode(0)
    while a_list and b_list:
        if a_list.val < b_list.val:
            # print(a_list.val)
            now.next = a_list
            a_list = a_list.next
        else:
            # print(b_list.val)
            now.next = b_list
            b_list = b_list.next
        now = now.next
    now.next = a_list or b_list
    return new_list.next

def longestValidParentheses(s):
    """
    :type s: str
    :rtype: int
    """
    max_len = 0
    length = 0
    my_stack = []
    for one in s:
        if one == ')' and my_stack:
            my_stack.pop()
            length+=1
            max_len = length if length > max_len else max_len
        elif one == '(':
            my_stack.append('(')
        else:
            length = 0
    return max_len*2
import functools

@functools.lru_cache()
def myPow(x, n):
    """
    :type x: float
    :type n: int
    :rtype: float
    """
    if n==1:
        return x
    elif n==0:
        return 1
    else:
        if n & 0x1:
            return x*myPow(x, (n-1))
        else:
            return myPow(x, n//2)*myPow(x, n//2)


if __name__ == '__main__':
    # a=[0,6,8,10]
    # b=[-1,3,5,6,9]
    # a_list=create_list_by_array(a)
    # b_list=create_list_by_array(b)
    # res = mergeTwoLists(a_list, b_list)
    # print_list(res)
    print(longestValidParentheses(')()())'))