#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void pr_exit(int status)
{
  if (WIFEXITED(status))
  {
    printf("Normal exit,status = %d\n",WEXITSTATUS(status));
  }
  else if (WIFSIGNALED(status)) {
    printf("abnormal exit,signal number = %d\n", WTERMSIG(status));
  }
  else if (WIFSTOPPED(status)){
    printf("child stopped, signal number = %d\n",WSTOPSIG(status));
  }
}
int main(int argc, char const *argv[]) {
  pid_t pid;
  int status;

  if((pid = fork()) < 0)
  {
      printf("fork error\n");
  }
  else if(pid == 0)
  {
      exit(7); /*child process exit*/
  }

  if (wait(&status) != pid) {
    printf("wait error in eixt(7)\n");
  }
  pr_exit(status);

  if((pid = fork()) < 0)
  {
      printf("fork error\n");
  }
  else if(pid == 0)
  {
      abort(); /*child process abort,generates SIGABRT*/
  }

  if (wait(&status) != pid) {
    printf("wait error in abort\n");
  }
  pr_exit(status);


  if((pid = fork()) < 0)
  {
      printf("fork error\n");
  }
  else if(pid == 0)
  {
      status /= 0; /*child process abort,generates SIGABRT*/
  }

  if (wait(&status) != pid) {
    printf("wait error in divide 0\n");
  }
  pr_exit(status);


  return 0;
}
