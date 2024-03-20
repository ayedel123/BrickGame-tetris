#ifndef __TETRIS__
#define __TETRIS__

#include "../back/back.h"

#include "../cli/debug.h"

#include "../cli/menu.h"
#include "../cli/timer.h"
#include "../cli/ui.h"
#include "../cli/window.h"

#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>

typedef enum { gameWin, menuWin, debugWin } windowsEnum;


int gameLoop(GameManager *gameManager, WINDOW **windows);

#define GAME_SPEED 300
#define GMAE_ACCELERATIONS 20

#endif