/*invert(x, p, n)
*把x中从第p位开始的n位取反，其余保持不变
*/
#include "stdio.h"
unsigned int invert(unsigned int x,unsigned int p,unsigned int n);
int main(int argc, char const *argv[])
{
	invert(59,5,4);
	return 0;
}
unsigned int invert(unsigned int x,unsigned int p,unsigned int n)
{
	int i=0;
	for (i = 0; i < n; i++)
	{
		x^=1<<(p-n+i);
		printf("%d x= %u\n",i,x);
	}
	printf("final: %u\n",x);
	return x;
}