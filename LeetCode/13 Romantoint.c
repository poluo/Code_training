int romanToInt(char* s) 
{
    char Roman[7]={'I','V','X','L','C','D','M'};
    int  Intnum[7]={1,5,10,50,100,500,1000};
    int i=0,count=0,last_count=0;
    int val=0;
    char c=0;
    while((c=*(s+i))!='\0')
    {
    	//printf("i=%d\n",i);
    	for (count = 0; count < 7; count++)
    	{
    		if (Roman[count]==c)
    		{
    			//printf("last_count=%d  count=%d\n",last_count,count);
    			if (last_count<count&&i!=0)
    			{
    				val+=Intnum[count]-2*Intnum[last_count];
    				break;
    			}
    			else
    			{
    				val+=Intnum[count];
    				break;
    			}
    		}
    	}
    	last_count=count;
    	i++;
    }
    return val;
}