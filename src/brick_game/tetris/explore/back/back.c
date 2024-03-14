#include "back.h"

void set_anchor(Brick *brick, int x, int y) {
  brick->x = x;
  brick->y = y;
}

int check_collision_horyzontal(Brick *localStar, Brick *sus, int ii, int iii,
                               int direction) {
  int col = 0;
  if (direction == right || direction == left || direction == state) {
    if (localStar->y + localStar->cords[ii][1] == sus->cords[iii][1] + sus->y &&
        localStar->x + localStar->cords[ii][0] ==
            sus->cords[iii][0] + sus->x - direction)
      col = COL_STATE_COL;
  }
  return col;
}

int check_collision_bot(Brick *localStar, Brick *sus, int ii, int iii,
                        int direction) {
  int col = 0;
  if (direction == down || direction == state) {

    if (localStar->x + localStar->cords[ii][0] == sus->cords[iii][0] + sus->x &&
        localStar->y + localStar->cords[ii][1] ==
            sus->cords[iii][1] + sus->y - direction / 2)
      col = COL_STATE_CRIT;
  }
  return col;
}

int check_collision(GameManager *gameManager, int direction) {
  int col = COL_STATE_NO_COL;
  Brick *local_star = &gameManager->bricks[gameManager->current_brick];
  for (int i = 0; i < gameManager->current_brick && !col; i++) {
    Brick *sus = &gameManager->bricks[i];
    for (int ii = 0; ii < 4 && !col; ii++) {
      for (int iii = 0; iii < 4 && !col; iii++) {
        col = check_collision_bot(local_star, sus, ii, iii, direction);
        col = (col == 0) ? check_collision_horyzontal(local_star, sus, ii, iii,
                                                      direction)
                         : col;
      }
    }
  }
  return col;
}

int check_bordercross_x(GameManager *gameManager, int direction) {
  int col = COL_STATE_NO_COL;
  Brick *current_brick = &gameManager->bricks[gameManager->current_brick];
  if (direction == right || direction == state) {
    if (current_brick->x + gameManager->brickBorder.right >=
        gameManager->winInfo.width - WINDOW_OFFSET - direction) {
      col = COL_STATE_COL;
    }
  }
  if (direction == left || direction == state) {
    int tmp = (direction == state) ? 1 : 0;
    if (current_brick->x + gameManager->brickBorder.left <=
        WINDOW_OFFSET - tmp) {
      col = COL_STATE_COL;
    }
  }
  return col;
}

int check_bordercross_y(GameManager *gameManager, int direction) {
  int col = COL_STATE_NO_COL;
  Brick *current_brick = &gameManager->bricks[gameManager->current_brick];
  if (direction == down || direction == state) {
    if (current_brick->y + gameManager->brickBorder.bottom >=
        gameManager->winInfo.height - WINDOW_OFFSET - direction / 2) {
      col = COL_STATE_CRIT;
    }
  }
  if (direction == top || direction == state) {
    int tmp = (direction == state) ? 1 : 0;
    if (current_brick->y + gameManager->brickBorder.top <=
        WINDOW_OFFSET - tmp) {
      col = COL_STATE_COL;
    }
  }
  return col;
}

int check_bordercross(GameManager *gameManager) {}

void moveCurrnetAnchor(GameManager *gameManager) {
  gameManager->bricks[gameManager->current_brick].x = gameManager->cursor.x;
  gameManager->bricks[gameManager->current_brick].y = gameManager->cursor.y;
}

int move_cursor(GameManager *gameManager, int direction) {
  // int res = check_collision_horyzontal(gameManager);

  gameManager->cursor.x = (direction == right || direction == left)
                              ? gameManager->cursor.x + direction
                              : gameManager->cursor.x;

  gameManager->cursor.y = (direction == top || direction == down)
                              ? gameManager->cursor.y + direction / 2
                              : gameManager->cursor.y;
  moveCurrnetAnchor(gameManager);
  return 0;
}

int checkCollision(GameManager *gameManager, int direction) {
  int res = check_bordercross_x(gameManager, direction);
  res = (res == 0) ? check_bordercross_y(gameManager, direction) : res;
  res = (res == 0) ? check_collision(gameManager, direction) : res;
  return res;
}

int moveBrick(GameManager *gameManager, int direction) {
  move_cursor(gameManager, direction);
  move_cursor(gameManager, -direction);

  Cursor *local_cursor = &gameManager->cursor;
  Brick *local_brick = &gameManager->bricks[gameManager->current_brick];
  int res = checkCollision(gameManager, direction);
  if (res == 0) {
    move_cursor(gameManager, direction);
  }
  return res;
}

