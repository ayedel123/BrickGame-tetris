#ifndef __BRICK__
#define __BRICK__

#include <stdlib.h>
#include <time.h>

#include "../../common/defines.h"

#define BRICK_TYPES_COUNT 7

typedef struct {
  int cords[4][2];
  int x;
  int y;
  int color;
} Brick;

typedef struct {
  int left;
  int right;
  int bottom;
  int top;
} BrickBorder;

extern const Brick BRICKS_TYPES[BRICK_TYPES_COUNT];

void bornBrick(Brick *brick, int x, int y, int brickType, int colorCount);


#endif