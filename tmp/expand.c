#include <stdio.h>
#include <string.h>
void expand(char s1[],char s2[]);
int main(int argc, char const *argv[])
{
	
	char str1[10]="abc-z";
	char str2[100];
	expand(str1,str2);
	printf("%s\n", str2);
	return 0;
}
int is_char_or_num(char s)
{
	if ((s>='a'&&s<='z')||(s>='A'&&s<='Z')||(s>='0'&&s<='9'))
	{
		return 1;
	}
	else
		return 0;
}
void expand(char s1[],char s2[])
{
	int len=strlen(s1);
	int i=0,j=0;
	int tmp=0;
	char c=0;
	for (i = 0; i < len; ++i)
	{
		if (s1[i]=='-'&&is_char_or_num(s1[i-1]))
		{
			tmp=s1[i+1]-s1[i-1];
			c=s1[i-1];
			printf("tmp %d\n",tmp);
			while(tmp)
			{
				c++;
				s2[j]=c;
				printf("c %c s2[j]%c\n",c,s2[j]);
				tmp--;
				j++;
			}
		}
		else
		{
			s2[j]=s1[i];
			printf("s1[i] %c s2[j]%c\n",s1[i],s2[j]);
			j++;
			i++;
		}

	}
	s2='\0';
}
