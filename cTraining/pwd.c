/**********************************************************
 * Author        : poluo
 * Email         : xxx@email.com
 * Create time   : 2017-08-01 09:37
 * Last modified : 2017-08-01 09:37
 * Filename      : pwd.c
 * Description   : 
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

void get_user_info_by_id(const uid_t user_id)
{
    struct passwd *user = getpwuid(user_id);
    uid_t id = 0,group_id = 0;
    char *name = NULL;
    if(user)
    {
        id = user->pw_uid;
        group_id = user->pw_gid;
        name = user->pw_name;
        printf("name: %s,uid: %d,gid: %d\n",name,id,group_id);
    }
    else
    {
        printf("No such user\n");
    }
}


void get_user_info(const char *user_name)
{
    struct passwd *user = getpwnam(user_name);
    uid_t user_id = 0,group_id = 0;
    char *name = NULL;
    if(user)
    {
        user_id = user->pw_uid;
        group_id = user->pw_gid;
        name = user->pw_name;
        printf("name: %s,uid: %d,gid: %d\n",name,user_id,group_id);
    }
    else
    {
        printf("No such user\n");
    }
}
int main(int argc,char *argv[])
{
    if(argc > 1)
    {
        printf("get %s's user info\n",argv[1]);
        //get_user_info(argv[1]);
        get_user_info_by_id(atoi(argv[1]));
    }
    else
    {
        printf("This program need a user name\n");
    }
}
