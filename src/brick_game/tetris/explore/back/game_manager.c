#include "game_manager.h"

void initGameManager(GameManager *gameManager) {
  gameManager->bricks = NULL;
  gameManager->current_brick = 0;
  gameManager->winInfo.height = 0;
  gameManager->winInfo.startx = 0;
  gameManager->winInfo.starty = 0;
  gameManager->winInfo.width = 0;
  gameManager->colorCount = 0;
  gameManager->points = 0;
  gameManager->record = 0;
  gameManager->field = NULL;
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
  int number;
  FILE *file = fopen(filename, "rb");

  if (file == NULL) {
    return 0;
  }

  fread(&number, sizeof(int), 1, file);
  fclose(file);

  return number;
}

void addPoints(GameManager *gm, int points) {
  if (gm->points <= 100000000)
    gm->points += points;
  if (gm->points > gm->record) {
    gm->record = gm->points;
    writeRecord("record", gm->record);
  }
}