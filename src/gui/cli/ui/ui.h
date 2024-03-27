#ifndef __TETRIS_UI__
#define __TETRIS_UI__

#include "../../../brick_game/tetris/back/back.h"
#include "../window/window.h"

#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

void drawField(WINDOW *win, GameInfo_t *gameManager);
WINDOW *setUpWindow(int winNumber);
int *setUpBrickGameWindows(WINDOW **windows, int winCount);
void cursesSetUp();
void gameOverMessage(WINDOW *win, int width, int height);
void startMessage(WINDOW *win, int width, int height);

#endif