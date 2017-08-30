#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include "socket.h"

unsigned int operation_mode = 0xFFFFFFFF;
char *client_ip = "127.0.0.1";
char *server_ip = "127.0.0.1";
int USER_ID = 0;

meminfo memory;
cpuinfo cpu;
process_list_info process_list;

void scan(void)
{
	get_memory_info(&memory);
	get_cpu_info(&cpu);
	get_process_list_info(&process_list);
}

char *populate_message(message_struct *info_ptr,char *text)
{
    static char *stream;

    info_ptr->id = USER_ID;
    info_ptr->time_val = time(NULL);
    info_ptr->content = malloc(strlen(text));
    if(info_ptr == NULL)
    {
    	PINFO("populate message failed,because of malloc content failed,%s\n",strerror(errno));
    	return NULL;
    }
    strcpy(info_ptr->content,text);

    stream = realloc(stream,sizeof(*info_ptr));

    if(stream == NULL)
    {
    	PINFO("populate message failed,because of calloc stream failed,%s\n",strerror(errno));
    	return NULL;
    }
    memcpy(stream, &(info_ptr->id), sizeof(int));
    memcpy(stream + offsetof(message_struct,time_val), &(info_ptr->time_val), sizeof(time_t));
    strcpy(stream + offsetof(message_struct,content), info_ptr->content);
	memcpy(stream + offsetof(message_struct,mem_info),&memory);
	memcpy(stream + offsetof(message_struct,cpu_info),&cpu);
	memcpy(stream + offsetof(message_struct,pro_info),&process_list);
    return stream;
}

int decode_message(char *stream,int len,message_struct *info_ptr)
{
    memcpy(&(info_ptr->id), stream, sizeof(int));
    memcpy(&(info_ptr->time_val), stream + offsetof(message_struct, time_val), sizeof(time_t));
    info_ptr->content = malloc(len - sizeof(int) - sizeof(time_t));
    memcpy(info_ptr->content, stream + offsetof(message_struct, content) ,len - sizeof(int) - sizeof(time_t));
	memcpy(info_ptr->mem_info, stream + offsetof(message_struct, mem_info),sizeof(meminfo));
	memcpy(info_ptr->cpu_info, stream + offsetof(message_struct, cpu_info),sizeof(cpuinfo));		
	memcpy(info_ptr->pro_info, stream + offsetof(message_struct, pro_info),sizeof(process_info));
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
			PINFO("user %d quit connection\n", info->id);
			return 1;
		}
	    PINFO("user:%d time: %s\n",info->id,ctime(&info->time_val));
	    PINFO("%s\n",info->content);
		PINFO("cpu model %s,cores %d\n",info->cpu_info.model,info->cpu_info.cores);
	}
    free(info);
    return 0;
}

int init_server(int domain,int type,int protocal,const struct sockaddr_in *addr, socklen_t alen, int qlen)
{
	int sockfd;
	if((sockfd = socket(domain,type,protocal)) < 0)
    {
        PINFO("init socket failed,%s\n",strerror(errno));
        return -1;
    }
     // bind socket
    if(bind(sockfd,(struct sockaddr*)addr,alen) < 0)
    {
        PINFO("bind socket error,%s\n",strerror(errno));
    }
    // listen
    if(listen(sockfd,qlen) == -1)
    {
        PINFO("listen failed,%s\n",strerror(errno));
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
            PINFO("accept failed\n");
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
        PINFO("fillup message error,%s\n",strerror(errno));
    }
    if((send_len = send(sockfd,stream,malloc_usable_size(stream),0)) < 0)
    {
        PINFO("send message failed,%s\n",strerror(errno));
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
    	PINFO("get socket fd fialed,%s\n",strerror(errno));
    }
	
	//get cpu,memory,process info
	scan();
	
    PINFO("please input message:\n");
    while(fgets(buf,sizeof(buf),stdin)!= NULL && strcmp(buf,"quit") != 0)
    {
    	send_message(sockfd,info,buf);
    	PINFO("please input message:\n");
    }
    if(strcmp(buf,"quit") == 0)
    {
    	send_message(sockfd,info,buf);
    }
    //draw_init();
   	//draw_cpu();
    //draw_done();
    close(sockfd);
}
