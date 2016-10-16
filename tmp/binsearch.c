#include <stdio.h>
#include <sys/time.h>
int binsearch(int x,int v[],int n)
{
	int low,high,mid;
	low=0;
	high=n-1;
	//printf("%d\n",high);
	//getchar();
	while(low<=high)
	{
		mid=(low+high)/2;
		//getchar();
		//printf("mid %d\n",mid);
		if (x<v[mid])
		{
			
			high=mid-1;
			//printf("high %d\n",high);
		}
		else if (x>v[mid])
		{
			
			low=mid+1;
			//printf("low %d\n",low);
		}
		else
			return mid;
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	int t[10]={0,1,3,4,5,6,7,8,9};
	int num=0,num2=0;
	int count=100;
	struct  timeval  start;
  	struct  timeval  end;
  	unsigned long timer;
	printf("begain:\n");
	gettimeofday(&start,NULL);
	while(count)
	{
		for ( num = 0; num < 10; num++)
		{
			num2=binsearch(num,t,10);
			//printf("num: %d x: %d\n",num,t[num2]);
		}
		count--;
	}
	gettimeofday(&end,NULL);
	timer = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
	printf("timer = %ld us\n",timer);
	count=100;
	gettimeofday(&start,NULL);
	while(count)
	{
		for ( num = 0; num < 10; num++)
		{
			num2=binsearch2(num,t,10);
			//printf("num: %d x: %d\n",num,t[num2]);
		}
		count--;
	}
	
	gettimeofday(&end,NULL);
	printf("timer = %ld us\n",timer);
	return 0;
}
int binsearch2(int x,int v[],int n)
{
	int low,high,mid;
	low=0;
	high=n-1;
	while(low<=high&&v[mid]!=x)
	{
		mid=(low+high)/2;
		if (x<v[mid])
		{
			high=mid-1;
		}
		else 
		{
			low=mid+1;
		}
		

	}
	if (v[mid]==x)
	{
		return mid;
	}
	else
	    return -1;
}