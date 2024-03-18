#include "menu.h"
#include <ncurses.h>
void printPoints(WINDOW *menuWin, int points, int record, int *y) {

  mvwprintw(menuWin, *y, 1, "points");
  mvwprintw(menuWin, *y + 1, 1, "%d", points);
  mvwprintw(menuWin, *y + 2, 1, "record");
  mvwprintw(menuWin, *y + 3, 1, "%d", record);
  (*y) += 4;
}

void printNextBrick(WINDOW *menuWin, Brick *next, int *y) {

  mvwprintw(menuWin, *y, 1, "next:");
  (*y)++;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mvwprintw(menuWin, *y + 1 + i, j + 3, " ");
    }
  }
  wattron(menuWin, COLOR_PAIR(next->color));

  for (int i = 0; i < 4; i++) {
    mvwprintw(menuWin, *y + 1 + next->cords[i][1], next->cords[i][0] + 3, "$");
  }
  wattroff(menuWin, COLOR_PAIR(next->color));
}

void printMenu(WINDOW *menuWin, GameManager *gameManager, int direction,
               long long time) {
  char s[255] = "game menu";
  int y = 1;
  mvwprintw(menuWin, y, 1, "game menu");
  y++;
  printPoints(menuWin, gameManager->points, gameManager->record, &y);
  printNextBrick(menuWin, &gameManager->bricks[gameManager->current_brick + 1],
                 &y);
  // printField(debugWin, gameManager, &y);
  wrefresh(menuWin);
}