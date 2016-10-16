//10进制以内都可以，10以上表示有问题

#include <stdio.h>
#include <string.h>
void itob(int n,char s[],int b);
void resverse(char s[]);
int main(int argc, char const *argv[])
{
	int n=-92;
	char sn[10];
	itob(n,sn,8);
	printf("sn %s\n", sn);
	return 0;
}
void resverse(char s[])
{
	int i,j,c;
	//printf("strlen(s) %d\n",strlen(s));
	for (i = 0,j=strlen(s)-1; i <j ; i++,j--)
	{
		printf("s[i] %c s[j] %c\n",s[i],s[j]);
		c=s[j];
		s[j]=s[i];
		s[i]=c;
		printf("s[i] %c s[j] %c\n",s[i],s[j]);
	}
}
void itob(int n,char s[],int b)
{
	int num=n,i=0;
	int sign=0;

	if (num<0)
	{
		sign=1;
	}
	do
	{
		if (sign==1)
		{
			s[i]=-(num%b)+'0';
		}
		else
			s[i]=num%b+'0';
		i++;
		//printf("i %d\n", i);
	}while((num/=b)!=0);
	if (sign==1)
	{
		s[i]='-';
		i++;
	}
	s[i]='\0';
	printf("s[i] %s\n", s);
	resverse(s);
}