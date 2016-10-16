#include <stdio.h>
int main(int argc, char const *argv[])
{
	int number=0x0008;
	int x=0;
	int n=3;
	number^=(-x^number)&(1<<n);
	printf("%d\n",number);
	x=1;
	n=2;
	number^=(-x^number)&(1<<n);
	printf("%d\n", number);
	return 0;
}