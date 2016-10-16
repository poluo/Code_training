/*
esacpe show'\n'--'\\''n' '\t'--'\\'t'
inv_escape show \\''n'--'\n'   '\\'t'--'\t'
*/
#include <stdio.h>
void escape(char *s,char *t);
void inv_escape(char *s,char *t);
int main(int argc, char const *argv[])
{
	char *str_pt=NULL;
	char *str_des=NULL;
	int str_len=0,count=0;
	char c=0;
	printf("please input your string's length :\n");
	scanf("%d",&str_len);
	str_pt=malloc(sizeof(char)*str_len);
	getchar();
	printf("please input your string:\n");
	while((c=getchar())!=EOF)
	{
		*(str_pt+count)=c;
		count++;
	}
	printf("input done\n");
	*(str_pt+count)='\0';
	printf("your's string is:\n%s\n",str_pt);
	int count2=0;
	while(*(str_pt+count)!='\0')
	{
		count2++;
		count++;
		if (*(str_pt+count)=='\n'||*(str_pt+count)=='\t')
		{
			count2++;
		}
	}
	str_des=malloc(sizeof(char)*count2);
	escape(str_des,str_pt);
	printf("escape string is:\n%s\n",str_des);
	inv_escape(str_pt,str_des);
	printf("inverse  string is:\n%s\n",str_pt);
	return 0;
}
void escape(char *s,char *t)
{
	int count=0,count2=0;
	while(*(t+count2)!='\0')
	{
		switch(*(t+count2))
		{
			case 9://\t
				*(s+count)=92;
				count++;
				*(s+count)='t';
				count++;
				count2++;
				break;
			case 10://\n
				*(s+count)=92;
				count++;
				*(s+count)='n';
				count++;
				count2++;
				break;
			default:
				*(s+count)=*(t+count2);
				count++;
				count2++;
				break;
		}
	}
	*(s+count)='\0';
}
void inv_escape(char *s,char *t)
{
	int count=0,count2=0;
	while(*(t+count)!='\0')
	{
		switch(*(t+count))
		{
			case 92://'\\'
			{
				count++;
				if (*(t+count)=='n')
				{
					count--;
					*(s+count2)=10;
					count++;
					count++;
					count2++;
				}
				else if (*(t+count)=='t')
				{
					count--;
					*(s+count2)=9;
					count++;
					count++;
					count2++;
				}
				break;
				
			}
			
			default:
				*(s+count2)=*(t+count);
				count++;
				count2++;
				break;
		}
		
	}
	*(s+count)='\0';
}