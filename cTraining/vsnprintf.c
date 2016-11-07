/**********************************************************
 * Author        : poluo
 * Email         : xxx@email.com
 * Create time   : 2016-11-03 15:09
 * Last modified : 2016-11-03 15:09
 * Filename      : vsnprintf.c
 * Description   :int vsnprintf (char * s, size_t n, const char * format, va_list arg );
 * Write formatted data from variable argument list to sized buffer
 * The number of characters that would have been written,If an encoding error occurs, a negative number is returned 
 * *******************************************************/
/* vsnprintf example */
#include <stdio.h>
#include <stdarg.h>

void PrintFError ( const char * format, ... )
{
  char buffer[256];
  va_list args;
  va_start (args, format);
  printf("%d chars have written into buffer\n",vsnprintf (buffer,256,format, args));
  perror (buffer);
  va_end (args);
}

int main ()
{
   FILE * pFile;
   char szFileName[]="myfile.txt";

   pFile = fopen (szFileName,"r");
   if (pFile == NULL)
     PrintFError ("Error opening '%s'",szFileName);
   else
   {
     // file successfully open
     fclose (pFile);
   }
    return 0;
}

