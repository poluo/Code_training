#include <stdio.h>
void rightrot(unsigned int x,int n);
int main(int argc, char const *argv[])
{
	rightrot(5,2);
	return 0;
}
void rightrot(unsigned int x,int n)
{
	int i=0;
	for (i = 0; i < n; ++i)
	{
		if (x&1)
		{
			x=x>>1;
			x|=1<<(sizeof(int)*8-1);
			printf("%x\n",x);
		}
		else
		{
			x=x>>1;
			printf("%x\n",x);
		}	

	}
	printf("final: %x\n",x);
}