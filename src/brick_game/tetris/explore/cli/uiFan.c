#include "uiFan.h"

// void drawBrick(WINDOW *win, Brick *brick, GameManager *gameManager) {
//   wattron(win, COLOR_PAIR(brick->color));
//   for (int i = 0; i < 4; i++) {
//     if (brick->cords[i][1] != gameManager->deadDot) {
//       mvwprintw(win, brick->y + brick->cords[i][1],
//                 brick->x + brick->cords[i][0], " ");
//     }
//   }
//   wmove(win, brick->y + brick->cords[0][1], brick->x + brick->cords[0][0]);
//   wattroff(win, COLOR_PAIR(brick->color));
//   wrefresh(win);
// }

void drawField(WINDOW *win,GameManager * gameManager) {

  for(int i =0;i<gameManager->winInfo.height;i++){
   for(int j =0;j<gameManager->winInfo.width;j++){
    if(gameManager->field[i][j]==0){
      mvwprintw(win,i+1,j+1, " ");
      }else{
       mvwprintw(win,i+1,j+1, "0");
      }

  } 
  }
  wrefresh(win);
}