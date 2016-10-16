/*
 * input some lines ,and output the longest line
*/
#include <stdio.h>
#define MAX_LEN 20
#define DEBUG_0_
#define DEBUG_1_
char *longest;
char *temp;
int getline1();
int length=0;
int main(int argc, char const *argv[])
{
	longest=(char *)malloc(sizeof(char)*MAX_LEN);
	temp=(char *)malloc(sizeof(char)*MAX_LEN);

	getline1();
	printf("the longest line's length: %d\n",length);
	printf("the longest line: %s\n",longest);

	return 0;
}
int getline1()
{
	char c;
	int i=0,count=0;
	while((c=getchar())!=EOF)
	{
		/*if ((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
		{
			*(temp+count)=c;
			count++;
		}*/
		if (c=='\n')
		{
			if (count>length)
			{
				length=count;
				printf("%d\n",length);
				for (i = 0; i < length; ++i)
				{
					*(longest+i)=*(temp+i);
				}
				*(longest+i)='\n';
				i++;
				*(longest+i)='\0';
				/* code */
			}
			count=0;
			/* code */
		}
		else
		{
			*(temp+count)=c;
			count++;
		}
	}
}