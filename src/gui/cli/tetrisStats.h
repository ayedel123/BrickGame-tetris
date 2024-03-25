#ifndef __TETRIS_MENU__
#define __TETRIS_MENU__

#include "../../brick_game/tetris/back/back.h"
#include "../../brick_game/tetris/common/defines.h"
#include "ui.h"
#include "window.h"

#include <ncurses.h>

void printTetrisStats(WINDOW *menuWin, GameInfo_t *gameInfo, int isOnPause);

#endif