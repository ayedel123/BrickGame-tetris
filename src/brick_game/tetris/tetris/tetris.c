
#include "tetris.h"

int gameLoop2(GameInfo_t *gameInfo, WINDOW **windows);

int main() {
  WINDOW *windows[3];
  GameInfo_t gameInfo;
  int **field = NULL;
  initField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);

  // int key = 0;
  // while (key != 404) {
  clearField(field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  setUp(windows, 3, &gameInfo, field, 300);
  gameLoop2(&gameInfo, windows);
  // }

  endwin();
  deleteField(field, GAME_WINDOW_HEIGHT);

  return 0;
}

int gameLoop(GameInfo_t *gameInfo, WINDOW **windows) {

  int direction = 0;
  int angle = 0;
  int isEnd = 0;
  long long startTime = GetTimeInMS();
  long long endTime = 0;
  int collision = 0;
  int keyVal = 0;
  while (keyVal != 404 && isEnd == 0) {

    keyVal = inputHandler(&direction, &angle);
    // debugInfo(windows[debugWin], gameInfo, direction, endTime - startTime);
    // printMenu(windows[menuWin], gameInfo);

    endTime = GetTimeInMS();
    collision = moveBrick(gameInfo, &gameInfo->currentBrick, direction, angle);
    if (endTime - startTime >=
        GAME_SPEED - GMAE_ACCELERATIONS * gameInfo->level) {
      int tmpcol = moveBrick(gameInfo, &gameInfo->currentBrick, DIR_DOWN, 0);
      collision = (tmpcol == COL_STATE_CRIT || tmpcol == COL_STATE_END)
                      ? tmpcol
                      : collision;
      startTime = GetTimeInMS();
    }
    if (collision == COL_STATE_CRIT) {
      isEnd = resetBrick(gameInfo);
      addPoints(gameInfo, fullLineHandler(gameInfo));
    }
    drawField(windows[gameWin], gameInfo);
  }
  return keyVal;
}

void setUp(WINDOW **windows, int winCount, GameInfo_t *gameInfo, int **field,
           int speed) {
  srand(time(0));
  cursesSetUp();
  setUpBrickGameWindows(windows, winCount);
  initGameInfo(gameInfo, field, speed);
}

int gameLoop2(GameInfo_t *gameInfo, WINDOW **windows) {

  long long startTime = GetTimeInMS();
  long long endTime = 0;
  int isEnd = 0;
  int keyVal = 0;
  int input = 0;
  tetris_state state = START;
  StartMessage(windows[gameWin], gameInfo->winInfo.width,
               gameInfo->winInfo.width);
  while (keyVal != 404 && state != EXIT_STATE) {
    input = userInput();
    *gameInfo = updateCurrentState(*gameInfo, &state, get_signal(input));
    if (state != START) {

      drawField(windows[gameWin], gameInfo);
    }
    if (state == GAMEOVER) {
      GameOverMessage(windows[gameWin], gameInfo->winInfo.width,
                      gameInfo->winInfo.width);
    }
    printMenu(windows[menuWin], gameInfo, state);
    endTime = GetTimeInMS();
    if (state == MOVING && endTime - startTime >= 20) {
      startTime = GetTimeInMS();
      *gameInfo = updateCurrentState(*gameInfo, &state, MOVE_DOWN);
    }
  }
  //  if (collision == COL_STATE_CRIT) {
  //    isEnd = resetBrick(gameInfo);
  //    addPoints(gameInfo, fullLineHandler(gameInfo));
  //  }
  return 0;
}
