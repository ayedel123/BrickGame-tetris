#ifndef __WINDOW__
#define __WINDOW__

#include <ncurses.h>

WINDOW *createNewWin(int height, int width, int starty, int startx);

#endif