#include "bricks.h"

// int **BRICKS_TYPES[BRICK_TYPES_COUNT] = {{{1, 0}, {2, 0}, {3, 0}}};

const Brick BRICKS_TYPES[BRICK_TYPES_COUNT] = {
    {{{0, 0}, {1, 0}, {2, 0}, {3, 0}}, 0, 0, 0},
    {{{0, 0}, {0, 1}, {1, 1}, {2, 1}}, 0, 0, 0},
    {{{0, 1}, {1, 1}, {2, 1}, {2, 0}}, 0, 0, 0},
    {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, 0, 0, 0},
    {{{0, 1}, {1, 1}, {1, 0}, {2, 0}}, 0, 0, 0},
    {{{0, 1}, {1, 1}, {2, 1}, {1, 0}}, 0, 0, 0},
    {{{0, 0}, {1, 0}, {1, 1}, {2, 1}}, 0, 0, 0}};
/*
  0:  0000  1:  00   2:   0  3: 00  4:   00
                 00     000     00      00

  5:   0   6:  00
      000       00
*/

void born_brick(Brick *brick, int x, int y, int brick_type, int colorCount) {

  brick_type = (brick_type < 0 || brick_type > BRICK_TYPES_COUNT)
                   ? rand() % BRICK_TYPES_COUNT
                   : brick_type;
  // int brick_type = 0;

  *brick = BRICKS_TYPES[brick_type];
  brick->color = (rand() % colorCount)+1;
}
