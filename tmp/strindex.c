#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MAX_LEN 100

int main(int argc, char const *argv[])
{
	
	char *my_str1=NULL;
	char *my_str2=NULL;
	char *tmp_str=(char *)malloc(sizeof(char)*MAX_LEN);
	char tmp_char=0;
	int i=0;

	printf("Please in put your string,first\n");
	while((tmp_char=getchar())!=EOF&&tmp_char!='\n')
	{
		tmp_str[i]=tmp_char;
		i++;
	}
	tmp_str[i]='\0';

	my_str1=(char *)malloc(sizeof(char)*i);
	if (my_str1==NULL)
	{
		printf("my_str1 malloc failed!\n");
	}
	memcpy(my_str1,tmp_str,i);

	printf("Please in put your string,first\n");
	i=0;
	while((tmp_char=getchar())!=EOF&&tmp_char!='\n')
	{
		tmp_str[i]=tmp_char;
		i++;
	}
	tmp_str[i]='\0';

	my_str2=(char *)malloc(sizeof(char)*i);
	if (my_str2==NULL)
	{
		printf("my_str1 malloc failed!\n");
	}
	memcpy(my_str2,tmp_str,i);
	free(tmp_str);

	printf("first string:%s\n",my_str1);
	printf("second string:%s\n", my_str2);
	printf("result: %d\n", strindex(my_str1,my_str2));
	return 0;
}
int strindex(char *s, char *t)
{
	int count_s=0,count_t=0;
	int index=0,count_s_tmp=0;
	while(s[count_s]!=NULL)
	{
		if(s[count_s]==t[count_t])
		{
			count_s_tmp=count_s;
			while(s[count_s_tmp]==t[count_t])
			{
				count_s_tmp++;
				count_t++;
				if (t[count_t]==NULL)
				{
					index=count_s_tmp-strlen(t);

					printf("index %d count_s_tmp %d count_s %d \n",index,count_s_tmp,count_s);
					break;
				}
			}
		}
		count_s++;
		count_t=0;
	}
	if (index!=0)
	{
		return index;
	}
	return -1;
}
