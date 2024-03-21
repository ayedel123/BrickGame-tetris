#include "checkCollision.h"

int checkCollisionBrick(int **field, Brick *brick, int cordI, int direction) {
  int result = (field[brick->y + brick->cords[cordI][1]]
                     [brick->x + brick->cords[cordI][0]] == 0)
                   ? 0
                   : COL_STATE_COL;

  if (result == COL_STATE_COL && direction == DIR_DOWN) {
    result = COL_STATE_CRIT;
  }
  return result;
}

int checkOutOfBounds(Brick *brick, int cordI, int width, int height,
                     int direction) {
  int brickX = brick->x + brick->cords[cordI][0];
  int brickY = brick->y + brick->cords[cordI][1];
  int result = (brickX < 0 || brickX >= width || brickY < 0 || brickY >= height)
                   ? COL_STATE_COL
                   : COL_STATE_NO;

  result =
      (brickY >= height && direction != DIR_STATE) ? COL_STATE_CRIT : result;
  return result;
}

int checkCollision(GameInfo_t *gameInfo, Brick *brick, int direction) {
  int result = 0;
  for (int i = 0; i < 4 && result == COL_STATE_NO; i++) {
    result = checkOutOfBounds(brick, i, gameInfo->winInfo.width,
                              gameInfo->winInfo.height, direction);
    if (result == COL_STATE_NO) {
      result = checkCollisionBrick(gameInfo->field, brick, i, direction);
    }
  }

  return result;
}