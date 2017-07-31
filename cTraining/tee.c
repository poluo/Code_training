#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  

#define  BUF_SIZE 1024
void copy_file(const char* des)
{
    int num_read =0, num_write = 0;
    //文件访问权限 rw-rw-rw
    mode_t file_perms = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
    int des_fd = open(des,O_WRONLY|O_CREAT|O_TRUNC,file_perms);
    if(des_fd == -1)
    {
        printf("error is %s\n",strerror(errno));
    }
    char buf[BUF_SIZE];
    while((num_read = read(STDIN_FILENO,buf,BUF_SIZE)) > 0)
    {
        num_write = write(des_fd,buf,num_read);
        if(num_read != num_write)
        {
            printf("Could not write all buf\n");
        }
    }
    close(des_fd);
}
void error_usage()
{
    printf("Usage illeage\n");
    printf("w/r text/num\n");
    exit(EXIT_FAILURE);
}
int main(int argc,char *argv[])  
{  

    printf("source file %s\n", argv[1]);
    copy_file(argv[1]);

    return 0;  
} 
