#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1000
#define MAX_LINE 100
char* longestCommonPrefix(char** strs, int strsSize);
int main(int argc, char const *argv[])
{
	char *tmp=(char *)malloc(sizeof(char)*MAX_LEN);
	char *str=NULL;
	char **tmp_ptr=(char **)malloc(sizeof(char *)*MAX_LEN);
	char **str_ptr=NULL;
	int i=0,j=0;
	char c=0;
	while(c!=EOF)
	{
		//printf("Please input your string,EOF to end, Enter to input another:\n");
		while((c=getchar())!='\n'&&c!=EOF)
		{
			*(tmp+i)=c;
			i++;
		}
		*(tmp+i)='\0';
		str=malloc(sizeof(char)*i);
		memcpy(str,tmp,i);
		//printf("%s\n",str);
		*(tmp_ptr+j)=str;
		j++;

		//printf("j=%d, %s\n",j-1,*(tmp_ptr+j-1));
		i=0;
	}
	j--;
	free(tmp);

	str_ptr=(char **)malloc(sizeof(char *)*j);
	memcpy(str_ptr,tmp_ptr,sizeof(char *)*j);
	free(tmp_ptr);
	//printf("out of EOF,j=%d\n",j);
	for (i= 0; i <j; i++)
	{
		printf("i=%d, %s\n",i,*(str_ptr+i));
	}
	
	printf("result of longestCommonPrefix:%s\n",longestCommonPrefix(str_ptr,j));
	return 0;
}
char* longestCommonPrefix(char** strs, int strsSize) 
{
    char *str1="";
    char *str2="";
    int i=0,n=0,tmp_n=0;
    printf("Process longestCommonPrefix，size=%d:\n",strsSize);
    while(i<strsSize)
    {
    	if(i==0)
    	{
    		if (strsSize==1)
    		{
    			return *strs;
    		}
    		n++;
    		str1=*(strs+i);
    		i++;
    		if (strcmp(str1,*(strs+i))==0)
    		{
    			n=strlen(str1);
    			tmp_n=n;
    			str2=str1;
    			printf("n=%d   %s\n",n,str2);
    		}
    		else
    		{
    			while(strncmp(str1,*(strs+i),n)==0&&strcmp(str1,*(strs+i))!=0)
	    		{
	    			n++;
	    		}
    			n--;
	    		tmp_n=n;
	    		str2=(char *)malloc(sizeof(char)*(n+1));
	    		memcpy(str2,str1,n);
	    		*(str2+n)='\0';
	    		printf("n=%d   %s\n",n,str2);
    		}
    		
    	}
    	else
    	{
    		str1=*(strs+i);
    		while(strncmp(str1,str2,n)!=0)
    		{
    			n--;
    		}
    		printf("tmp_n=%d n=%d\n",tmp_n,n);
    		if(n==0)
    		    return "";
    		else if (tmp_n>n)
    		{
    			//free(str2);//free or not ??
    			str2=(char *)malloc(sizeof(char)*(n+1));
	    		memcpy(str2,str1,n);
	    		*(str2+n)='\0';
	    		printf("n=%d   str=%s\n",n,str2);
    		}
    	}
    	i++;
    	printf("i=%d \n",i);
    }
    return str2; 
}