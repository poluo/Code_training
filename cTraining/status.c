#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PROC_DIR "/proc"
#define FILE_NAME_MAX 50
#define PROC_LINE_LENGTH 512

typedef enum
{
	sleeping,
	running,
	other
}status_enum;

typedef struct process_status
{
	char *name;
	status_enum status;
	pid_t pid;
	pid_t ppid;
	char * vmsize;
}process_status;

void print_err(const char *mess)
{
	extern int errno;
	printf("%s,and errno =%d\n",mess,errno);
	exit(EXIT_FAILURE);
}
static size_t xread(int fd, void *buf,size_t count)
{
	size_t already_read = 0;
	while(1)
	{
		size_t res = read(fd,buf,count);
		if(res == -1)
		{
			return -1;
		}
		if(res > 0)
		{
			buf = ((char *)buf) + res;
			count -= res;
			already_read += res;
		}
		if(res ==0 || count == 0)
		{
			return already_read;
		}
	}
}
void lstrip(char *s)
{
	char *p = s;
	while((*p == ' ') || (*p == '\t'))
	{
		*p++;
	}
	strcpy(s,p);
}
void populate_status(char *str,process_status *status)
{
	char *tmp;
	if(strncmp(str,"Name",4) == 0)
	{
		tmp = malloc(sizeof(str)-4);
		strcpy(tmp,str+5);
		lstrip(tmp);
		status->name = malloc(sizeof(tmp));
		strcpy(status->name,tmp);
		free(tmp);
		printf("status->name %s\n",status->name);
	}
	else if(strncmp(str,"State",5) == 0)
	{
		tmp = malloc(sizeof(str)-5);
		strcpy(tmp,str+6);
		lstrip(tmp);
		if(strstr(tmp,"sleeping") != NULL)
		{
			status->status = sleeping;
		}
		else if(strstr(tmp,"running") != NULL)
		{
			status->status = running;
		}
		else 
		{
			status->status = other;
		}
		free(tmp);
		printf("status->status %d\n",status->status);
	}
	else if(strncmp(str,"Pid",3) == 0)
	{
		tmp = malloc(sizeof(str)-3);
		strcpy(tmp,str+4);
		lstrip(tmp);
		status->pid = atoi(tmp);
		free(tmp);
		printf("status->pid %d\n",status->pid);
	}
	else if(strncmp(str,"PPid",4) == 0)
	{
		tmp = malloc(sizeof(str)-4);
		strcpy(tmp,str+5);
		lstrip(tmp);
		status->ppid = atoi(tmp);
		free(tmp);
		printf("status->ppid %d\n",status->ppid);
	}
	else if(strncmp(str,"VmSize",6) == 0)
	{
		tmp = malloc(sizeof(str)-6);
		strcpy(tmp,str+7);
		lstrip(tmp);
		status->vmsize = (char *)malloc(sizeof(tmp));
		strcpy(status->vmsize,tmp);
		free(tmp);
		printf("status->vmsize %s\n",status->vmsize);
	}
}
void proc_status_file(char *buf)
{
	char *pch;
	char *str;
	process_status this;
	pch = strtok(buf,"\n");
	while(pch != NULL)
	{
		// printf("%s\n", pch);
		populate_status(pch,&this);
		pch = strtok(NULL,"\n");
	}
	
}
int main(int argc, char const *argv[])
{
	DIR *mydir = opendir(PROC_DIR);
	struct  dirent *mydir_des = NULL;
	char filename[FILE_NAME_MAX]={0};
	if(mydir == NULL)
	{
		print_err("PROC DIR can not open");
	}
	while((mydir_des = readdir(mydir)) != NULL)
	{
		if(mydir_des->d_type & DT_DIR) // this mean child is a dir
		{
			if(atoi(mydir_des->d_name)) // PID
			{
				sprintf(filename,"%s/%s/status",PROC_DIR,mydir_des->d_name);
				printf("filename %s\n", filename);
				int fd = open(filename,O_RDONLY);
				if(fd == -1)
				{
					printf("filename %s open failed\n",filename);
				}
				else
				{
					// printf("success open filename %s fd %d\n",filename,fd);
					char buf[PROC_LINE_LENGTH+1];
					size_t rres = xread(fd,buf,PROC_LINE_LENGTH);
					close(fd);
					if(rres < 1)
					{
						print_err("filename read failed");
					}
					else
					{
						proc_status_file(buf);
					}
				}
			}

		}
	}
	closedir(mydir);
	return 0;
}
