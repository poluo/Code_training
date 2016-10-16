/*setbits(x, p, n, y)
*将x中第p位开始的n个位设置为y中最右边n位的值,x的其余位保持不变
*/
#include <stdio.h>
void setbits(unsigned int x, unsigned int p,unsigned int n,unsigned int y)
{
	int i=0;
	for (i = 0; i < n; i++)
	{
		if (y&(1<<i))
		{
			x|=1<<(p-n+i);
			printf("p-n+i=%d x:%u\n",p-n+i,x);
		}
		else
		{
			x&=~(1<<(p-n+i));
			printf("p-n+i=%d x:%u\n",p-n+i,x);
		}
			
		
	}
	printf("final x:%u\n",x);
}
int main(int argc, char const *argv[])
{
	setbits(15,3,2,9);
	return 0;
}
