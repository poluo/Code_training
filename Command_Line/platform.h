#ifndef _PLATFORM_H
#define _PLATFORM_H


#ifdef linux
	#include <unistd.h>
	#include <termios.h>
#elif  _WIN32
	#include <conio.h>
#endif


#ifdef linux
	#define GET_CH getch()
	#define PRINT_STR printf("%s\n",str_tmp)
	#define BACK_LINE_HEAD printf("\r\033[k")
	#define ENTER_KEY '\n'
	#define MOVEDOWN(x) printf("\033[%dB", (x))
#elif _WIN32
	#define GET_CH _getche()
	#define PRINT_STR printf("\n%s\n",str_tmp)
	#define BACK_LINE_HEAD printf("\r")
	#define ENTER_KEY '\r'
	#define MOVEDOWN(x) printf("\033[%dB", (x)) ///?? in WIN32
#endif


#ifdef linux
	extern  char getch();
#endif // linux

#endif
