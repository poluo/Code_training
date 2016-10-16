/*
*3. Longest Substring Without Repeating Characters  
*Given a string, find the length of the longest substring without repeating characters.
*Examples:
*Given "abcabcbb", the answer is "abc", which the length is 3.
*Given "bbbbb", the answer is "b", with the length of 1.
*Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100
int lengthOfLongestSubstring(char* s);
int main(int argc, char const *argv[])
{
	char *tmp_ptr=malloc(sizeof(char)*MAX_LEN);
	char *s_ptr=NULL;
	int i=0;
	char tmp_c=0;
	printf("Please input your string:\n");
	while((tmp_c=getchar())!='\n'&&tmp_c!=EOF)
	{
		*(tmp_ptr+i)=tmp_c;
		i++;
	}
	*(tmp_ptr+i)='\0';
	s_ptr=malloc(sizeof(char)*i);
	memcpy(s_ptr,tmp_ptr,i);
	free(tmp_ptr);
	printf("Longest Substring length=%d\n",lengthOfLongestSubstring(s_ptr));
	return 0;
}
int lengthOfLongestSubstring(char* s) 
{
	int ar[128]={0};
	int i=0;
	int tmp_val=0,last_val=0,val=0;
	char c=0,last_c=0;

	while((c=*(s+i))!='\0')
	{
		if (ar[c]==0)
		{
			tmp_val++;
			ar[c]=i+1;
		}
		else
		{
			if (last_c==c)
			{
				printf("tmp_val==1,all clear!\n");
				memset(ar,0,sizeof(int)*128);
				tmp_val=1;
			}
			else
			{
				tmp_val=i+1-ar[c];
			}
			ar[c]=i+1;
		}
		if (tmp_val>last_val)
			tmp_val=last_val+1;
		val=val>tmp_val?val:tmp_val;
		last_c=c;
		last_val=tmp_val;
		printf("char=%c val=%d tmp_val=%d  i=%d\n", *(s+i),val,tmp_val,i);
		i++;
	}
	val=val>tmp_val?val:tmp_val;
	return val;
}