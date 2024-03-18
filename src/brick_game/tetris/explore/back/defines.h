#ifndef __DEFINES__
#define __DEFINES__

typedef struct Cursor {
  int x;
  int y;
} Cursor;

typedef struct WinInfo {
  int startx, starty;
  int height, width;
} WinInfo;

typedef enum directions_enum {
  top = -2,
  down = 2,
  right = 1,
  left = -1,
  state = 0
} directions_enum;

#define COL_STATE_NO_COL 0
#define COL_STATE_COL 1
#define COL_STATE_CRIT 2
#define COL_STATE_END 3
#define WINDOW_OFFSET 1

#endif