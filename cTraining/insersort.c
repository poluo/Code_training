#include <stdio.h>
#include <stdlib.h>
void shell_insert_sort(int a[],int length,int k)
{
	int i=0,j=0;
	int tmp=0;

	for (i = k; i < length ; ++i)
	{
		if (a[i]<a[i-k])
		{
			tmp=a[i];
			j=i-k;
			while((tmp<a[j])&&(j>=0))
			{
				a[j+k]=a[j];
				j-=k;
			}
			a[j+k]=tmp;
		}
	}
}
void shell_sort(int a[],int length)
{
	int k=length/2;
	int i=0;

	while(k >=1)
	{
		shell_insert_sort(a,length,k);
		k/=2;
	}
	
	for (i = 0; i < length; ++i)
	{
		printf("%d \n", a[i]);
	}
}
void inser_sort(int a[],int length)
{
	int i=0,j=0;
	int tmp=0;

	for (i = 1; i < length ; ++i)
	{
		if (a[i]<a[i-1])
		{
			tmp=a[i];
			j=i-1;
			while((tmp<a[j])&&(j>=0))
			{
				a[j+1]=a[j];
				j--;
			}
			a[j+1]=tmp;
		}
	}
}
void select_sort(int a[],int length)
{
	int i = 0,j=0;
	int tmp_val=0,tmp_index=0;

	for (i = 1; i < length; ++i)
	{
		tmp_val=a[i];
		tmp_index=i;
		j=i+1;

		while(j<length)
		{
			if (a[j]<tmp_val)
			{
				tmp_val=a[j];
				tmp_index=j;
			}
			j++;
		}

		if (tmp_val<a[i-1])
		{
			a[tmp_index]=a[i-1];
			a[i-1]=tmp_val;
		}
	}
}
int bubble_sort(int a[],int length)
{
	int i=0,j=0;
	int tmp;
	for (i = 0; i < length-1; ++i)
	{
		for (j = 0; j < length-i-1; ++j)
		{
			if (a[j] > a[j+1])
			{
				tmp=a[j+1];
				a[j+1]=a[j];
				a[j]=tmp;
			}
		}
	}
	

}

int bubble_improve_sort(int a[],int length)
{
	int i=length-1,j=0;
	int tmp;
	int pos=0;

	while(i)
	{
		pos=0;
		for (j = 0; j < i; ++j)
		{
			if (a[j] > a[j+1])
			{
				tmp=a[j+1];
				a[j+1]=a[j];
				a[j]=tmp;
				pos=j;
			}
		}
		i=pos;
	}

	for (i = 0; i < length; ++i)
	{
		printf("%d \n", a[i]);
	}

}

int bubble_improve2_sort(int a[],int length)
{
	int i=0,tmp=0;
	int low=0,high=length-1;

	while(low<high)
	{
		for (i = low; i < high; ++i)
		{
			if (a[i]>a[i+1])
			{
				tmp=a[i+1];
				a[i+1]=a[i];
				a[i]=tmp;
			}
		}

		high--;

		for (i = high; i >low; i--)
		{
			if (a[i]<a[i-1])
			{
				tmp=a[i-1];
				a[i-1]=a[i];
				a[i]=tmp;
			}
		}

		low++;
	}

	for (i = 0; i < length; ++i)
	{
		printf("%d\n",a[i]);
	}
}
void merge(int *r,int *rf, int i, int m, int n)  
{  
    int j,k;  
    for(j=m+1,k=i; i<=m && j <=n ; ++k)
    {  
        if(r[j] < r[i]) 
        	rf[k] = r[j++];  
        else 
        	rf[k] = r[i++];  
    }  
    while(i <= m)  rf[k++] = r[i++];  
    while(j <= n)  rf[k++] = r[j++]; 
}
void merge_sort(int a[],int length)
{
	int *b=malloc(sizeof(int)*length);
	int *tmp;
	int i=0;
	int step=1;
	int s=0;
	while(step<length)
	{
		i=0;
		while(i+step*2<length)
		{
			merge(a,b,i,i+step-1,i+step*2-1);
			i+=2*step;
		}
		if (i+step<length)
		{
			merge(a,b,i,i+step-1,length-1);
		}
		step*=2;
		tmp=b;
		b=a;
		a=tmp;
	}
	for (i = 0; i < length; ++i)
	{
		printf("%d\n",tmp[i]);
	}

} 
int swap_value(int a[], int i, int j)
{
	int tmp=0;

	tmp=a[i];
	a[i]=a[j];
	a[j]=tmp;

	return 0;
}
void quick_sort(int a[], int left, int right)
{
	int i=0,last=0;
	if(left>=right)
		return;
	swap_value(a,left,(left+right)/2);
	last=left;
	for (i = left+1; i <=right; i++)
	{
		if ((a[i]-a[left])<0)
		{
			swap_value(a,++last,i);
		}
	}
	swap_value(a,left,last);
	quick_sort(a,left,last-1);
	quick_sort(a,last+1,right);
}
int main(int argc, char const *argv[])
{
	int a[8] = {8,6,5,2,5,8,9,6};
	int b[8];
	quick_sort(a,0,7);
	int i=0;
	for (i = 0; i < 8; ++i)
	{
		printf("%d \n", a[i]);
	}

	return 0;
}