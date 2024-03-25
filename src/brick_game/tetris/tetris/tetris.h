#ifndef __TETRIS__
#define __TETRIS__

#include "../../../gui/cli/cli.h"
#include "../back/back.h"
#include "../common/defines.h"
#include "fsm.h"

#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>

int gameLoop(GameInfo_t *gameInfo, WINDOW **windows);
void setUp(WINDOW **windows, int winCount, GameInfo_t *gameInfo, int **field);

#define GAME_SPEED 300
#define GMAE_ACCELERATION 20

#endif