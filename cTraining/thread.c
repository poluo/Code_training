#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void printids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu\n",s,(unsigned long)pid,(unsigned long)tid);
}

void *thread_fn1(void *arg)
{
    printids("new thread:");
    printf("thread 1 will exit\n");
    pthread_exit((void*)1);
}

void *thread_fn2(void *arg)
{
    printids("new thread:");
    printf("thread 2 will exit\n");
    pthread_exit((void*)2);
}
int main(int argc, char const *argv[])
{
    int err;
    int thread_id = 1;
    pthread_t tid1,tid2;
    void *tret;
    err = pthread_create(&tid1,NULL,thread_fn1,NULL);
    if(err !=0)
        printf("can not create thread,%d\n",thread_id);
    thread_id ++;
    err = pthread_create(&tid2,NULL,thread_fn2,NULL);
    if(err !=0)
        printf("can not create thread,%d\n",thread_id);


    err = pthread_join(tid1, &tret);
    if(err != 0)
        printf("thread join error\n");
    printf("thread 1 exit code %d\n",(int)tret);
    err = pthread_join(tid2, &tret);
    if(err != 0)
        printf("thread join error\n");
    printf("thread 2 exit code %d\n",(int)tret);

    return 0;
}
