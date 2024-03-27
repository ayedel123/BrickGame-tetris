#ifndef __TETRIS_FSM__
#define __TETRIS_FSM__

#include "../../../gui/cli/cli.h"
#include "../back/back.h"
#include "../common/defines.h"

#include <curses.h>

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  COLLIDE,
  GAMEOVER,
  ONPAUSE,
  EXIT_STATE
} tetris_state;

typedef enum {
  MOVE_UP = 0,
  MOVE_DOWN,
  MOVE_RIGHT,
  MOVE_LEFT,
  ROTATE_LEFT,
  ROTATE_RIGHT,
  PAUSE,
  EXIT,
  START_SIG,
  NOSIG
} tetris_signals;

#define ESCAPE 27
#define KEY_ROTATE_LEFT 'q'
#define KEY_ROTATE_RIGHT 'e'
#define KEY_ESCAPE '0'
#define KEY_PAUSE ' '
#define KEY_START '\n'

GameInfo_t updateCurrentState(GameInfo_t gameInfo, tetris_state *state,
                              tetris_signals signal, WINDOW **windows);
tetris_signals getSignal(int userInput);

#endif