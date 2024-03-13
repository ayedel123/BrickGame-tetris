#ifndef __BACK__
#define __BACK__

#include "bricks.h"
#include "defines.h"
#include "game_manager.h"

int move_brick(GameManager *gameManager, int direction);
void calcBrickBordesrs(GameManager *gameManager);
void resetBrick(GameManager *gameManager);
void rotate(GameManager *gameManager, int angle);

#endif