#ifndef __TETRIS_CHECK_COLLISION_
#define __TETRIS_CHECK_COLLISION_

#include "../GameManager/gameManager.h"

int checkCollision(GameManager *gameManager, Brick *brick, int direction);
int checkOutOfBounds(Brick *brick, int cordI, int width, int height);
int checkCollisionBrick(int **field, Brick *brick, int cordI, int direction);

#endif