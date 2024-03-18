#ifndef __BACK__
#define __BACK__

#include "bricks.h"
#include "defines.h"
#include "game_manager.h"

int moveBrick(GameManager *gameManager, Brick *oldBrick, int direction,
              int angle);
int resetBrick(GameManager *gameManager);
int handleAction(GameManager *gm, int direction, int angle);
int fullLineHandler(GameManager *gm);

#endif