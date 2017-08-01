/**********************************************************
 * Author        : poluo
 * Email         : xxx@email.com
 * Create time   : 2017-08-01 09:01
 * Last modified : 2017-08-01 09:01
 * Filename      : opt.c
 * Description   : an example for getopt() and getopt_long(),more detail in http://man7.org/linux/man-pages/man3/getopt.3.html
 * *******************************************************/


#include <stdio.h>  //for printf
#include <stdlib.h> //for atioi
#include <unistd.h> //for getopt
#include <getopt.h> // for getopt_long

void test_getopt(int argc,char *argv[])
{
    int ch;
    char *cvalue = NULL;
    while((ch = getopt(argc,argv,"ahc:")) != -1)
    {
        switch(ch)
        {
            case 'a':
                printf("We have a argument,'a'\n");
                break;
            case 'h':
                printf("We have a argument,'h'\n");
                break;
            case 'c':
                cvalue = optarg;
                printf("We have a argument,'c',and the option is %s\n",cvalue);
                break;
            default:
                break;
        }
    }
    
}

void test_getopt_long(int argc,char *argv[])
{
    int opt,opt_index;
    char *cvalue = NULL;
    static struct option long_opts[]=
    {
        {"help",    no_argument,        0,  'h'},
        {"version", no_argument,        0,  'v'},
        {"add",     required_argument,  0,  'a'},
        {"delete",  required_argument,  0,  'd'},
        {0,         0,                  0,    0} 
    };
    while((opt = getopt_long(argc,argv,"hva:d:",long_opts,&opt_index)) != -1)
    {
        switch(opt)
        {
            case 'h':
                printf("This is help text\n");
                break;
            case 'v':
                printf("This is version text\n");
                break;
            case 'a':
                cvalue = optarg;
                printf("this is add function,3+%s=%d\n",cvalue,3+atoi(cvalue));
                break;
            case 'd':
                cvalue = optarg;
                printf("this is delete function,10-%s=%d\n",cvalue,10-atoi(cvalue));
                break;
        }
    }
}
int main(int argc,char *argv[])
{
   //test_getopt(argc,argv); 
   test_getopt_long(argc,argv);
}
