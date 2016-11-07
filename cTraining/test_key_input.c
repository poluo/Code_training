#include <stdio.h>
#ifdef linux
	#include <unistd.h>
	#include <termios.h>
#elif  _WIN32
	#include <conio.h>
#endif
#ifdef linux
	char getch();
#endif // linux

#ifdef linux
	#define GET_CH getch()
#elif _WIN32
	#define GET_CH _getche()	
#endif

int  main(int argc, char const *argv[])
{
	int i=0;
	char c=0,last_c=0,last_last_c=0;
	while((c=GET_CH)!='\n'&&c!=EOF)
	{
		printf("%d %c",c,c);
		if (last_last_c==27&&last_c==91)
		{
			switch(c)
			{
				case 65:
					printf("up\n");
					break;
				case 66:
					printf("down\n");
					break;
				case 67:
					printf("right\n");
					break;
				case 68:
					printf("left\n");
					break;
				default:
					printf("wrong\n");
			}
		}
		last_last_c=last_c;
		last_c=c;
	}
	return 0;
}
#ifdef linux
char getch()
{

    /*#include <unistd.h>   //_getch*/
    /*#include <termios.h>  //_getch*/
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c",buf);
    return buf;
}
#endif // linux
