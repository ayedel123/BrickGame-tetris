#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__

#include "bricks.h"
#include "defines.h"

typedef struct GameManager {
  WinInfo winInfo;
  int current_brick;
  Brick *bricks;
  int colorCount;

  int **field;

} GameManager;

void init_game_manager(GameManager *gameManager);

#endif