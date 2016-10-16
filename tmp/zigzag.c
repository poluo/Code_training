/****
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
(you may want to display this pattern in a fixed font for better legibility)
P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"
******/

#include <stdio.h>
#include <string.h>
char* convert(char* s, int numRows);
int main(int argc, char const *argv[])
{
	char*c=convert("Apalindromeisaword,phrase,number,orothersequenceofunitsthatcanbereadthesamewayineitherdirection,withgeneralallowancesforadjustmentstopunctuationandworddividers.", 5);
	printf("convert is done\n");
	printf("%s\n", c);
	return 0;
}
char* convert(char* s, int numRows)
{
	int len=strlen(s);
	//printf("s length is :%d\n",len);
	int i=0,count_row=0,count_col=0,count_char=0;
	char fisrt_col_flag=0;
    char *tmp[numRows];//array of pointer ,char (*s1)[numRows] a pointer to array
    if (numRows<2)
    	return s;
    for (i = 0; i <=numRows; i++)
    {
    	tmp[i]=malloc(sizeof(char)*len);
    }
    //printf("malloc is done\n");
    while(1)
    {
    	if ((count_char+1)%(2*numRows-2)<=numRows&&(count_char+1)%(2*numRows-2)!=0)
    	{
    		fisrt_col_flag=1;
    	}
    	else
    		fisrt_col_flag=0;
    	if (fisrt_col_flag)//first col judged through count_char
    	{
    		for (i = 0; i < numRows; ++i)
    		{
    			//printf("count_char:%d\n",count_char);
	    		//printf("first col\n");
	    		///printf("count_row %d count_col %d\n", count_row,count_col);
	    		tmp[count_row][count_col]=s[count_char];
	    		count_row++;
	    		if (count_row>=numRows)
	    		{
	    			count_row=0;
	    		}
	    		count_char++;
	    		if (count_char>len)
	    			goto end;
    		}
    		count_col++;

    	}
    	else
    	{
    		//printf("count_char:%d\n",count_char);
    		//printf("not first col\n");
    		for (i = 0; i < numRows; i++)
    		{
    			//printf("i+count_col: %d  %d %d\n", i+count_row,i,count_col);
    			if ((i+count_col)%(numRows-1)==0)  // i stand for row
    			{
    				tmp[i][count_col]=s[count_char];//s[count_char]
    				count_char++;
    				if (count_char>len)
    					goto end;
    			}
    			else
    			{
    				tmp[i][count_col]=' '; //' '
    			}
    			//printf("%c \n", tmp[i][count_col]);
    		}
    		count_col++;
    	}
    	//getchar();
    }
end:
	//printf("goto end\n");
    for (i = 0; i < numRows; i++)
    {
       	printf("%s\n",tmp[i]);
    }
    //printf("end print\n");
    len=0;
    for (i = 0; i <numRows; i++)
    {
    	count_char=0;
    	while(tmp[i][count_char]!='\0')
    	{
    		//printf("i %d count_char %d %c\n",i,count_char,tmp[i][count_char] );
    		if (tmp[i][count_char]==' ')
    		{
    			;
    		}
    		else
    		{
    			tmp[numRows][len]=tmp[i][count_char];
    			len++;
    		}
    		count_char++;

    	}
    }
    tmp[numRows][len]='\0';
error:
	return tmp[numRows];
}
