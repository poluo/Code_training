/*
Palindrome Numbe
 */
#include <stdio.h>

typedef enum
{
	FLASE=0,
	TURE
}bool;
bool isPalindrome(int x);
int main(int argc, char const *argv[])
{
	int num=0;
	printf("Please input your number:\n");
	while(scanf("%d",&num)==1)
	{
		printf("your input number:%d\n",num);
		printf("isPalindrome:%d\n",isPalindrome(num));
		printf("Please input your number:\n");
	}
	printf("error input,exit!\n");	
	return 0;
}
bool isPalindrome(int x)
{	
	int ret=0,last_ret=0;
	int copy_x=x;
	while(copy_x!=0)
	{
		ret=ret*10+copy_x%10;
		if ((ret-copy_x%10)/10!=last_ret)
		{
			printf("overflow\n");
			return 0;
		}
		copy_x/=10;
		last_ret=ret;
	}
	//printf("ret=%d\n,return=%d\n",ret,(copy_x==ret)?1:0);
	return (x==ret)?1:0;
}