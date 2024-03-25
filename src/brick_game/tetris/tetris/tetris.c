
#include "tetris.h"

void setUp(WINDOW **windows, int winCount, GameInfo_t *gameInfo, int **field) {
  srand(time(0));
  cursesSetUp();
  setUpBrickGameWindows(windows, winCount);
  initGameInfo(gameInfo, field, GAME_SPEED, GMAE_ACCELERATION);
}

int gameLoop(GameInfo_t *gameInfo, WINDOW **windows) {

  long long startTime = getTimeInMS();
  long long endTime = 0;
  int isEnd = 0;
  int keyVal = 0;
  int input = 0;
  tetris_state state = START;

  while (keyVal != 404 && state != EXIT_STATE) {
    input = userInput();
    *gameInfo =
        updateCurrentState(*gameInfo, &state, getSignal(input), windows);

    endTime = getTimeInMS();
    if (state == MOVING &&
        endTime - startTime >=
            gameInfo->speed - gameInfo->level * gameInfo->acceleration) {
      startTime = getTimeInMS();
      *gameInfo = updateCurrentState(*gameInfo, &state, MOVE_DOWN, windows);
    }
  }

  return 0;
}

int main() {
  WINDOW *windows[3];
  GameInfo_t gameInfo;
  int **field = NULL;
  initField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  clearField(field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  setUp(windows, 2, &gameInfo, field);
  gameLoop(&gameInfo, windows);
  endwin();
  deleteField(field, GAME_WINDOW_HEIGHT);

  return 0;
}