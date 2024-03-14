#ifndef __BRICK__
#define __BRICK__

#include <stdlib.h>
#include <time.h>

#include "defines.h"

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

void born_brick(Brick *brick, int x, int y, int brick_type, int colorCount);
void set_anchor(Brick *brick, int x, int y);

// typedef enum collison_code { no_col, bot_only, right_only, left_only ,bot};

#endif