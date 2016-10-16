#include <stdio.h>
int main(int argc, char const *argv[])
{
	unsigned char count=0;
	while(1)
	{
		if (count++<=3)
		{
			printf("hello world %c\n",count);
			/* code */
		}
		sleep(1);
	}
	return 0;
}