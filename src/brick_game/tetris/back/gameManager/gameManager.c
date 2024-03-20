#include "gameManager.h"

void initGameManager(GameManager *gm, int **field) {
  gm->winInfo.height = GAME_WINDOW_HEIGHT;
  gm->winInfo.width = GAME_WINDOW_WIDTH;
  gm->colorCount = COLOR_COUNT;
  gm->field = field;
  bornBrick(&gm->currentBrick, gm->winInfo.width / 2, 0, -1, gm->colorCount);
  bornBrick(&gm->nextBrick, gm->winInfo.width / 2, 0, -1, gm->colorCount);
  gm->points = 0;
  gm->lvl = 1;
  gm->record = readRecord("record");
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

void addPoints(GameManager *gm, int points) {
  if (gm->points <= 100000000)
    gm->points += points;
  if (gm->points > gm->record) {
    gm->record = gm->points;
    writeRecord("record", gm->record);
  }

  if (gm->points >= 600 * gm->lvl && gm->lvl < 10) {
    gm->lvl += 1;
  }
}
