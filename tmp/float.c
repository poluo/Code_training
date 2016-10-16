#include <stdio.h>
int main(int argc, char const *argv[])
{
	float f_num;
	double d_num;
	printf("float: %d\n",sizeof(float));
	printf("double: %d\n",sizeof(double));

	printf("Please input float f_num:\n");
	scanf("%f",&f_num);
	printf("float:f_num: %f\n",f_num);
	printf("double:f_num: %lf\n",f_num);

	printf("Please input double d_num:\n");
	scanf("%lf",&d_num);
	printf("float:d_num: %f\n",d_num);
	printf("double:d_num: %lf\n",d_num);
	return 0;
}