#ifndef __TETRIS_MENU__
#define __TETRIS_MENU__

#include "../back/back.h"
#include "window.h"

void printMenu(WINDOW *menuWin, GameManager *gameManager, int direction,
               long long time);

#endif