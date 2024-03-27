#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__

#include "../../common/defines.h"
#include "../bricks/bricks.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  WinInfo winInfo;
  Brick currentBrick;
  Brick nextBrick;
  int colorCount;
  int points;
  int **field;
  int level;
  int highScore;
  int speed;
  int acceleration;
  int pause;

} GameInfo_t;

void addPoints(GameInfo_t *gameInfo, int fullLines);
void writeRecord(const char *filename, int record);
int readRecord(const char *filename);
void initGameInfo(GameInfo_t *gameInfo, int **field, int speed,
                  int acceleration);
void baseInitGameInfo(GameInfo_t *gameInfo);

#endif