/**********************************************************
 * Author        : cplusplus.com
 * Email         : xxx@email.com
 * Create time   : 2016-11-03 14:55
 * Last modified : 2016-11-03 14:55
 * Filename      : variable_arguments_example.c
 * Description   : 
 * *******************************************************/

#include <stdio.h>      /* printf */
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

void PrintFloats (int n, ...)
{
  int i;
  double val;
  printf ("Printing floats:");
  va_list vl;
  va_start(vl,n);
  for (i=0;i<n;i++)
  {
    val=va_arg(vl,double);
    printf (" [%.2f]",val);
  }
  va_end(vl);
  printf ("\n");
}

int main ()
{
  PrintFloats (3,3.14159,2.71828,1.41421);
  return 0;
}
