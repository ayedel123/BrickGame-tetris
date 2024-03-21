#ifndef __TETRIS_MENU__
#define __TETRIS_MENU__

#include "../back/back.h"
#include "ui.h"
#include "window.h"
#include <ncurses.h>

void printMenu(WINDOW *menuWin, GameInfo_t *gameInfo,int state);

#endif