/*
int to Roman
 */
#include <stdio.h>
#include <stdlib.h>
char* intToRoman(int num);
int romanToInt(char* s) ;
int main(int argc, char const *argv[])
{
	/*int num=0;
	printf("Please input your number:\n");
	while(scanf("%d",&num)==1)
	{
		printf("your input number:%d\n",num);
		printf("Roman number:%s\n",intToRoman(num));
		printf("Please input your number:\n");
	}*/
	/*char *tmp=malloc(sizeof(char)*20);
	char *str=NULL;
	char c=0;
	int i=0;
	printf("Please input your Roman number:\n");
	while((c=getchar())!='\n'&&c!=EOF)
	{
		*(tmp+i)=c;
		i++;
	}
	*(tmp+i)='\0';
	printf("your Roman number is %s\n",tmp);
	str=malloc(sizeof(char)*i);
	memcpy(str,tmp,i);
	free(tmp);
	printf("str=%s\n",str);
	printf("result=%d\n",romanToInt(str));*/
	printf("Test beagin,intToRoman and RomanToInt:\n");
	int i=0,sign=0;
	char *tmp=NULL;
	for (i = 1; i < 4000; i++)
	{
		tmp=intToRoman(i);
		if (i!=romanToInt(tmp))
		{
			printf("error! i=%d,roman=%s,toint=%d\n",i,tmp,romanToInt(tmp));
			sign=1;
			break;
		}
	}
	if (sign==0)
	{
		printf("Success! all right.\n");
	}
	printf("Test ends\n");
	/*int i=0;
	char *res=NULL;
	for (i = 1; i < 4000; i++)
	{
		res=intToRoman(i);
	}
*/
	return 0;
}
char* intToRoman(int num) 
{
	char *result=NULL;
	char *tmp=malloc(sizeof(char)*20);
	char N[4][2]={'I','V',
				'X','L',
				'C','D',
				'M'};
	int i=0;
	int copy_num=num;
	int reverse_num=0;
	int end_num=0;
	int bit=num>999?4:(num>99?3:(num>9?2:1));
	//printf("bit=%d\n",bit);
	while(copy_num!=0)
	{
		reverse_num=reverse_num*10+copy_num%10;
		copy_num/=10;
	}
	//printf("bit=%d\n",bit);
	//printf("reverse_num=%d\n",reverse_num);
	while(bit)
	{
		end_num=reverse_num%10;
		//printf("end_num=%d,reverse_num=%d\n",end_num,reverse_num );
		if (end_num!=4&&end_num!=9)
		{
			if(end_num<5)//1 2 3 
			{
				while(end_num)
				{
					tmp[i]=N[bit-1][0];
					i++;
					end_num--;
				}	
			}
			else //5 6 7 8
			{
				tmp[i]=N[bit-1][1];
				i++;
				while(end_num>5)
				{
					tmp[i]=N[bit-1][0];
					i++;
					end_num--;
				}
			}
		}
		else
		{
			if (end_num==4)//4
			{
				tmp[i]=N[bit-1][0];
				i++;
				tmp[i]=N[bit-1][1];
				i++;
			}
			else //9
			{
				tmp[i]=N[bit-1][0];
				i++;
				tmp[i]=N[bit][0];
				i++;
			}
		}
		reverse_num/=10;
		bit--;
	} 
	tmp[i]='\0';
	//printf("i=%d,tmp=%s\n",i,tmp);
	result=(char *)malloc(sizeof(char)*i);
	memcpy(result,tmp,i);
	free(tmp);
	//printf("result=%s\n",result);
	return result;
}
