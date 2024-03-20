#ifndef __DEFINES__
#define __DEFINES__

typedef struct WinInfo {
  int height, width;
} WinInfo;

typedef enum directions_enum {
  DIR_TOP = -2,
  DIR_DOWN = 2,
  DIR_RIGHT = 1,
  DIR_LEFT = -1,
  DIR_STATE = 0
} DIRECTIONS_ENUM;

#define COL_STATE_NO 0
#define COL_STATE_COL 1
#define COL_STATE_CRIT 2
#define COL_STATE_END 3

#define WINDOW_OFFSET 1
#define GAME_WINDOW_HEIGHT 20
#define GAME_WINDOW_WIDTH 10
#define GAME_WINDOW_STARTX 0
#define GAME_WINDOW_STARTY 0

#define COLOR_COUNT 7

#endif