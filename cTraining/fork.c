#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globvar = 99;
char buf[] = "a write to stdout\n";

int main(int argc, char const *argv[])
{
    int     var = 88;
    pid_t   pid;

    if (write(STDOUT_FILENO,buf,sizeof(buf)-1) != sizeof(buf) -1)
        printf("write error\n");
    printf("now begain fork()\n");

    if((pid = fork()) < 0)
    {
        printf("fork error\n");
    }
    else if(pid == 0)
    {
        globvar ++;
        var ++;
        printf("I am child process\n");
    }
    else
    {
        printf("I am parent process\n");
        wait();
    }
    printf("pid  = %d,ppid =%d, globvar = %d, var =%d\n", getpid(),getppid(),globvar,var);
    exit(0);
}
