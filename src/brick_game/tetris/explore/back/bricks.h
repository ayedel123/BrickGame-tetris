#ifndef __BRICK__
#define __BRICK__

#include <stdlib.h>
#include <time.h>

#define BRICK_TYPES_COUNT 7

typedef struct {
  int cords[4][2];
  int anchor_x;
  int anchor_y;
} Brick;

extern const Brick BRICKS_TYPES[BRICK_TYPES_COUNT];

void born_brick(Brick *brick, int x, int y, int brick_type);
void set_anchor(Brick *brick, int x, int y);

#endif