#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  

#define  BUF_SIZE 1024
int write_file(const char *filename,const char *text)
{
    //用读写追加方式打开一个文件 ,若文件不存创建文件
    int fd=open(filename,O_RDWR|O_CREAT|O_APPEND);  
    if(fd==-1)  
    {  
        printf("error is %s\n",strerror(errno));  
    }  
    else  
    {  
        //打印文件描述符号  
        printf("success fd = %d\n",fd);  
        char *buf = malloc(sizeof(text)+1);  
        memset(buf,0,sizeof(buf));
        strcpy(buf,text);  
        write(fd,buf,strlen(buf)); 
        close(fd);  
    }  
}

int read_file(const char *filename)
{
    //用只读方式打开一个文件
    int num_read = 0;
    int fd=open(filename,O_RDONLY);  
    if(fd==-1)  
    {  
        printf("error is %s\n",strerror(errno));  
    }  
    else  
    {  
        //打印文件描述符号  
        printf("success fd = %d\n",fd);  
        char buf[BUF_SIZE];  
        while((num_read = read(fd,buf,BUF_SIZE)) > 0)
        {
            printf("%s\n",buf);
            memset(buf,0,BUF_SIZE);
        }
        close(fd);  
    }  
}
void copy_file(const char* src, const char* des)
{
    int num_read =0, num_write = 0;
    int src_fd = open(src,O_RDONLY);
    //文件访问权限 rw-rw-rw
    mode_t file_perms = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
    int des_fd = open(des,O_WRONLY|O_CREAT|O_TRUNC,file_perms);
    char buf[BUF_SIZE];
    num_write = lseek(src_fd,10,SEEK_CUR);
    printf("offset %d\n",num_write);
    while((num_read = read(src_fd,buf,BUF_SIZE)) > 0)
    {
        num_write = write(des_fd,buf,num_read);
        if(num_read != num_write)
        {
            printf("Could not write all buf\n");
        }
    }
    close(src_fd);
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
    if(argc<2)
    {
        error_usage();

    }
    if(strncmp(argv[1],"w",1) == 0)
    {
        printf("wirte file\n");
        write_file(argv[2],argv[3]);
        exit(EXIT_SUCCESS);
    }
    else if(strncmp(argv[1],"r",1) == 0)
    {
        printf("read file\n");
        read_file(argv[2]);
    }
    else if(strncmp(argv[1],"cp",2) == 0)
    {
        printf("source file %s\n", argv[2]);
        printf("destination file %s\n", argv[3]);
        copy_file(argv[2],argv[3]);
    }
    
    return 0;  
} 
