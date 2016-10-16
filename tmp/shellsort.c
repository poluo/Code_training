void shellsort(int v[],int n)
{
  int gap,i,j,temp;

  for (gap = n/2; gap >0; gap/=2) 
  {
    for (i = 0; i < count; i++) 
    {
      for (j = i-gap; j>0 &&v[j]>v[j+gap]; j-=gap) 
      {
        v[j]+=v[j+gap];
        v[j+gap]=v[j]-v[j+gap];
        v[j]=v[j]-v[j+gap];
        /*
        tmp=v[j]；
        v[j]=v[j+gap];
        v[j+gap]=temp;
        */
      }
    }
  }
}
