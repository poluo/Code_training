/*
Valid Parentheses
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 100
typedef enum n
{
	FLASE,
	TURE
}bool;
struct mystack 
{
	char number;
	struct mystack *next;
};
void print_stcak(struct mystack *stack);
bool isValid(char* s);
int main(int argc, char const *argv[])
{
	
	char *my_str=NULL;
	char *tmp_str=(char *)malloc(sizeof(char)*MAX_LEN);
	char tmp_char=0;
	int i=0,result=0;
	printf("Please in put your string:\n");
	while((tmp_char=getchar())!=EOF&&tmp_char!='\n')
	{
		tmp_str[i]=tmp_char;
		i++;
	}
	tmp_str[i]='\0';
	my_str=(char *)malloc(sizeof(char)*i);
	if (my_str==NULL)
	{
		printf("my_str1 malloc failed!\n");
	}
	memcpy(my_str,tmp_str,i);
	free(tmp_str);

	printf("your string Valid or not :%d\n",isValid(my_str));
	return 0;
}
bool isValid(char* s) 
{
	
	int i=0;
	struct mystack *test=NULL;
	int count=0;
	char c=0;
    while(s[i]!='\0')
    {
    	if (s[i]!='['&&s[i]!=']'&&s[i]!='('&&s[i]!=')'&&s[i]!='{'&&s[i]!='}')
    	{
    		return 0;
    	}
    	else
    	{
    		if (s[i]=='['||s[i]=='{'||s[i]=='(')
    		{
    			if (test==NULL)
    			{
    				//printf("test is NULL\n");
    				struct mystack *tmp_stack=calloc(0,sizeof(struct mystack));
    				tmp_stack->number=s[i];
    				tmp_stack->next=NULL;
    				//printf("test\n");
    				test=tmp_stack;
    				count++;
    				//printf("count: %d char: %c\n",count,test->number);
    				//print_stcak(test);
    			}
    			else
    			{
    				struct mystack *copy_stack=test;
    				struct mystack *tmp_stack=calloc(0,sizeof(struct mystack));
    				tmp_stack->number=s[i];
    				tmp_stack->next=copy_stack;
    				test=tmp_stack;
    				count++;
    				//printf("count: %d char: %c\n",count,test->number);
    				//print_stcak(test);
    			}
    		}
    		else
    		{
    			if (test!=NULL)
    			{
    				c=test->number;
    			}
    			//printf("c: %c\n",c);
    			if ((c=='['&&s[i]==']')||(c=='{'&&s[i]=='}')||(c=='('&&s[i]==')'))
    			{
    				//printf("Parentheses\n");
    				struct mystack *copy_stack=test;
    				test=copy_stack->next;
    				free(copy_stack);
    				count--;
    			}
    			else
    				return 0;
    		}
    	}
    	i++;
    }
    //printf("isValid end\n");
    if (count!=0)
    {
    	return 0;
    }
    return 1;
}
void print_stcak(struct mystack *stack)
{
	struct mystack *tmp_stack=stack;
	printf("Print stack:\n");
	while (tmp_stack!=NULL)
	{
		printf("%c %d\n", tmp_stack->number,tmp_stack->number);
		tmp_stack = tmp_stack->next;
	}
}