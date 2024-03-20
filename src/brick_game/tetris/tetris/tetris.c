
#include "tetris.h"

void setUp(WINDOW **windows, int winCount, GameManager *gm, int **field);
int inputHandler(int *direction, int *angle);

int main() {
  WINDOW *windows[3];
  GameManager gm;
  int **field = NULL;
  initField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);

  int key = 0;
  while (key != 404) {
    clearField(field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    setUp(windows, 2, &gm, field);
    key = gameLoop(&gm, windows);
  }

  endwin();
  deleteField(field, GAME_WINDOW_HEIGHT);

  return 0;
}

int gameLoop(GameManager *gm, WINDOW **windows) {

  int direction = 0;
  int angle = 0;
  int isEnd = 0;
  long long startTime = GetTimeInMS();
  long long endTime = 0;
  int collision = 0;
  int keyVal = 0;
  while (keyVal != 404 && isEnd == 0) {

    keyVal = inputHandler(&direction, &angle);
    // debugInfo(windows[debugWin], gm, direction, endTime - startTime);
    printMenu(windows[menuWin], gm);

    endTime = GetTimeInMS();
    collision = moveBrick(gm, &gm->currentBrick, direction, angle);
    if (endTime - startTime >= GAME_SPEED - GMAE_ACCELERATIONS * gm->lvl) {
      int tmpcol = moveBrick(gm, &gm->currentBrick, DIR_DOWN, 0);
      collision = (tmpcol == COL_STATE_CRIT || tmpcol == COL_STATE_END)
                      ? tmpcol
                      : collision;
      startTime = GetTimeInMS();
    }
    if (collision == COL_STATE_CRIT) {
      isEnd = resetBrick(gm);
      addPoints(gm, fullLineHandler(gm));
    }
    drawField(windows[gameWin], gm);
  }
  return keyVal;
}

void clearField(int **field, int rows, int cols) {

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      field[i][j] = 0;
    }
  }
}

void deleteField(int **field, int rows) {

  for (int i = 0; i < rows; i++) {
    free(field[i]);
  }
  free(field);
}

int initField(int ***field, int rows, int cols) {
  *field = (int **)calloc(rows, sizeof(int *));
  for (int i = 0; i < rows; i++) {
    (*field)[i] = (int *)calloc(cols, sizeof(int));
  }
  return 0;
}

void setUp(WINDOW **windows, int winCount, GameManager *gm, int **field) {
  srand(time(0));
  cursesSetUp();
  setUpBrickGameWindows(windows, winCount);
  initGameManager(gm, field);
}
