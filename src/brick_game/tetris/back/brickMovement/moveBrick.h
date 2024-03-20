#ifndef __TETRIS_MOVE_BRICK__
#define __TETRIS_MOVE_BRICK__

#include "../../common/defines.h"
#include "../GameManager/gameManager.h"
#include "checkCollision.h"

int moveBrick(GameManager *gameManager, Brick *oldBrick, int direction,
              int angle);
void moveBrickInField(int **field, Brick *brick);
void deleteFromField(int **field, Brick *brick);
void rotateBrickCords(Brick *brick, int angle);
void moveBrickCords(Brick *brick, int direction);

#endif