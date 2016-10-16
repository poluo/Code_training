#include <stdio.h>
#define FN_NAME(id) "fn_"#id"_proc"
typedef void(*fn)(void);
void fn_0_proc(void)
{
 printf("I am 0\n");
}

void fn_1_proc(void)
{
 printf("I am 1\n");
}

void fn_2_proc(void)
{
 printf("I am 2\n");
}
fn fn_hndl[3];

int main(int argc, char *argv[])
{
 int id = 0;
// for(id = 0; id < 3; id++)
//{
 // printf("FN_NAME(%d)",id);
  fn_hndl[0]=(fn)FN_NAME(0);
  fn_hndl[1]=(fn)FN_NAME(1);
  fn_hndl[2]=(fn)FN_NAME(2);
//}
 for(id = 0; id < 3; id++)
 {
  printf("%s\n",fn_hndl[id]);
  //fn_hndl[id]();
  if(strcmp(fn_hndl[id],"fn_0_proc")==0)
     fn_0_proc();
  else if(strcmp(fn_hndl[id],"fn_1_proc")==0)
     fn_1_proc();
  else if(strcmp(fn_hndl[id],"fn_2_proc")==0)
     fn_2_proc();
  
 }
return 0;
}
