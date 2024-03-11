#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__

#include "bricks.h"
#include "defines.h"

typedef struct GameManager {
  WinInfo winInfo;
  Cursor cursor;
  int current_brick;
  Brick *bricks;
  BrickBorder brickBorder;

} GameManager;

void init_game_manager(GameManager * gameManager);

#endif