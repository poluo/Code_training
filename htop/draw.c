#include <curses.h>
#include <stdio.h>
void draw_init()
{
	initscr();
	if(has_colors())
	{
        start_color();
		init_pair(0,COLOR_BLACK,COLOR_BLACK);
    	init_pair(1,COLOR_GREEN,COLOR_BLACK);
    	init_pair(2,COLOR_RED,COLOR_BLACK);
		init_pair(3,COLOR_CYAN,COLOR_BLACK);
		init_pair(4,COLOR_WHITE,COLOR_BLACK);
		init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
		init_pair(6,COLOR_BLUE,COLOR_BLACK);
		init_pair(7,COLOR_YELLOW,COLOR_BLACK);
		attron(COLOR_PAIR(2));
		move(50,100);
        printw("test\n");
        refresh();
        getch();
        attroff(COLOR_PAIR(2));
	}
    else
    {
        printf("there is no color\n");
    }
}

void draw_done()
{
	endwin();
}
