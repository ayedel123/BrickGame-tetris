#include "back.h"

void set_anchor(Brick *brick, int x, int y) {
  brick->anchor_x = x;
  brick->anchor_y = y;
}

int check_collision_bot(GameManager *gameManager) {
  int col = COL_STATE_NO_COL;
  Brick *local_star = &gameManager->bricks[gameManager->current_brick];
  for (int i = 0; i < gameManager->current_brick && !col; i++) {
    Brick *sus = &gameManager->bricks[i];
    for (int ii = 0; ii < 4 && !col; ii++) {
      for (int iii = 0; iii < 4 && !col; iii++) {
        if (local_star->anchor_x + local_star->cords[ii][0] ==
                sus->cords[iii][0] + sus->anchor_x &&
            local_star->anchor_y + local_star->cords[ii][1] + 1 ==
                sus->cords[iii][1] + sus->anchor_y)
          col = COL_STATE_BRICK;
      }
    }
  }
  if (col == COL_STATE_NO_COL) {
    if (local_star->anchor_y + gameManager->brickBorder.bottom >=
        gameManager->winInfo.height) {
      col = 1;
    }
  }
  return col;
}

int check_bordercross_x(GameManager *gameManager) {
  int col = COL_STATE_NO_COL;
  Brick *current_brick = &gameManager->bricks[gameManager->current_brick];
  if (current_brick->anchor_x + gameManager->brickBorder.right >=
      gameManager->winInfo.width - WINDOW_OFFSET) {
    col = COL_STATE_BORDER;
    move_cursor(gameManager, left);
  }
  if (current_brick->anchor_x + gameManager->brickBorder.left <=
      WINDOW_OFFSET - 1) {
    move_cursor(gameManager, right);
    col = COL_STATE_BORDER;
  }
  return col;
}

int check_bordercross_y(GameManager *gameManager) {
  int col = COL_STATE_NO_COL;
  Brick *current_brick = &gameManager->bricks[gameManager->current_brick];
  if (current_brick->anchor_y + gameManager->brickBorder.top >=
      gameManager->winInfo.height - WINDOW_OFFSET) {
    col = COL_STATE_BORDER;
    move_cursor(gameManager, top);
  }
  if (current_brick->anchor_y + gameManager->brickBorder.bottom <=
      WINDOW_OFFSET - 1) {
    move_cursor(gameManager, down);
    col = COL_STATE_BORDER;
  }
  return col;
}

int check_bordercross(GameManager *gameManager) {}

void move_currnet_anchor(GameManager *gameManager) {
  gameManager->bricks[gameManager->current_brick].anchor_x =
      gameManager->cursor.x;
  gameManager->bricks[gameManager->current_brick].anchor_y =
      gameManager->cursor.y;
}

int move_cursor(GameManager *gameManager, int direction) {
  // int res = check_collision_horyzontal(gameManager);

  gameManager->cursor.x = (direction == right || direction == left)
                              ? gameManager->cursor.x + direction
                              : gameManager->cursor.x;

  gameManager->cursor.y = (direction == top || direction == down)
                              ? gameManager->cursor.y + direction / 2
                              : gameManager->cursor.y;
  return 0;
}

int move_brick(GameManager *gameManager, int direction) {
  Cursor *local_cursor = &gameManager->cursor;
  Brick *local_brick = &gameManager->bricks[gameManager->current_brick];
  int res = move_cursor(gameManager, direction);
  move_currnet_anchor(gameManager);
  check_bordercross_x(gameManager);
  move_currnet_anchor(gameManager);
  check_bordercross_y(gameManager);
  move_currnet_anchor(gameManager);
  return res;
}

void calcBrickBordesrs(GameManager *gameManager) {
  Brick *brick = &gameManager->bricks[gameManager->current_brick];
  BrickBorder *border = &gameManager->brickBorder;
  for (int i = 0; i < 4; i++) {
    border->right = (border->right > brick->cords[i][0]) ? border->right
                                                         : brick->cords[i][0];
    border->left =
        (border->left < brick->cords[i][0]) ? border->left : brick->cords[i][0];

    border->top = (border->bottom > brick->cords[i][1]) ? border->bottom
                                                        : brick->cords[i][1];

    border->bottom =
        (border->top < brick->cords[i][1]) ? border->top : brick->cords[i][1];
  }
}