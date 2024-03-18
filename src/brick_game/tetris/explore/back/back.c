#include "back.h"

int checkCollisionBrick(int **field, Brick *brick, int cordI, int direction) {
  int result = (field[brick->y + brick->cords[cordI][1]]
                     [brick->x + brick->cords[cordI][0]] == 0)
                   ? 0
                   : COL_STATE_COL;

  if (result == COL_STATE_COL && direction == down) {
    result = COL_STATE_CRIT;
  }
  return result;
}

int checkOutOfBounds(Brick *brick, int cordI, int width, int height) {
  int brickX = brick->x + brick->cords[cordI][0];
  int brickY = brick->y + brick->cords[cordI][1];
  int result = (brickX < 0 || brickX >= width || brickY < 0) ? COL_STATE_COL
                                                             : COL_STATE_NO_COL;
  result = (brickY >= height) ? COL_STATE_CRIT : result;
  return result;
}

int checkCollision(GameManager *gameManager, Brick *brick, int direction) {
  int result = 0;
  for (int i = 0; i < 4 && result == 0; i++) {
    result = checkOutOfBounds(brick, i, gameManager->winInfo.width,
                              gameManager->winInfo.height);
    if (result == COL_STATE_NO_COL) {
      result = checkCollisionBrick(gameManager->field, brick, i, direction);
    }
  }
  return result;
}
//доработка

void moveBrickCords(Brick *brick, int direction) {
  if (direction == right || direction == left) {
    brick->x += direction;
  }
  if (direction == top || direction == down) {
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

int moveBrick(GameManager *gameManager, Brick *oldBrick, int direction,
              int angle) {
  Brick newBrick = *oldBrick;
  deleteFromField(gameManager->field, oldBrick);

  if (direction != state) {
    moveBrickCords(&newBrick, direction);
  } else if (angle != 0) {
    rotateBrickCords(&newBrick, angle);
  }

  int result = checkCollision(gameManager, &newBrick, direction);
  if (result == COL_STATE_NO_COL) {
    *oldBrick = newBrick;
  }
  moveBrickInField(gameManager->field, oldBrick);

  return result;
}

int handleAction(GameManager *gm, int direction, int angle) {
  int result = 0;
  result =
      (result == COL_STATE_CRIT)
          ? result
          : moveBrick(gm, &gm->bricks[gm->current_brick], direction, angle);

  return result;
}

void resetBrick(GameManager *gameManager) {
  int x = 0;
  int y = 0;
  born_brick(&gameManager->bricks[gameManager->current_brick], x, y, -1,
             gameManager->colorCount);
}

void dropLines(GameManager *gm, int lastLine, int linesCount) {
  for (int i = 0; i < lastLine; i++) {
    for (int j = 0; j < gm->winInfo.width; j++) {
      if (lastLine - i - linesCount >= 0) {
        gm->field[lastLine - i][j] = gm->field[lastLine - i - linesCount][j];
        gm->field[lastLine - i - linesCount][j] = 0;
      } else {
        gm->field[lastLine - i][j] = 0;
      }
    }
  }
}

int isLineFull(GameManager *gm, int lineId) {
  int counter = 0;
  int result = 0;
  for (int j = 0; j < gm->winInfo.width; j++) {
    if (gm->field[lineId][j] != 0) {
      counter++;
    }
  }
  if (counter == gm->winInfo.width)
    result = 1;
  return result;
}

int fullLineHandler(GameManager *gm) {
  int lastLine = 0;
  int result = 0;
  int fullLines = 0;
  for (int i = 0; i < gm->winInfo.height; i++) {
    if (isLineFull(gm, i) != 0) {
      fullLines++;
      lastLine = i;
      result = 1;
    }
  }
  if (result) {
    dropLines(gm, lastLine, fullLines);
  }
  return result;
}
