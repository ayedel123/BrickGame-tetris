#include "fullLineHandler.h"

void dropLines(GameManager *gm, int lastLine, int linesCount) {
  for (int i = 0; i < lastLine; i++) {
    for (int j = 0; j < gm->winInfo.width; j++) {
      if (lastLine - i - linesCount >= 0) {
        gm->field[lastLine - i][j] = gm->field[lastLine - i - linesCount][j];
        gm->field[lastLine - i - linesCount][j] = 0;
      } else {
        gm->field[lastLine - i][j] = 0;
      }
    }
  }
}

int isLineFull(GameManager *gm, int lineId) {
  int counter = 0;
  int result = 0;
  for (int j = 0; j < gm->winInfo.width; j++) {
    if (gm->field[lineId][j] != 0) {
      counter++;
    }
  }
  if (counter == gm->winInfo.width)
    result = 1;
  return result;
}

int fullLineHandler(GameManager *gm) {
  int lastLine = 0;
  int fullLines = 0;
  for (int i = 0; i < gm->winInfo.height; i++) {
    if (isLineFull(gm, i) != 0) {
      fullLines++;
      lastLine = i;
    }
  }
  if (fullLines != 0) {
    dropLines(gm, lastLine, fullLines);
  }
  return fullLines * 100;
}

int resetBrick(GameManager *gm) {
  int x = gm->winInfo.width / 2;
  int y = 0;
  gm->currentBrick = gm->nextBrick;
  bornBrick(&gm->nextBrick, x, y, -1, gm->colorCount);

  int isEnd = checkCollision(gm, &gm->currentBrick, DIR_DOWN);
  return isEnd;
}