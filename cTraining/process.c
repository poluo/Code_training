#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //for getenv setenv
extern char **environ;

int main()
{
    char **ep;
    int rv = 0;
    pid_t my_pid = 0, my_ppid = 0;
    my_pid = getpid();
    my_ppid = getppid();
    if((rv = clearenv()) == 0)
    {
        printf("clearenv success\n");
    }
    else
    {
        printf("clearenv failed\n");
    }
    printf("my pid =%d ppid = %d\n",my_pid,my_ppid);
    /*for(ep = environ;*ep!=NULL;ep++)
    {
        if(strstr(*ep,"NAME")!=NULL)
            printf("%s\n",*ep);
    }*/
    //检索环境变量中的单个值
    // printf("%s\n",getenv("NAME"));
    rv = setenv("NAME","TEST",1);
    if(rv == 0)
    {
        printf("setenv success\n");
        printf("%s\n",getenv("NAME"));
    }
    else
    {
        printf("setenv failed,rv = %d\n",rv);
    }
    return 0;
}
