#include "gameInfo.h"

void initGameInfo(GameInfo_t *gameInfo, int **field, int speed,
                  int acceleration) {
  gameInfo->winInfo.height = GAME_WINDOW_HEIGHT;
  gameInfo->winInfo.width = GAME_WINDOW_WIDTH;
  gameInfo->colorCount = COLOR_COUNT;
  gameInfo->field = field;
  bornBrick(&gameInfo->currentBrick, gameInfo->winInfo.width / 2, 0, -1,
            gameInfo->colorCount);
  bornBrick(&gameInfo->nextBrick, gameInfo->winInfo.width / 2, 0, -1,
            gameInfo->colorCount);
  gameInfo->points = 0;
  gameInfo->level = 1;
  gameInfo->speed = speed;
  gameInfo->highScore = readRecord("record");
  gameInfo->acceleration = acceleration;
}

void baseInitGameInfo(GameInfo_t *gameInfo) {
  gameInfo->winInfo.height = 0;
  gameInfo->winInfo.width = 0;
  gameInfo->colorCount = 1;
  gameInfo->field = NULL;
  gameInfo->currentBrick = BRICKS_TYPES[0];
  gameInfo->nextBrick = BRICKS_TYPES[0];
  gameInfo->level = 0;
  gameInfo->points = 0;
  gameInfo->highScore = 0;
  gameInfo->acceleration = 0;
}

void writeRecord(const char *filename, int record) {
  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    return;
  }
  fwrite(&record, sizeof(int), 1, file);
  fclose(file);
}

int readRecord(const char *filename) {
  int number = 0;
  FILE *file = fopen(filename, "rb");

  if (file != NULL) {
    fread(&number, sizeof(int), 1, file);
    fclose(file);
  }
  return number;
}

void addPoints(GameInfo_t *gameInfo, int fullLines) {

  int points = 0;
  switch (fullLines) {
  case 0:
    points = 0;
    break;
  case 1:
    points = 100;
    break;
  case 2:
    points = 300;
    break;
  case 3:
    points = 700;
    break;
  case 4:
    points = 1500;
    break;
  default:
    points = 1500;
    break;
  }
  if (gameInfo->points <= 100000000)
    gameInfo->points += points;
  if (gameInfo->points > gameInfo->highScore) {
    gameInfo->highScore = gameInfo->points;
    writeRecord("record", gameInfo->highScore);
  }
  if (gameInfo->points >= 600 * (gameInfo->level) && gameInfo->level < 10) {
    gameInfo->level = gameInfo->points / 600+1;
  }
}
