#ifndef _SOCKET_H
#define _SOCKET_H

#include "linux_info.h"

#define SOCKET_CLIENT_PORT   5001
#define SOCKET_SERVER_PORT   5001
#define MAX_CONTENT_LEN     1024
#define RECV_MAX_LEN        (MAX_CONTENT_LEN + 4)

typedef struct message
{
    int id;
    time_t time_val;
    char *content;
	meminfo mem_info;
	cpuinfo cpu_info;
	process_info pro_info;
}__attribute__((packed)) message_struct;

void play_client();
void play_server();

#endif