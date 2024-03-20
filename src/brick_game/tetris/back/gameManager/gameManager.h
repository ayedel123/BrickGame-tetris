#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__

#include "../../common/defines.h"
#include "../bricks/bricks.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct GameManager {
  WinInfo winInfo;
  Brick currentBrick;
  Brick nextBrick;
  int colorCount;
  int points;
  int **field;
  int lvl;
  int record;

} GameManager;

void addPoints(GameManager *gm, int points);
void writeRecord(const char *filename, int record);
int readRecord(const char *filename);
void initGameManager(GameManager *gm, int **field);
int resetBrick(GameManager *gameManager);

#endif