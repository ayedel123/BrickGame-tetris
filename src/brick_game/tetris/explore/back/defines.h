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
  left = -1
} directions_enum;

#define COL_STATE_NO_COL 0
#define COL_STATE_BRICK 1
#define COL_STATE_BORDER 2
#define WINDOW_OFFSET 1

#endif