#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_LEN 65535
/*
Leetcode第8题，atoi，把字符串转成整数
Note：
1.考虑前面有空格的情况
2.数字前有可选的正负号
3.数字后面可能有字符，应该忽略这些字符，对数字没有影响
4.如果第一个非空格字符不是数字，或者其他非法情况，返回0
5.如果溢出返回INT_MAX (2147483647) 或 INT_MIN (-2147483648) 
*/
int main(int argc, char const *argv[])
{
	/*mian 函数读取未知长度字符串，动态分配内存
	先动态申请一个较大的空间，如65535字节，直接向里输入字符，
	输入结束后测出长度，按实际需要另外申请一个空间把字符串拷贝过来，释放原来的空间。*/
	char *my_str=NULL;
	char *tmp_str=(char *)malloc(sizeof(char)*MAX_LEN);
	char tmp_char=0;
	int i=0,result=0;
	printf("Please in put your string\n");
	/*先把字符串放入较大的内存中*/
	while((tmp_char=getchar())!=EOF&&tmp_char!='\n')
	{
		tmp_str[i]=tmp_char;
		i++;
	}
	tmp_str[i]='\0';
	/*按照实际长度拷贝，释放原来的空间*/
	my_str=(char *)malloc(sizeof(char)*i);
	if (my_str==NULL)
	{
		printf("my_str malloc failed!\n");
	}
	memcpy(my_str,tmp_str,i);
	free(tmp_str);
	printf("input string:\n%s\n", my_str);
    
	result=myAtoi(my_str);
	printf("result of myAtoi:\n%d\n", result);
	
	return 0;
}
int myAtoi(char* str) 
{
	int i=0,tmp_return=0,sign=0,count=0;
	int length=strlen(str);
	/*非法情况，直接返回0  str是NULL 或者'' */
	if (str==NULL||length==0)
	{
		//printf("str istr NULL!\n");
		return 0;
	}
	/*去除前面的空格*/
	while(str[i]==' ')
	{
		//printf("str[0] error: not strign or digit\n");
		i++;
	}
	/*空格后的可选正负号*/
	if (str[i]=='+'||str[i]=='-')
	{
		if (str[i]=='-')
		{
			sign=1;
		}
		i++;
	}
	/*处理数字字符串*/
	while(str[i]!='\0'&&str[i]>='0'&&str[i]<='9')
	{
		tmp_return=tmp_return*10+str[i]-'0';
		/*有溢出*/
		if (tmp_return>INT_MAX||(tmp_return<0&&sign==0))
		{
			printf("INT_MAX overflow\n");
			return INT_MAX;
		}
		if ((-tmp_return<INT_MIN||-tmp_return>0)&&sign==1)
		{
			printf("INT_MIN overflow\n");
			return INT_MIN;
		}
		if (((tmp_return>INT_MAX/10&&sign==0)||(-tmp_return<INT_MIN/10&&sign==1))&&(str[i+1]!='\0'&&str[i+1]>='0'&&str[i+1]<='9'))
		{
			if (sign==0)
			{
				return INT_MAX;
			}
			else
			{
				return INT_MIN;
			}
		}
		//printf("i:%d tmp_return:%d\n",i,tmp_return);
		i++;
	}

	if (sign==1)
	{
		tmp_return=-tmp_return;
	}
	return tmp_return;
}
