/*
11. Container With Most Water  QuestionEditorial Solution  My Submissions
Total Accepted: 92877
Total Submissions: 260483
Difficulty: Medium
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX_LEN 100
int maxArea(int* height, int heightSize);
int main(int argc, char const *argv[])
{
	/*int num=0;
	int *tmp_ptr=malloc(sizeof(int)*MAX_LEN);
	int *con_ptr=NULL;
	int i=0,tmp_i=0;
	printf("Please input your number:\n");
	while(scanf("%d",&num))
	{
		*(tmp_ptr+i)=num;
		i++;
	}
	printf("i=%d\n",i);*/


	/*for (tmp_i= 0; tmp_i<i ; tmp_i++)
	{
		printf("%d ",*(tmp_ptr+tmp_i));
	
		if ((tmp_i+1)%8==0)
		{
			printf("\n");
		}
	}
	printf("\n");*/

	/*con_ptr=malloc(sizeof(int)*i);
	memcpy(con_ptr,tmp_ptr,i*sizeof(int));
	free(tmp_ptr);
	printf("maxArea=%d\n",maxArea(con_ptr,i));
	printf("maxArea=%d\n",maxArea3(con_ptr,i));*/
	/*for (tmp_i= 0; tmp_i<i; tmp_i++)
	{
		printf("%d ",*(con_ptr+tmp_i));
	
		if ((tmp_i+1)%8==0)
		{
			printf("\n");
		}
	}
	printf("\n");*/
	int ar[15000];
	int i=0;
	struct  timeval  start;
  	struct  timeval  end;
  	unsigned long timer;
	for (i = 0; i < 15000; ++i)
	{
		ar[i]=i;
	}

	gettimeofday(&start,NULL);
	printf("maxArea=%d\n", maxArea(ar,15000));
	gettimeofday(&end,NULL);
	timer = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
	printf("timer = %ld us\n",timer);

	gettimeofday(&start,NULL);
	printf("maxArea3=%d\n", maxArea3(ar,15000));
	gettimeofday(&end,NULL);
	timer = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
	printf("timer = %ld us\n",timer);
	return 0;
}
int maxArea(int* height, int heightSize) 
{
    int i=0,j=0;
    int val=0,tmp=0;
    for (i = 0; i < heightSize; i++)
    {
    	for (j=i+1;j<heightSize;j++)
    	{
    		tmp=(*(height+i))<(*(height+j))?(*(height+i)):(*(height+j));
    		tmp*=(j-i);
    		val=tmp>val?tmp:val;
    	}
    }
    return val;
}
int maxArea2(int* height, int heightSize) 
{
    int i=0,j=0;
    int val=0,tmp=0;
    for (i = heightSize-1; i >0; i--)
    {
    	for (j=0;i+j<heightSize;j++)
    	{
    		tmp=(*(height+i+j))<(*(height+j))?(*(height+i+j)):(*(height+j));
    		tmp*=i;
    		val=tmp>val?tmp:val;
    	}
    }
    return val;
}
int maxArea3(int* height, int heightSize) 
{
    int i=0,j=heightSize-1;
    int val=0,tmp=0;
    while(i!=j)
    {
    	if (*(height+i)>*(height+j))
    	{
    		tmp=(*(height+j))*(j-i);
    		j--;
    	}
    	else
    	{
    		tmp=(*(height+i))*(j-i);
    		i++;	
    	}
    	val=val>tmp?val:tmp;
    	// printf("i=%d j=%d val=%d\n",i,j,val);
    }
    return val;
}