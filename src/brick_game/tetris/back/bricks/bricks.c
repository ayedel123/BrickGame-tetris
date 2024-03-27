#include "bricks.h"

const Brick BRICKS_TYPES[BRICK_TYPES_COUNT] = {
    {{{0, 0}, {1, 0}, {2, 0}, {3, 0}}, 0, 0, 0},
    {{{0, 0}, {0, 1}, {1, 1}, {2, 1}}, 0, 0, 0},
    {{{0, 1}, {1, 1}, {2, 1}, {2, 0}}, 0, 0, 0},
    {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, 0, 0, 0},
    {{{0, 1}, {1, 1}, {1, 0}, {2, 0}}, 0, 0, 0},
    {{{0, 1}, {1, 1}, {2, 1}, {1, 0}}, 0, 0, 0},
    {{{0, 0}, {1, 0}, {1, 1}, {2, 1}}, 0, 0, 0}};
/*
  0:  0000  1:  000   2:   0  3: 00  4:   00
                  0      000     00      00

  5:   0   6:  00
      000       00
*/

void bornBrick(Brick *brick, int x, int y, int brickType, int colorCount) {

  brickType = (brickType < 0 || brickType > BRICK_TYPES_COUNT)
                  ? rand() % BRICK_TYPES_COUNT
                  : brickType;

  *brick = BRICKS_TYPES[brickType];
  brick->x = x;
  brick->y = y;
  brick->color = (rand() % colorCount) + 1;
}
