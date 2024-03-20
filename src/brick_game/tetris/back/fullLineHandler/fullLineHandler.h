#ifndef __TETRIS_FULL_LINE_HANDLER__
#define __TETRIS_FULL_LINE_HANDLER__

#include "../gameManager/gameManager.h"
#include "../brickMovement/checkCollision.h"

int fullLineHandler(GameManager *gm);

int isLineFull(GameManager *gm, int lineId);
void dropLines(GameManager *gm, int lastLine, int linesCount);
int resetBrick(GameManager *gm);

#endif