void calcBrickBordesrs(GameManager *gameManager) {
  Brick *brick = &gameManager->bricks[gameManager->current_brick];
  BrickBorder *border = &gameManager->brickBorder;
  border->right = brick->cords[0][0];
  border->left = brick->cords[0][0];
  border->top = brick->cords[0][1];
  border->bottom = brick->cords[0][1];
  for (int i = 0; i < 4; i++) {
    border->right = (border->right > brick->cords[i][0]) ? border->right
                                                         : brick->cords[i][0];
    border->left =
        (border->left < brick->cords[i][0]) ? border->left : brick->cords[i][0];

    border->bottom = (border->bottom > brick->cords[i][1]) ? border->bottom
                                                           : brick->cords[i][1];

    border->top =
        (border->top < brick->cords[i][1]) ? border->top : brick->cords[i][1];
  }
}

void resetBrick(GameManager *gameManager) {
  (gameManager->current_brick)++;
  gameManager->cursor.x = 1;
  gameManager->cursor.y = 1;
  born_brick(&gameManager->bricks[gameManager->current_brick],
             gameManager->cursor.x, gameManager->cursor.y, -1,gameManager->colorCount);
  calcBrickBordesrs(gameManager);
}

void rotateRight(Brick *brick) {
  int tmp = 0;
  for (int i = 0; i < 4; i++) {
    tmp = brick->cords[i][0];
    brick->cords[i][0] = -brick->cords[i][1];
    brick->cords[i][1] = tmp;
  }
}

void rotateLeft(Brick *brick) {
  int tmp = 0;
  for (int i = 0; i < 4; i++) {
    tmp = brick->cords[i][0];
    brick->cords[i][0] = brick->cords[i][1];
    brick->cords[i][1] = -tmp;
  }
}

void justRotate(GameManager *gameManager, int angle) {
  if (angle == -1) {
    rotateLeft(&gameManager->bricks[gameManager->current_brick]);
  } else if (angle == 1) {
    rotateRight(&gameManager->bricks[gameManager->current_brick]);
  }
  calcBrickBordesrs(gameManager);
}

int rotate(GameManager *gameManager, int angle) {
  justRotate(gameManager, angle);
  int res = checkCollision(gameManager, state);

  if (res != 0) {
    justRotate(gameManager, -angle);
  }
  return res;
}

void fillField(GameManager *gameManager) {
  for (int i = 0; i < gameManager->current_brick; i++) {
  }
}

void writeSuspectDots(Brick *brick, int **susYDotes, int *susCount, int y) {
  for (int k = 0; k < 4; k++) {
    if (brick->y + brick->cords[k][1] == y) {
      susYDotes[*susCount] = &brick->cords[k][1];
      (*susCount)++;
    }
  }
}

int tryDeleteDots(int **susYDotes, int *susCount, int deleteVal) {
  int res = 0;

  if (*susCount == 10) {
    for (int i = 0; i < *susCount; i++) {
      *susYDotes[i] = deleteVal;
    }
    *susCount = 0;
    res = 1;
  }

  return res;
}

void dropBricks(GameManager *gameManager, int lastLine, int delLines) {
  for (int i = 0; i < gameManager->current_brick; i++) {
    for (int j = 0; j < 4; j++) {
      if ((gameManager->bricks[i].cords[j][1] + gameManager->bricks[i].y <
           lastLine) &&
          gameManager->bricks[i].cords[j][1] != gameManager->deadDot)
        gameManager->bricks[i].cords[j][1] += delLines;
    }
  }
}

void deleteDots(GameManager *gameManager) {
  int *susYDotes[gameManager->winInfo.width - 2]; // Нет инициализации

  int susCount = 0;
  int tmp = 0;
  int lastLine = 0;
  Brick *susBrick;
  int delLines = 0;
  int deleteVal = -gameManager->winInfo.height;
  for (int y = gameManager->winInfo.height - 1; y > 0; y--) {
    for (int j = 0; j < gameManager->current_brick && tmp == 0; j++) {
      writeSuspectDots(&gameManager->bricks[j], susYDotes, &susCount, y);
      tmp = tryDeleteDots(susYDotes, &susCount, gameManager->deadDot);
    }
    if (tmp) {
      lastLine = y;
      delLines++;
    }
    susCount = 0;
    tmp = 0;
  }
  if (delLines > 0)
    dropBricks(gameManager, lastLine, delLines);
}

