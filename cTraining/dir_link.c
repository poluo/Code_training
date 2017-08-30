#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h> // for getopt_long
#include <errno.h>
#include <dirent.h>

#define NEW_LINK	(0)
#define UN_LINK		(1)
#define RENAME		(2)
#define SYMLINK		(3)
#define READLINK	(4)
#define	MKDIR		(5)
#define RMDIR		(6)
#define OPENDIR		(7)
#define READDIR		(8)
#define REMOVE		(9)
#define NFTW		(10)
#define HANDLE_MAX_NUM	(11)

char des[128];
char src[128];
char buf[256];

typedef unsigned char (*operation_handle)(void);

unsigned char parse_arg(int argc,char const *argv[])
{
    int opt,opt_index,i;
    char *cvalue = NULL;
    static struct option long_opts[]=
    {
        {"newlink", required_argument,  0,  'n'},
        {"unlink",  required_argument,  0,  'u'},
        {"rename",  required_argument,  0,  'r'},
        {"symlink",	required_argument,	0,	's'},
        {"readlink",required_argument,	0,	'l'},
        {"mkdir",	required_argument,	0,	'm'},
        {"rmdir",	required_argument,	0,	'd'},
        {"opendir", required_argument,	0,	'o'},
        {0,         0,                  0,    0} 
    };
    while((opt = getopt_long(argc,argv,"n:u:r:s:l:m:d:o:",long_opts,&opt_index)) != -1)
    {
        switch(opt)
        {
            case 'n':
                cvalue = optarg;
                memcpy(src,cvalue,strlen(cvalue));
                memcpy(des,argv[optind],strlen(argv[optind]));
                return NEW_LINK;
            case 'u':
                cvalue = optarg;
                memcpy(src,cvalue,strlen(cvalue));
                return UN_LINK;
            case 'r':
                cvalue = optarg;
                memcpy(src,cvalue,strlen(cvalue));
                memcpy(des,argv[optind],strlen(argv[optind]));
                return RENAME;
            case 's':
                cvalue = optarg;
                memcpy(src,cvalue,strlen(cvalue));
                memcpy(des,argv[optind],strlen(argv[optind]));
                return SYMLINK;
            case 'l':
                cvalue = optarg;
                memcpy(src,cvalue,strlen(cvalue));
                return READLINK;
            case 'm':
                cvalue = optarg;
                memcpy(src,cvalue,strlen(cvalue));
                return MKDIR;
            case 'd':
                cvalue = optarg;
                memcpy(src,cvalue,strlen(cvalue));
                return RMDIR;
            case 'o':
                cvalue = optarg;
                memcpy(src,cvalue,strlen(cvalue));
                return OPENDIR;
        }
    }
}

unsigned char new_link(void)
{
	printf("src %s des %s\n",src,des);
	link(src,des);
	memset(src,0,strlen(src));
	memset(des,0,strlen(des));
	return 0;
}

unsigned char my_unlink(void)
{
	printf("pathname %s\n",src);
	unlink(src);
	memset(src,0,strlen(src));
	return 0;
}

unsigned char my_rename(void)
{
	printf("src %s des %s\n",src,des);
	rename(src,des);
	memset(src,0,strlen(src));
	memset(des,0,strlen(des));
	return 0;
}

unsigned char my_symlink(void)
{
	printf("src %s des %s\n",src,des);
	symlink(src,des);
	memset(src,0,strlen(src));
	memset(des,0,strlen(des));
	return 0;
}

unsigned char my_readlink(void)
{
	printf("pathname %s\n",src);
	readlink(src,buf,256);
	printf("%s\n",buf);
	memset(src,0,strlen(src));
	return 0;
}
unsigned char my_mkdir(void)
{
	printf("pathname %s\n",src);
	mkdir(src,755);
	memset(src,0,strlen(src));
	return 0;
}
unsigned char my_rmdir(void)
{
	printf("pathname %s\n", src);
	rmdir(src);
	memset(src,0,strlen(src));
	return 0;
}

unsigned char my_opendir(void)
{
	printf("pathname %s\n",src);
	DIR *d = opendir(src);
	struct dirent *entry;
	if(!d)
	{
		printf("cant open dir %s\n",src);
	}
	while((entry = readdir(d)) != NULL)
	{
		char *name = entry->d_name;
		int inode = entry->d_ino;
		printf("name %s inode %d\n",name,inode);
	}
	closedir(d);
}
operation_handle oper_list[HANDLE_MAX_NUM] = {
	new_link,
	my_unlink,
	my_rename,
	my_symlink,
	my_readlink,
	my_mkdir,
	my_rmdir,
	my_opendir,
	NULL,

};

int main(int argc, char const *argv[])
{
	unsigned char choice = parse_arg(argc,argv);
	unsigned char res = oper_list[choice]();
	if(res)
	{
		printf("something wrong happened,please check %s\n",strerror(errno));
	}
	return 0;
}