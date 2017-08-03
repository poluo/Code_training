#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> // for getopt
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>

#define SOCKET_CLIENT_PORT   5001
#define SOCKET_SERVER_PORT   5001
#define MAX_CONTENT_LEN     1024
#define RECV_MAX_LEN        (MAX_CONTENT_LEN+10)
typedef struct message
{
    int id;
    char content[MAX_CONTENT_LEN];
}message_struct;

char *client_ip = "127.0.0.1";
char *server_ip = "127.0.0.1";

void print_err(const char *mess)
{
    extern int errno;
    printf("%s,and errno =%d\n",mess,errno);
    exit(EXIT_FAILURE);
}

int fillup_message(message_struct *info_ptr,char *text)
{
    static int message_id = 0;
    message_id += 1;
    info_ptr->id = message_id;
    strcpy(info_ptr->content,text);
    return 0;
}
void play_server()
{
    int sockfd,connection_fd;
    int recv_len,resp_len;
    char buf[RECV_MAX_LEN];
    message_struct info;
    struct sockaddr_in server_addr;
    //init socket
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        print_err("init socket failed");
    }
    // init sockaddr_in
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(SOCKET_SERVER_PORT);
    
    // bind socket
    if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
    {
        print_err("bind socket error");
    }
    // listen
    if(listen(sockfd,2) == -1)
    {
        print_err("listen failed");
    }

    //accept and receive mesaage
    while(1)
    {
        if((connection_fd = accept(sockfd,(struct sockaddr *)NULL,NULL)) < 0)
        {
            printf("accept failed\n");
            continue;
        }
        recv_len = recv(connection_fd,buf,RECV_MAX_LEN,0);
        memcpy(&info,buf,recv_len);
        printf("receive message %d %s\n",info.id,info.content);
        memset(buf,0,recv_len);
        strcpy(buf,"hello,client");
        if(fillup_message(&info,buf))
        {
            print_err("fillup message error");
        }
        if((resp_len = send(connection_fd,&info,sizeof(info),0)) < 0)
        {
            print_err("send response mesaage error");
        }
        printf("send response message success\n");
        close(connection_fd);
    }
    close(sockfd);
}

void play_client()
{
    int sockfd;
    int send_len;
    int recv_len;
    message_struct info;
    char buf[RECV_MAX_LEN];
    struct sockaddr_in server_addr;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        print_err("init socket failed");
    }
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(client_ip);
    server_addr.sin_port = htons(SOCKET_CLIENT_PORT);

    if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
    {
        print_err("connect socket error");
    }
    strcpy(buf,"hello world");
    if(fillup_message(&info,buf))
    {
        print_err("fillup message error");
    }
    if((send_len = send(sockfd,&info,sizeof(info),0)) < 0)
    {
        print_err("send message failed");
    }
    printf("send message success,len = %d,id =%d,content =%s\n", send_len,info.id,info.content);
    recv_len = recv(sockfd,buf,RECV_MAX_LEN,0);
    if(recv_len < 0)
    {
        print_err("receive response message failed");
    }
    memcpy(&info,buf,recv_len);
    printf("receive response message %d %s\n",info.id,info.content);
    close(sockfd);
}

int mygetopt(int argc,char *argv[])
{
    int ch;
    char *rvalue = NULL;
    while((ch = getopt(argc,argv,"hr:")) != -1)
    {
        switch(ch)
        {
            case 'r':
                rvalue = optarg;
                if((strcmp(rvalue,"s") == 0 )||(strcmp(rvalue,"S") == 0))
                    return 1;
                if((strcmp(rvalue,"c") == 0 )||(strcmp(rvalue,"C") == 0))
                    return 2;
                printf("argument must be m\\M or s\\S \n");
                break;

            case 'h':
                printf("help text\n");
                break;

            default:
                return -1;
                break;
        }
    }   
}

int main(int argc,char *argv[])
{
    int role = mygetopt(argc,argv);

    if(role == 2)
    {
        puts("This is a socket Client");
        play_client();
    }
    else if(role == 1)
    {
        puts("This is a socket Server");
        play_server();
    }
    else
    {
        print_err("Nither Server or Client");
    }
    return 0;
}
