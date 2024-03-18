#ifndef __TETRIS__
#define __TETRIS__

#include "../back/back.h"
#include "debug.h"
#include "game_window.h"
#include "menu.h"
#include "ui.h"
#include "window.h"

#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h>

#define KEY_ESC 27

typedef enum { gameWin, menuWin, debugWin } windowsEnum;
#define COLOR_COUNT 7

void deleteField(int **field, int rows);
int clearField(int **field, int rows, int cols);
int initField(int ***field, int rows, int cols);
int gameLoop(GameManager *gameManager, WINDOW **windows);

#endif