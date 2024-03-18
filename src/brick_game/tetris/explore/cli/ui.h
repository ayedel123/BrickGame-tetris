#ifndef __TETRIS_UI__
#define __TETRIS_UI__
#include "../back/back.h"
#include "debug.h"
#include "game_window.h"
#include "window.h"
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

void drawField(WINDOW *win, GameManager *gameManager);
WINDOW *setUpWindow(WinInfo *WinInfo, int winNumber);
void *setUpBrickGameWindows(WinInfo *winInfo, WINDOW **windows, int winCount);
int inputHandler(int *direction, int *angle);
void cursesSetUp();

#endif