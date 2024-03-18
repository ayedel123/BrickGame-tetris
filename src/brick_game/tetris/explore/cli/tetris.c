
#include "tetris.h"

long long GetTimeInMS() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}
void setUpGameManager(GameManager *gameManager, Brick *bricks, int **field);
void setUp(WinInfo *winInfo, WINDOW **windows, int winCount,
           GameManager *gameManager, Brick *bricks, int **field);
WINDOW *setUpWindow(WinInfo *WinInfo, int winNumber);
int inputHandler(int *direction, int *angle);

int main() {
  char s[255];
  WINDOW *windows[3];
  WinInfo winInfo[3];
  Brick bricks[100];
  GameManager gameManager;
  int **field = NULL;
  initField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);

  int key = 0;
  while (key != 404) {
    initGameManager(&gameManager);
    setUp(winInfo, windows, 3, &gameManager, bricks, field);
    clearField(field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    key = gameLoop(&gameManager, windows);
  }

  endwin();
  deleteField(field, GAME_WINDOW_HEIGHT);

  return 0;
}

int gameLoop(GameManager *gameManager, WINDOW **windows) {

  int direction = 0;
  int angle = 0;
  int isEnd = 0;
  long long startTime = GetTimeInMS();
  long long endTime = 0;
  int collision = 0;
  int keyVal = 0;
  while (keyVal != 404 && isEnd == 0) {
    keyVal = inputHandler(&direction, &angle);
    debugInfo(windows[debugWin], gameManager, direction, endTime - startTime);
    printMenu(windows[menuWin], gameManager, direction, endTime - startTime);

    endTime = GetTimeInMS();
    collision = handleAction(gameManager, direction, angle);
    if (endTime - startTime >= 300) {
      int tmpcol = handleAction(gameManager, down, 0);
      collision = (tmpcol == COL_STATE_CRIT || tmpcol == COL_STATE_END)
                      ? tmpcol
                      : collision;
      startTime = GetTimeInMS();
    }
    if (collision == COL_STATE_CRIT) {
      isEnd = resetBrick(gameManager);
      addPoints(gameManager, fullLineHandler(gameManager));
    }

    drawField(windows[gameWin], gameManager);
    wrefresh(windows[gameWin]);
  }
  return keyVal;
}

void setUpGameManager(GameManager *gameManager, Brick *bricks, int **field) {
  initGameManager(gameManager);
  gameManager->bricks = bricks;
  gameManager->winInfo.height = GAME_WINDOW_HEIGHT;
  gameManager->winInfo.width = GAME_WINDOW_WIDTH;
  gameManager->winInfo.startx = GAME_WINDOW_STARTX;
  gameManager->winInfo.starty = GAME_WINDOW_STARTY;
  gameManager->colorCount = COLOR_COUNT;
  gameManager->field = field;
  gameManager->record = readRecord("record");
  born_brick(&bricks[0], 1, 1, -1, COLOR_COUNT);
  born_brick(&bricks[1], 1, 1, -1, COLOR_COUNT);
}

int clearField(int **field, int rows, int cols) {

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

void setUp(WinInfo *winInfo, WINDOW **windows, int winCount,
           GameManager *gameManager, Brick *bricks, int **field) {
  srand(time(0));
  cursesSetUp();
  setUpBrickGameWindows(winInfo, windows, winCount);
  setUpGameManager(gameManager, bricks, field);
}
