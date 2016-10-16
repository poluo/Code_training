#include <ctype.h>
#include <stdio.h>
#include <math.h>
#define MAX_LEN 100
double atof2(char s[]);
int main(int argc, char const *argv[])
{
  
  char *my_str1=NULL;
  char *tmp_str=(char *)malloc(sizeof(char)*MAX_LEN);
  char tmp_char=0;
  int i=0;

  printf("Please in put your string,first\n");
  while((tmp_char=getchar())!=EOF&&tmp_char!='\n')
  {
    tmp_str[i]=tmp_char;
    i++;
  }
  tmp_str[i]='\0';

  my_str1=(char *)malloc(sizeof(char)*i);
  if (my_str1==NULL)
  {
    printf("my_str1 malloc failed!\n");
  }
  memcpy(my_str1,tmp_str,i);
  free(tmp_str);
  printf("first string:%s\n",my_str1);
  printf("%f\n", atof2(my_str1));
  return 0;
}
double atof2(char s[])
{
  double val, power;
  int i, sign,flag;
  for (i = 0; isspace(s[i]); i++)  /* skip white space */
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');
  if (s[i] == '.')
  {
    i++;
    for (power = 1.0; isdigit(s[i]); i++) 
    {
      val = 10.0 * val + (s[i] - '0');
      power *= 10;
    }
    printf("val:%f power:%f\n",val,power);
    return sign * val / power;
  }
  else if (s[i]=='E'||s[i]=='e')
  {
    i++;
    flag=(s[i]=='-')?-1:1;
    i++;
    for (power = 0.0; isdigit(s[i]); i++)
      power = 10.0 * power + (s[i] - '0');
    printf("val:%f power:%f\n",val,power);
    power=pow(10,power);
    if (flag==-1)
    {
      return val*sign/power;
    }
    //return (flag==-1)?(val*sign/power):(val*sign*power);
    return val*sign*power;
  }
}