#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char **generateParenthesis(int n, int *returnSize);

int main(int argc, char const *argv[])
{
	char **test=NULL;
	int len=0,i=0;

	test=generateParenthesis(5,&len);
	printf("len=%d\n",len);

	for (i = 0; i < len; ++i)
	{
		printf("%s\n",test[i]);
	}
	getchar();
	return 0;
}
int is_special(char *str,int length)
{
	char *tmp=calloc(length,sizeof(char));
	int i=0;

	for (i = 0; i < length; ++i)
	{
		if (i%2==0)
		{
			tmp[i]='(';
		}
		else
		{
			tmp[i]=')';
		}
	}

	if (strncmp(tmp,str,length)==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

char *memcpy_left(char *str,int len)
{
	int length = len*2;
	char *ret=malloc(sizeof(char)*(length+3));
	
	ret[0]='(';
	ret[1]=')';
	strncpy(&ret[2],str,length);
	ret[length+2]='\0';

	return ret;	
}

char *memcpy_mid(char *str,int len)
{
	int length = len*2;
	char *ret=malloc(sizeof(char)*(length+3));

	ret[0]='(';
	strncpy(&ret[1],str,length);
	ret[length+1]=')';
	ret[length+2]='\0';

	return ret;
}

char *memcpy_right(char *str,int len)
{
	int length=len*2;
	char *ret=malloc(sizeof(char)*(length+3));

	strncpy(ret,str,length);
	ret[length]='(';
	ret[length+1]=')';
	ret[length+2]='\0';

	return ret;
}
char **generateParenthesis(int n, int *returnSize)
{
	static char *pat = "()";
	char left_pat = '(';
	char right_pat = ')';
	int i = 0;


	if (n == 1)
	{
		*returnSize=1;
		return &pat;
	}
	else
	{
		//*returnSize=pow(2,n)-n;

		char *sub_one_str = malloc(sizeof(char) * (2 * (n-1)));
		char **sub_ret_str = NULL;
		int tmp_len = 0;
		sub_ret_str = generateParenthesis(n-1,&tmp_len);

		printf("tmp_len=%d \n",tmp_len);
		/*for (i = 0; i < tmp_len; ++i)
		{
			printf("%s\n",sub_ret_str[i]);
		}*/

		char *ret_one_str = malloc(sizeof(char) * (2*n+1));
		char **ret_str = malloc(sizeof(ret_one_str) * (tmp_len*3-1));
		int count=0;

		for (i = 0; i < tmp_len; ++i)
		{
			if (is_special(sub_ret_str[i],2*(n-1)))
			{
			}
			else
			{
				ret_str[count]=memcpy_left(sub_ret_str[i],n-1);
				//printf("73 %s\n", ret_str[count]);
				count++;
			}
			
			ret_str[count]=memcpy_right(sub_ret_str[i],n-1);
			//printf("75 %s\n", ret_str[count]);
			count++;
			ret_str[count]=memcpy_mid(sub_ret_str[i],n-1);
			//printf("78 %s\n", ret_str[count]);
			count++;
		}
		*returnSize=count;
		return ret_str;
	}
}


