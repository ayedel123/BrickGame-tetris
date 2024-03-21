#include "moveBrick.h"

//доработка

void moveBrickCords(Brick *brick, int direction) {
  if (direction == DIR_RIGHT || direction == DIR_LEFT) {
    brick->x += direction;
  }
  if (direction == DIR_TOP || direction == DIR_DOWN) {
    brick->y += direction / 2;
  }
}

void rotateBrickCords(Brick *brick, int angle) {
  int tmp = 0;
  for (int i = 0; i < 4; i++) {
    tmp = brick->cords[i][0];
    brick->cords[i][0] = angle * brick->cords[i][1];
    brick->cords[i][1] = -angle * tmp;
  }
}

void deleteFromField(int **field, Brick *brick) {
  for (int i = 0; i < 4; i++) {
    field[brick->y + brick->cords[i][1]][brick->x + brick->cords[i][0]] = 0;
  }
}

void moveBrickInField(int **field, Brick *brick) {

  for (int i = 0; i < 4; i++) {
    field[brick->y + brick->cords[i][1]][brick->x + brick->cords[i][0]] =
        brick->color;
  }
}

int moveBrick(GameInfo_t *gameInfo, Brick *oldBrick, int direction, int angle) {
  Brick newBrick = *oldBrick;
  int result = COL_STATE_NO;
  for (int i = 0; i < 4 && result == COL_STATE_NO; i++) {
    result = checkOutOfBounds(oldBrick, i, gameInfo->winInfo.width,
                              gameInfo->winInfo.height, DIR_STATE);
  }
  if (result == COL_STATE_NO) {
    deleteFromField(gameInfo->field, oldBrick);

    if (direction != DIR_STATE) {
      moveBrickCords(&newBrick, direction);
    } else if (angle != 0 && direction == DIR_STATE) {
      rotateBrickCords(&newBrick, angle);
    }

    result = checkCollision(gameInfo, &newBrick, direction);
    if (result == COL_STATE_NO) {
      *oldBrick = newBrick;
    }

    moveBrickInField(gameInfo->field, oldBrick);
  }
  return result;
}
