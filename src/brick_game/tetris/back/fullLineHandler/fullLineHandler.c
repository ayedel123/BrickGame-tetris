#include "fullLineHandler.h"

void dropLines(GameInfo_t *gameInfo, int lastLine, int linesCount) {
  for (int i = 0; i < lastLine; i++) {
    for (int j = 0; j < gameInfo->winInfo.width; j++) {
      if (lastLine - i - linesCount >= 0) {
        gameInfo->field[lastLine - i][j] =
            gameInfo->field[lastLine - i - linesCount][j];
        gameInfo->field[lastLine - i - linesCount][j] = 0;
      } else {
        gameInfo->field[lastLine - i][j] = 0;
      }
    }
  }
}

int isLineFull(GameInfo_t *gameInfo, int lineId) {
  int counter = 0;
  int result = 0;
  for (int j = 0; j < gameInfo->winInfo.width; j++) {
    if (gameInfo->field[lineId][j] != 0) {
      counter++;
    }
  }
  if (counter == gameInfo->winInfo.width)
    result = 1;
  return result;
}

int fullLineHandler(GameInfo_t *gameInfo) {
  int lastLine = 0;
  int fullLines = 0;
  for (int i = 0; i < gameInfo->winInfo.height; i++) {
    if (isLineFull(gameInfo, i) != 0) {
      fullLines++;
      lastLine = i;
    }
  }
  if (fullLines != 0) {
    dropLines(gameInfo, lastLine, fullLines);
  }
  return fullLines;
}

int resetBrick(GameInfo_t *gameInfo) {
  int x = gameInfo->winInfo.width / 2;
  int y = 0;
  gameInfo->currentBrick = gameInfo->nextBrick;
  bornBrick(&gameInfo->nextBrick, x, y, -1, gameInfo->colorCount);

  int isEnd = checkCollision(gameInfo, &gameInfo->currentBrick, DIR_DOWN);
  return isEnd;
}