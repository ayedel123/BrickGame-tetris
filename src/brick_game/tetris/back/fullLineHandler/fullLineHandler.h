#ifndef __TETRIS_FULL_LINE_HANDLER__
#define __TETRIS_FULL_LINE_HANDLER__

#include "../brickMovement/checkCollision.h"
#include "../gameInfo/gameInfo.h"

int fullLineHandler(GameInfo_t *gameInfo);

int isLineFull(GameInfo_t *gameInfo, int lineId);
void dropLines(GameInfo_t *gameInfo, int lastLine, int linesCount);
int resetBrick(GameInfo_t *gameInfo);

#endif