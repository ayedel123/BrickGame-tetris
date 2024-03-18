#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__

#include "bricks.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct GameManager {
  WinInfo winInfo;
  int current_brick;
  Brick *bricks;
  int colorCount;
  int points;
  int **field;

  int record;

} GameManager;

void init_game_manager(GameManager *gameManager);
void addPoints(GameManager *gm, int points);
void writeRecord(const char *filename, int record);
int readRecord(const char *filename);
void initGameManager(GameManager *gameManager);

#endif