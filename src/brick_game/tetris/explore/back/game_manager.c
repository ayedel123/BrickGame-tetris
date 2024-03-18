#include "game_manager.h"

void init_game_manager(GameManager *gameManager) {
  gameManager->bricks = NULL;
  gameManager->current_brick = 0;
  gameManager->winInfo.height = 0;
  gameManager->winInfo.startx = 0;
  gameManager->winInfo.starty = 0;
  gameManager->winInfo.width = 0;
  gameManager->colorCount = 0;
  gameManager->field = NULL;
}
