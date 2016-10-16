#include <stdio.h>
#include <math.h>
#define MAX_LEN 100
#define SWAP(x,y) x=x+y;y=x-y;x=x-y;
char *itoa(int a);

int main(int argc, char const *argv[])
{
  int num=0;
  double num1=9.2,num2=3.3;
  SWAP(num1,num2);
  printf("%f %f\n",num1,num2);
  printf("Please in put your number:\n");
  scanf("%d",&num);
  printf("%s",reverse(itoa(num)));
  return 0;
}
char *itoa(int a)
{
  static char tmp_str[MAX_LEN];
  static int i=0;
  if (a/10)
  {
    itoa(a/10);
  }
  tmp_str[i]=a%10+'0';
  //printf("%c %d %d\n",tmp_str[i],a%10,i);
  i++;
  if (pow(10,i)>a)
  {
    return tmp_str;
  }
}
