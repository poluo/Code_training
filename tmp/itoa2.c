#include <stdio.h>
#include <string.h>
void itoa(int n,char s[],int length);
void resverse(char s[]);
int main(int argc, char const *argv[])
{
	int n=98;
	char sn[10];
	printf("%d",n);
	itoa(n,sn,5);
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
void itoa(int n,char s[],int length)
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
			s[i]=-(num%10)+'0';
		}
		else
			s[i]=num%10+'0';
		i++;
		//printf("i %d\n", i);
	}while((num/=10)!=0);
	if (sign==1)
	{
		s[i]='-';
		i++;
	}
	while(i<length)
	{
		s[i]=' ';
		i++;
	}
	s[i]='\0';
	printf("s[i] %s\n", s);

	resverse(s);
}