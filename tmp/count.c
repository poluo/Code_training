#include <stdio.h>
/****************************************
*This program count the every single input word's length and show it by graph
*****************************************/
//#define DEBUG_0_
#define DEBUG_1_
void show_graph(int len);
int main(int argc, char const *argv[])
{
	char c;
	int length,tmp;
	tmp=0;
#ifdef DEBUG_0_
	printf("Please input your word\n");
	while(getchar()!=EOF)
		tmp++;
	printf("%c\n",tmp);
#endif
#ifdef DEBUG_1_
	tmp=1;
	printf("Please input your word\n");
	while((c=getchar())!=EOF)
	{
		if(c=='\n'||c=='\t'||c==' ')
		{
			tmp=1;//not in word
			//printf("%d\n",length);
			show_graph(length);
			length=0;
		}
		else if (tmp==1)
		{
			length++;
		}
	
	}
#endif
	return 0;
}
void show_graph(int len)
{
	int i=0;
	for (i = 0; i < len; i++)
	{
		printf("*");
		/* code */
	}
	printf("\n");
}