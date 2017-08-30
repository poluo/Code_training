#include <string.h>  //strlen
#include <stdio.h>  //for printf
#include <stdlib.h> //for atioi
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include <sys/types.h>
#include <fcntl.h>
#include "main.h"
#include "linux_info.h"


void get_memory_info(meminfo *this)
{
    FILE* fd = fopen(PROCMEMINFOFILE,"r");
    size_t len = 0;
    ssize_t read;
    if(fd == NULL)
    {
        PINFO("%s open failed\n",PROCMEMINFOFILE);
        return;
    }
    char *buf = NULL;

    while((read = getline(&buf,&len,fd)) != -1)
    {
        #define tryRead(label, variable) (String_startsWith(buf, label) && sscanf(buf + strlen(label), " %32llu kB", variable))
        switch (buf[0]) {
          case 'M':
             if (tryRead("MemTotal:", &this->totalMem)) {}
             else if (tryRead("MemFree:", &this->freeMem)) {}
             else if (tryRead("MemShared:", &this->sharedMem)) {}
             break;
          case 'B':
             if (tryRead("Buffers:", &this->buffersMem)) {}
             break;
          case 'C':
             if (tryRead("Cached:", &this->cachedMem)) {}
             break;
          case 'S':
             switch (buf[1]) {
             case 'w':
                if (tryRead("SwapTotal:", &this->totalSwap)) {}
         }
         break;
      }
        #undef tryRead
    }
    fclose(fd);
    if(buf)
    {
        free(buf);
    }
    PDEBUG("MemTotal:\t\t%d KB\n",this->totalMem);
    PDEBUG("MemFree:\t\t%d KB\n", this->freeMem);
    PDEBUG("MemShared:\t%d KB\n", this->sharedMem);
    PDEBUG("Buffers:\t\t%d KB\n", this->buffersMem);
    PDEBUG("Cached:\t\t%d KB\n", this->cachedMem);
    PDEBUG("SwapTotal:\t%d KB\n", this->totalSwap);
    PDEBUG("SwapFree:\t\t%d KB\n", this->totalSwap);
}

void get_cpu_info(cpuinfo *this)
{
    FILE* fd = fopen(PROCSTATFILE,"r");
	char *tmp = NULL;
    size_t len = 0;
    ssize_t read;
	unsigned long long int total,use;
    if(fd == NULL)
    {
        PINFO("%s open failed %s\n",PROCSTATFILE,strerror(errno));
        return;
    }
    char *buf = NULL;

    if((read = getline(&buf,&len,fd)) != -1)
    {
        if(strncmp(buf,"cpu",strlen("cpu")) == 0)
        {
            sscanf(buf, "cpu  %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu", 
                &this->usertime, &this->nicetime, &this->systemtime, &this->idletime, &this->ioWait, &this->irq, 
                &this->softIrq, &this->steal, &this->guest);
        }
        else
        {
            PINFO("Can not match cpu info\n");
        }
    }
    else
    {
        PINFO("read cpuinfo failed\n");
    }
    fclose(fd);
 
	total  = this->usertime + this->nicetime + this->systemtime + this->idletime + this->ioWait + this->irq + this->softIrq
			+ this->steal + this->guest;
	use = this->usertime + this->nicetime + this->systemtime + this->ioWait;
	this->utilization = use / total;

	
	fd = fopen(PROCCPUINFO,"r");
	if(fd == NULL)
	{
		PINFO("%s open failed\n",PROCCPUINFO);
		return;
	}
	while((read = getline(&buf,&len,fd)) != -1)
    {	
        if(String_startsWith(buf,"model name"))
        {
        	tmp = strchr(buf,':');
            memset(this->model,0,sizeof(this->model));
            sscanf(tmp, ": %[^\t\n]",this->model);
        }
		if(String_startsWith(buf, "cpu cores"))
		{
			tmp = strchr(buf,':');
			this->cores = atoi(tmp+2);
            printf("cores %d\n",this->cores);
		}
    }
    fclose(fd);
    if(buf)
    {
        free(buf);
    }
    PDEBUG("usertime:%d \n",this->usertime);
    PDEBUG("nicetime:%d \n",this->nicetime);
    PDEBUG("systemtime:%d \n",this->systemtime);
    PDEBUG("idletime:%d \n",this->idletime);
    PDEBUG("ioWait:%d \n",this->ioWait);
    PDEBUG("irq:%d \n",this->irq);
    PDEBUG("softIrq:%d \n",this->softIrq);
    PDEBUG("steal:%d \n",this->steal);
    PDEBUG("guest:%d \n",this->guest);
   	PDEBUG("utilization:%f \n",this->utilization);
	PDEBUG("model name:%s\n",this->model);
	PDEBUG("cores:%d\n",this->cores);
}

