#include <stdio.h>
#include <stdlib.h>

void my_exit1(void);
void my_exit2(void);

extern char **environ;
int main(int argc, char const *argv[])
{
    int i = 0;
    
    if(atexit(my_exit2) != 0)
    {
        printf("can not register my_exit2");
    }
    if(atexit(my_exit1) != 0)
    {
        printf("can not register my_exit1");
    }
    if(argc > 1)
    {
        for (i = 0; argv[i] != NULL; ++i)
        {
            printf("argv[%d]: %s\n",i,argv[i]);
        }
        printf("hello world\n");
        printf("main function is done\n");
    }
    else
    {
        printf("There is no more argument,except program name %s\n",argv[0]);
    }
    // for (i = 0; i < 5; ++i)
    // {
    //     printf("No%d environ=%s \n",i,environ[i]);
    // }
    printf("PWD %s\n",getenv("PWD"));
    
    
    exit(0);
}
void my_exit1()
{
    printf("first exit handler\n");
}
void my_exit2(void)
{
    printf("second exit handler\n");
}