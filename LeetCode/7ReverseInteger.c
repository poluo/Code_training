/*
LeetCode No.7
Example1: x = 123, return 321
Example2: x = -123, return -321
Reverse Integer
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int reverse2(int x);
int main(int argc, char const *argv[])
{
	int num=0;
	printf("Please input your number:\n");
	while(scanf("%d",&num)==1)
	{
		printf("your input number:%d\n",num);
		printf("reverse number:%d\n",reverse2(num));
		printf("Please input your number:\n");
	}
	printf("error input,exit!\n");	
	return 0;
}
/*
x作为参数，不会溢出，即使溢出，也会截取。只考虑转换后溢出的情况。比如-1000000003.
溢出的判读：加减的话看符合，乘法的话把数除回去，看相不相等。
 */
int reverse2(int x) 
{
	int flag=x<0?-1:1;	
	int ret=0,last_ret=0;
	while(x!=0)
	{
		ret=ret*10+x%10;
		if ((ret-x%10)/10!=last_ret)
		{
			return 0;
		}
		x/=10;
		last_ret=ret;
	}
	return ret;
}
