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
#include <malloc.h>
#include <time.h>
#include <sys/time.h>

#define SOCKET_CLIENT_PORT   5001
#define SOCKET_SERVER_PORT   5001
#define MAX_CONTENT_LEN     1024
#define RECV_MAX_LEN        (MAX_CONTENT_LEN + 4)

typedef struct message
{
    int id;
    time_t time_val;
    char *content;
}__attribute__((packed)) message_struct;

char *client_ip = "127.0.0.1";
char *server_ip = "127.0.0.1";
int USER_ID = 0;
void print_err(const char *mess)
{
    extern int errno;
    printf("%s,and errno =%d\n",mess,errno);
    exit(EXIT_FAILURE);
}

char *populate_message(message_struct *info_ptr,char *text)
{
    static char *stream;

    info_ptr->id = USER_ID;
    info_ptr->time_val = time(NULL);
    info_ptr->content = malloc(strlen(text));
    if(info_ptr == NULL)
    {
    	print_err("populate message failed,because of malloc content failed");
    	return NULL;
    }
    strcpy(info_ptr->content,text);

    stream = realloc(stream,sizeof(*info_ptr));

    if(stream == NULL)
    {
    	print_err("populate message failed,because of calloc stream failed");
    	return NULL;
    }
    memcpy(stream,&(info_ptr->id),sizeof(int));
    memcpy(stream+offsetof(message_struct,time_val),&(info_ptr->time_val),sizeof(time_t));
    strcpy(stream+offsetof(message_struct,content),info_ptr->content);
    return stream;
}

int decode_message(char *stream,int len,message_struct *info_ptr)
{
    memcpy(&(info_ptr->id),stream,sizeof(int));
    memcpy(&(info_ptr->time_val),stream + offsetof(message_struct,time_val),sizeof(time_t));
    info_ptr->content = malloc(len - sizeof(int) - sizeof(time_t));
    memcpy(info_ptr->content,stream + offsetof(message_struct,content),len - sizeof(int) - sizeof(time_t));
}

int  print_received_message(int connection_fd)
{
	char buf[RECV_MAX_LEN];
	int recv_len;
	message_struct *info = (message_struct *)malloc(sizeof(message_struct));
	recv_len = recv(connection_fd,buf,RECV_MAX_LEN,0);
	if(recv_len > 0)
	{
		decode_message(buf,recv_len,info);
		if(strcmp(info->content,"quit") == 0)
		{
			printf("user %d quit connection\n", info->id);
			return 1;
		}
	    printf("user:%d time: %s",info->id,ctime(&info->time_val));
	    printf("%s",info->content);
	}
    
    free(info);
    return 0;
}

int init_server(int domain,int type,int protocal,const struct sockaddr_in *addr, socklen_t alen, int qlen)
{
	int sockfd;
	if((sockfd = socket(domain,type,protocal)) < 0)
    {
        printf("init socket failed\n");
        return -1;
    }
     // bind socket
    if(bind(sockfd,(struct sockaddr*)addr,alen) < 0)
    {
        print_err("bind socket error");
    }
    // listen
    if(listen(sockfd,qlen) == -1)
    {
        print_err("listen failed");
    }
    return sockfd;
}
void play_server()
{
    int sockfd,connection_fd;
    int resp_len;
    
    struct sockaddr_in server_addr;

    // init sockaddr_in
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(SOCKET_SERVER_PORT);
    sockfd = init_server(AF_INET,SOCK_STREAM,0,&server_addr,sizeof(server_addr),5);

    //accept and receive mesaage
    while(1)
    {
        if((connection_fd = accept(sockfd,(struct sockaddr *)NULL,NULL)) < 0)
        {
            printf("accept failed\n");
            continue;
        }

        while(! print_received_message(connection_fd))
        {
        	sleep(0.5);
        }
        close(connection_fd);	

        
    }
    close(sockfd);
}

int connect_retry(int domain,int type,int protocal,const struct sockaddr_in *addr, socklen_t alen)
{
	int sockfd,i;
	#define MAX_NUM_RETRY 5
	for(i = 0; i < MAX_NUM_RETRY; i++)
	{
		if((sockfd = socket(domain,type,protocal)) < 0)
	    {
	        printf("init socket failed\n");
	        return -1;
	    }
	    if(connect(sockfd,(const struct sockaddr *)addr,alen) == 0)
	    {
	    	return sockfd;
	    }
	    printf("connect socket error\n");
        close(sockfd);
        sleep(1);
	}
	return -1;
}
int send_message(int sockfd,message_struct *info,char *text)
{
	char *stream;
	int send_len;
	if((stream = populate_message(info,text)) == NULL)
    {
        print_err("fillup message error");
    }
    if((send_len = send(sockfd,stream,malloc_usable_size(stream),0)) < 0)
    {
        print_err("send message failed");
    }
    #if 0
    printf("send message success,len = %d,id = %d,time_val = %d ,content = %s\n", send_len,info->id,info->time_val,info->content);
	#endif
}
void play_client()
{
    
    int recv_len;
    int sockfd;
    message_struct *info = (message_struct *)malloc(sizeof(message_struct));
    char buf[RECV_MAX_LEN];
    

    struct sockaddr_in server_addr;
    
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(client_ip);
    server_addr.sin_port = htons(SOCKET_CLIENT_PORT);

    sockfd = connect_retry(AF_INET,SOCK_STREAM,0,&server_addr,sizeof(server_addr));
    if(sockfd < 0)
    {
    	print_err("get socket fd fialed");
    }
    printf("please input message:\n");
    while(fgets(buf,sizeof(buf),stdin)!= NULL && strcmp(buf,"quit") != 0)
    {
    	send_message(sockfd,info,buf);
    	printf("please input message:\n");
    }
    if(strcmp(buf,"quit") == 0)
    {
    	send_message(sockfd,info,buf);
    }
    
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
               	{
               		USER_ID = 1;
                    return 1;
               	}
                if((strcmp(rvalue,"c") == 0 )||(strcmp(rvalue,"C") == 0))
                {
                	USER_ID = 2;
                    return 2;
                }
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
