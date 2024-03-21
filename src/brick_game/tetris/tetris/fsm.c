#include "fsm.h"

void spawHandler(GameInfo_t *gameInfo, tetris_state *state) {
  addPoints(gameInfo, fullLineHandler(gameInfo));
  if (resetBrick(gameInfo) != COL_STATE_NO)
    *state = GAMEOVER;
  else
    *state = MOVING;
}

void getMoveData(int signal, int *direction, int *angle) {
  switch (signal) {
  case MOVE_UP:
    *direction = DIR_TOP;
    break;
  case MOVE_DOWN:
    *direction = DIR_DOWN;
    break;
  case MOVE_LEFT:
    *direction = DIR_LEFT;
    break;
  case MOVE_RIGHT:
    *direction = DIR_RIGHT;
    break;
  case ROTATE_LEFT:
    *angle = -1;
    break;
  case ROTATE_RIGHT:
    *angle = 1;
    break;
  case NOSIG:
    break;
  };
}

void movingHandler(GameInfo_t *gameInfo, tetris_state *state,
                   tetris_signals signal) {
  if (signal != EXIT) {
    int direction = DIR_STATE;
    int angle = 0;
    getMoveData(signal, &direction, &angle);
    int col = moveBrick(gameInfo, &gameInfo->currentBrick, direction, angle);
    if (col == COL_STATE_CRIT) {
      *state = SPAWN;
    }
  } else
    *state = EXIT_STATE;
}

void startHandler(GameInfo_t *gameInfo, tetris_state *state,
                  tetris_signals signal) {
  if (signal != EXIT) {
    clearField(gameInfo->field, gameInfo->winInfo.height,
               gameInfo->winInfo.width);
    *state = SPAWN;
  } else if (signal == EXIT) {
    *state = EXIT_STATE;
  }
}

void gameOverHandler(tetris_state *state, tetris_signals signal) {
  if (signal != EXIT) {
    *state = START;
  } else
    *state = EXIT_STATE;
}

void exitHandler(tetris_state *state) { *state = EXIT; }

GameInfo_t updateCurrentState(GameInfo_t gameInfo, tetris_state *state,
                              tetris_signals signal) {

  switch (*state) {

  case START:
    startHandler(&gameInfo, state, signal);
    break;
  case SPAWN:
    spawHandler(&gameInfo, state);
    break;
  case MOVING:
    movingHandler(&gameInfo, state, signal);
    break;
    break;
  case GAMEOVER:
    gameOverHandler(state, signal);
    break;
  case EXIT_STATE:
    exitHandler(state);
    break;
  }
  return gameInfo;
}

tetris_signals get_signal(int userInput) {
  tetris_signals rc = NOSIG;

  if (userInput == KEY_UP)
    rc = MOVE_UP;
  else if (userInput == KEY_DOWN)
    rc = MOVE_DOWN;
  else if (userInput == KEY_LEFT)
    rc = MOVE_LEFT;
  else if (userInput == KEY_RIGHT)
    rc = MOVE_RIGHT;
  else if (userInput == KEY_ROTATE_LEFT)
    rc = ROTATE_LEFT;
  else if (userInput == KEY_ROTATE_RIGHT)
    rc = ROTATE_RIGHT;
  else if (userInput == ERR)
    rc = NOSIG;
  else if (userInput == KEY_ESCAPE)
    rc = EXIT;

  return rc;
}

int userInput() { return getch(); }