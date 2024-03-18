#ifndef __BACK__
#define __BACK__

#include "bricks.h"
#include "defines.h"
#include "game_manager.h"

int moveBrick(GameManager *gameManager, int direction);
void calcBrickBordesrs(GameManager *gameManager);
void resetBrick(GameManager *gameManager);
int rotate(GameManager *gameManager, int angle);
void deleteDots(GameManager *gameManager);
int handleAction(GameManager *gm, int direction, int angle);
int fullLineHandler(GameManager *gm);

#endif