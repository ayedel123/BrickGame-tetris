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

int checkCollision(GameManager *gm, Brick *brick, int direction) {
  int result = 0;
  for (int i = 0; i < 4 && result == 0; i++) {
    result = checkOutOfBounds(brick, i, gm->winInfo.width, gm->winInfo.height,
                              direction);
    if (result == COL_STATE_NO) {
      result = checkCollisionBrick(gm->field, brick, i, direction);
    }
  }

  return result;
}