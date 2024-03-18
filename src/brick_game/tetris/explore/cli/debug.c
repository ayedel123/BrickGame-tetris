#include "debug.h"

void printCursorInfo(WINDOW *debugWin, GameManager *gameManager, int direction,
                     int *y, char *s) {
  sprintf(s, "%3d %3d", gameManager->cursor.x, gameManager->cursor.y);
  mvwprintw(debugWin, *y, 2, s);
  (*y)++;
  switch (direction) {
  case top:
    mvwprintw(debugWin, *y, 2, "top");
    break;
  case down:
    mvwprintw(debugWin, *y, 2, "down");
    break;
  case right:
    mvwprintw(debugWin, *y, 2, "right");
    break;
  case left:
    mvwprintw(debugWin, *y, 2, "left");
    break;
  }
  (*y)++;
}

void printBrick(WINDOW *debugWin, GameManager *gameManager, int *y, char *s) {
  sprintf(s, "012345");
  mvwprintw(debugWin, *y, 3, s);
  (*y)++;
  for (int i = 0; i < 4; i++) {
    sprintf(s, "%d", i);
    mvwprintw(debugWin, *y + i, 2, s);
  }
  for (int i = 0; i < 4; i++) {
    sprintf(s, "0");
    mvwprintw(
        debugWin,
        *y + 1 + gameManager->bricks[gameManager->current_brick].cords[i][1],
        3 + gameManager->bricks[gameManager->current_brick].cords[i][0], s);
  }
}

void printBrickBorder(WINDOW *debugWin, GameManager *gameManager, int *y,
                      char *s) {

  sprintf(s, "border");
  mvwprintw(debugWin, *y, 2, s);
  (*y)++;

  sprintf(s, "%d %d", gameManager->bricks[gameManager->current_brick].x,
          gameManager->bricks[gameManager->current_brick].y);
  mvwprintw(debugWin, *y, 2, s);
  sprintf(s, "%d", gameManager->brickBorder.top);
  mvwprintw(debugWin, *y, 7, s);
  (*y)++;
  sprintf(s, "%d %d %d", gameManager->brickBorder.left,
          gameManager->brickBorder.bottom, gameManager->brickBorder.right);
  mvwprintw(debugWin, *y, 5, s);
  (*y)++;
}

void printTime(WINDOW *debugWin, long long time, int *y, char *s) {
  sprintf(s, "%10ld ms", time);
  (*y)++;
  (*y)++;
  mvwprintw(debugWin, *y, 2, s);
  (*y)++;
}

void printField(WINDOW *debugWin,GameManager * gameManager, int *y){
    for(int i =0;i<gameManager->winInfo.height;i++){
   for(int j =0;j<gameManager->winInfo.width;j++){
    if(gameManager->field[i][j]==0){
      mvwprintw(debugWin,i+*y,j, "0");
      }else{
       mvwprintw(debugWin,i+*y,j, "1");
      }

  } 
  }
}

void debugInfo(WINDOW *debugWin, GameManager *gameManager, int direction,
               long long time) {
  char s[255];
  int y = 2;
  printCursorInfo(debugWin, gameManager, direction, &y, s);
  printBrickBorder(debugWin, gameManager, &y, s);
  printTime(debugWin, time, &y, s);
  printField(debugWin,gameManager, &y);
  // printBrick(debugWin, gameManager, &y, s);
  //    sprintf(s, "bd %3d %3d", gameManager.brickBorder.right,
  //            gameManager.brickBorder.left);
  //    // mvwprintw(menu, 5, 1, s);
  //    sprintf(s, "aw %3d %3d",
  //            gameManager.bricks[gameManager.current_brick].x,
  //            gameManager.winInfo.width);
  //  mvwprintw(menu, 6, 1, s);s
  wrefresh(debugWin);
}
