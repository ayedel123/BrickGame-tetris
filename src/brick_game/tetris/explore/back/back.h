#ifndef __BACK__
#define __BACK__

#include "bricks.h"
#include "defines.h"
#include "game_manager.h"

int check_collision_bot(GameManager *gameManager);
int move_cursor(GameManager *gameManager, int direction);
int move_brick(GameManager *gameManager, int direction);
void move_currnet_anchor(GameManager *gameManager);
int check_bordercross_x(GameManager *gameManager);
void calcBrickBordesrs(GameManager *gameManager);

#endif