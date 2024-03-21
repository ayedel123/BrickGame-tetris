#ifndef __TETRIS__
#define __TETRIS__

#include "../back/back.h"

#include "../cli/debug.h"

#include "../cli/menu.h"
#include "../cli/timer.h"
#include "../cli/ui.h"
#include "../cli/window.h"

#include "fsm.h"

#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>

typedef enum { gameWin, menuWin, debugWin } windowsEnum;

int gameLoop(GameInfo_t *gameInfo, WINDOW **windows);
void setUp(WINDOW **windows, int winCount, GameInfo_t *gameInfo, int **field,
           int speed);
int inputHandler(int *direction, int *angle);

#define GAME_SPEED 300
#define GMAE_ACCELERATIONS 20

#endif