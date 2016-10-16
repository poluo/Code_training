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
char *convert2(char *s, int nRows);
int main(int argc, char const *argv[])
{
	char *c=convert("Apalindrome",3);
	printf("convert is done\n");
	printf("%s\n", c);
	return 0;
}
char* convert(char* s, int numRows) 
{
	int len=strlen(s);
	//printf("s length is :%d\n",len);
	int i=0,count_row=0,count_col=0,count_char=0;
    char *tmp[numRows];//array of pointer ,char (*s1)[numRows] a pointer to array 
    if (numRows<2)
    	return s;
    for (i = 0; i <numRows+1; i++)
    {
    	tmp[i]=(char *)malloc(sizeof(char)*len);
    }
    //printf("malloc is done\n");
    while(1)
    {
    	if ((count_char+1)%(2*numRows-2)<=numRows&&(count_char+1)%(2*numRows-2)!=0)//first col judged through count_char
    	{
    		for (i = 0; i < numRows; i++)
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
char *convert2(char *s, int nRows)
{
    if ((NULL == s) | (nRows < 1))
    {
        return NULL;
    }
    // + 1 for NIL or '\0' in the end of a string
    const size_t len = strlen(s);
    char* output = (char*) malloc(sizeof(char) * ( len + 1));
    char* head = output;
    int row;
    unsigned int index;
    output[len] = '\0';
    if ( 1 == nRows )
    {
        return strcpy(output, s);
    }
    for (row = 0; row < nRows; ++row)
    {
        //processing row by row using (2nRows-2) rule
        for (index = row; index < len; index += 2*nRows-2)
        {
            // if it is the first row or the last row, then this is all
            *output++ = s[index];
            // otherwise, there are middle values, using (2nRows-2-2*row) rule
            // notice that nRows-1 is the last row
            if ( (row>0)&(row<nRows-1) & ((index+2*nRows - 2 - 2*row) < len))
            {
                *output++ = s[index+2*nRows - 2 - 2*row];
            }
        }
    }
    return head;
}