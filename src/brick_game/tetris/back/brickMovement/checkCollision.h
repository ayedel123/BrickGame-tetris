#ifndef __TETRIS_CHECK_COLLISION_
#define __TETRIS_CHECK_COLLISION_

#include "../gameInfo/gameInfo.h"

int checkCollision(GameInfo_t *gameInfo, Brick *brick, int direction);
int checkOutOfBounds(Brick *brick, int cordI, int width, int height,
                     int direction);
int checkCollisionBrick(int **field, Brick *brick, int cordI, int direction);

#endif