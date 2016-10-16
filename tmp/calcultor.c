#include <stdio.h>
#define ERROR 0x80000000
#define MAX_LEN 100
/*calcultor 不能正常使用，优先级无法识别。。。*/

struct mystack 
{
	int number;
	struct mystack *next;
};
int cal(char *s);
int op(int t1,int t2,char c);
int isoperation(char c);
void push(struct mystack *tmp_stack,int tmp);
void print_stcak(struct mystack *tmp_stack);
int pop(struct mystack *tmp_stack);
char *convert_str(char *tmp);
int main(int argc, char const *argv[])
{
	
	char *my_str1=NULL;
	char *tmp_str=(char *)malloc(sizeof(char)*MAX_LEN);
	char tmp_char=0;
	int i=0,result=0;
	printf("Please in put your numbers:\n");
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
	free(tmp_str);
	printf("your numbers:%s\n",my_str1);
	my_str1=convert_str(my_str1);
	printf("after convert:%s\n",my_str1);
	result=cal(my_str1);
	printf("result:%d\n",result);
	return 0;
}
char *convert_str(char *tmp)
{
	int i=0,val=0,j=0;;
	char *tmp_copy=calloc(0,sizeof(char)*MAX_LEN);
	char c=0;
begain:
	while(tmp[i]==' ')
		i++;
	if (isdigit(tmp[i]))
	{
		while(isdigit(tmp[i]))
		{
			tmp_copy[j]=tmp[i];
			j++;
			i++;
		}

		tmp_copy[j]=' ';
		j++;
	}
	printf("66 %s\n", tmp_copy);
	if (isoperation(tmp[i]))
	{
		c=tmp[i];
		i++;
		if (isdigit(tmp[i]))
		{
			while(isdigit(tmp[i]))
			{
				tmp_copy[j]=tmp[i];
				j++;
				i++;
			}
			tmp_copy[j]=' ';
			j++;
			tmp_copy[j]=c;
			j++;
		}
	}
	if (tmp[i]!='\0')
		goto begain;
	j++;
	for ( i = 0; i < j; ++i)
	{
		printf("i %d tmp_copy[%c]\n",i,tmp_copy[i]);
	}
	tmp_copy[j]='\0';
	return tmp_copy;
}
int cal(char *s)
{
	struct mystack *test=calloc(0,sizeof(struct mystack));
	int i=0;
	int val1=0,val2=0;
	while(s[i]==' ')
		i++;//skip whitespace
	//first not whitespace char is not digit return ERROR!
	if (!isdigit(s[i]))
	{
		//printf("error!\n");
		return ERROR;
	}
	while(isdigit(s[i])||isoperation(s[i])||s[i]==' ')
	{
		if(isdigit(s[i]))
		{
			while(isdigit(s[i]))
				{
					val1=val1*10+s[i]-'0';
					i++;
				}
			push(test,val1);
			val1=0;
			print_stcak(test);
		}
		while (s[i]==' ')
			i++;
		while(isoperation(s[i]))
		{
			val1=pop(test);
			val2=pop(test);
			val2=op(val1,val2,s[i]);
			push(test,val2);
			val1=0;
			i++;
		}
	}
	return val2;
}
int op(int t1,int t2,char c)
{
	switch(c)
	{
		case '+':
			return t2+=t1;
		case '-':
			return t2-=t1;
		case '*':
			return t2*=t1;
		case '/':
			return t2/=t1;
		default:
			printf("switch operation error!\n");
			return 0;
	}
}
int isoperation(char c)
{
	return c=='+'||c=='-'||c=='*'||c=='/';
}
void push(struct mystack *tmp_stack,int tmp)
{
	//printf("push number:%d\n",tmp);
	struct mystack *copy_stack=calloc(0,sizeof(struct mystack));
	copy_stack->number=tmp;
	copy_stack->next=tmp_stack->next;
	tmp_stack->next=copy_stack;
}
int pop(struct mystack *tmp_stack)
{
	struct mystack *copy_stack=tmp_stack->next;
	if (copy_stack==NULL)
	{
		//printf("pop out of range!\n");
		return ERROR;
	}
	int num=copy_stack->number;
	tmp_stack->next=copy_stack->next;
	//printf("pop number:%d\n",num);
	return num;
}
void print_stcak(struct mystack *tmp_stack)
{
	struct mystack *copy_stack=tmp_stack;
	copy_stack=copy_stack->next;
	while(copy_stack!=NULL)
	{
		//printf("number:%d\n",copy_stack->number);
		copy_stack=copy_stack->next;
	}
}