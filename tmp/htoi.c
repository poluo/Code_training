/*********
*transfer hex to int
*********/

#include <stdio.h>
int* htoi2(char *s);
char *move_0x(char* s);
int main(int argc, char const *argv[])
{
	char *input=malloc(sizeof(char)*100);
	char c=0;
	int i=0,result=0;
	int *output=NULL;
	printf("please input some hex numbers: (100 char is at most)\n");
	while((c=getchar())!='\n'&&c!=EOF)
	{
		input[i]=c;
		i++;
	}
	input[i]='\0';
	printf("your input numbers is %s\n",input);
	output=malloc(sizeof(int)*strlen(input));
	output=htoi2(input);
	
	if (output!=NULL)
	{
		for (i = 0; i < strlen(input)/2; i+=2)
		{
			printf("OUTPUT[I] %d %d\n",output[i],output[i+1]);
			result=output[i]*16;
			result+=output[i+1];
			printf("result %d\n",result);
			printf(" ");
		}
	}
	return 0;
}
int* htoi2(char *s)
{
	char *s_temp=move_0x(s);
	if (s_temp==NULL)
	{
		return NULL;
	}
	printf("return %s\n",s_temp);
	int i=0;
	int *a=malloc(sizeof(int)*strlen(s_temp));

	while(s_temp[i]!='\0')
	{
		if (s_temp[i]>='0'&&s_temp[i]<='9')
		{
			
			a[i]=s_temp[i]-48;
			
		}
		else if (s_temp[i]>='a'&&s_temp[i]<='z')
		{
			printf("s_temp[i] %d\n",s_temp[i]);
			a[i]=s_temp[i]-97+10;
		
		}
		else if (s_temp[i]>='A'&&s_temp[i]<='Z')
		{
			a[i]=s_temp[i]-65+10;
		}
		i++;
	}
	printf("htoi is done\n");
	return a;
}
char *move_0x(char* s)
{
	int i=0,count=0;
	unsigned char start_flag=0;
	char *re=malloc(sizeof(char)*strlen(s));
	while(s[i]!='\0')
	{
		if (s[i]=='0'&&start_flag!=1&&(s[i+1]=='X'||s[i+1]=='x'))
		{
			start_flag=1;
			i+=2;
		}
		else if((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))
		{
			re[count]=s[i];
			i++;
			count++;
			start_flag=0;
		}
		else
		{
			printf("some numbers is wrong: %c\n",s[i]);
			printf("string :%s\n",re);
			return NULL;
		}
	}
	re[count]='\0';
	printf("return string :%s\n",re);
	return re;
}