static ssize_t xread(int fd, void *buf, size_t count) {
  // Read some bytes. Retry on EINTR and when we don't get as many bytes as we requested.
  size_t alreadyRead = 0;
  for(;;) {
     ssize_t res = read(fd, buf, count);
     if (res == -1 && errno == EINTR) continue;
     if (res > 0) {
       buf = ((char*)buf)+res;
       count -= res;
       alreadyRead += res;
     }
     if (res == -1) return -1;
     if (count == 0 || res == 0) return alreadyRead;
  }
}

static double jiffy = 0.0;
static inline unsigned long long LinuxProcess_adjustTime(unsigned long long t) {
   if(jiffy == 0.0) jiffy = sysconf(_SC_CLK_TCK);
   double jiffytime = 1.0 / jiffy;
   return (unsigned long long) t * jiffytime * 100;
}

// read stat file
void read_stat_file_info(process_info *this, const char* filename)
{
    int i = 0;
    int fd = open(filename,O_RDONLY);
    if(fd < 0)
    {
        PINFO("can not open stat file %s %s\n",filename,strerror(errno));
        return;
    }
    char buf[MAX_READ];
    int size = xread(fd,buf,MAX_READ);
    char *location  = strchr(buf,' ');
    if(!location) return;
    location += 2;
    char *end = strrchr(location,')');
    if(!end) return;
    this->command_len= end - location;
    this->command= calloc(0,sizeof(this->command_len + 1));
    memcpy(this->command,location,this->command_len);
    this->command[this->command_len] = '\0';

    location = end +2;
    this->state = location[0];
    location += 2;
    this->ppid= strtol(location,&location,10);
    location += 2;
    this->session = strtoul(location, &location, 10);
    location += 8;
    this->utime = LinuxProcess_adjustTime(strtoull(location, &location, 10));
    location += 1;
    this->stime = LinuxProcess_adjustTime(strtoull(location, &location, 10));
    location += 1;
    this->cutime = LinuxProcess_adjustTime(strtoull(location, &location, 10));
    location += 1;
    this->cstime = LinuxProcess_adjustTime(strtoull(location, &location, 10));
    location += 1;
    this->priority = strtol(location, &location, 10);
    location += 1;
    this->nice = strtol(location, &location, 10);
    location += 1;
    this->nlwp = strtol(location, &location, 10);
    location += 1;
    for (i=0; i<17; i++) 
        location = strchr(location, ' ')+1;
    
    this->exit_signal = strtol(location, &location, 10);
    location += 1;
    assert(location != NULL);
    
    this->processor = strtol(location, &location, 10);
   
    this->time = this->utime + this->stime;
    PDEBUG("pid %d\n",this->pid);
    PDEBUG("command %s\n",this->command);
    PDEBUG("state %c\n",this->state);

}
void get_process_list_info(process_list_info *this)
{
    DIR *dir;
    struct dirent *entry;
    dir = opendir("/proc");
    if(!dir) 
    {
        PINFO("can not open /proc,error %s\n",strerror(errno));
    }
    while((entry = readdir(dir)) != NULL)
    {
        char *name = entry->d_name;
        if(name[0] < '0' || name[0] > '9')
            continue;
        int pid = atoi(name);
        char subdirname[MAX_NAME];
        snprintf(subdirname, MAX_NAME, "/proc/%s/stat",name);
        if(this->size == 0)
        {
            this->process = calloc(1,sizeof(process_info));
            this->size = 1;
            this->process->pid = pid;
            read_stat_file_info(this->process,subdirname);
        }
        else
        {
            this->size ++;
            this->process = realloc(this->process,this->size*sizeof(process_info));
            this->process[this->size - 1].pid = pid;
            read_stat_file_info(&this->process[this->size - 1],subdirname);
        }
    }
    closedir(dir);
}
