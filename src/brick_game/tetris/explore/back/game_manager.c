#include "game_manager.h"

void init_game_manager(GameManager *gameManager) {
  gameManager->brickBorder.bottom = 0;
  gameManager->brickBorder.right = 0;
  gameManager->brickBorder.left = 0;
  gameManager->brickBorder.top = 0;
  gameManager->bricks = NULL;
  gameManager->current_brick = 0;
  gameManager->cursor.x = 0;
  gameManager->cursor.y = 0;
  gameManager->winInfo.height = 0;
  gameManager->winInfo.startx = 0;
  gameManager->winInfo.starty = 0;
  gameManager->winInfo.width = 0;
  gameManager->deadDot = 0;
  gameManager->colorCount = 0;
}
