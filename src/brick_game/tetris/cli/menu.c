#include "menu.h"

void printPoints(WINDOW *menuWin, GameInfo_t *gameInfo, int *y) {
  mvwprintw(menuWin, *y, 1, "%2d lvl", gameInfo->level);
  mvwprintw(menuWin, *y + 2, 1, "points");
  mvwprintw(menuWin, *y + 3, 1, "%5d", gameInfo->points);
  mvwprintw(menuWin, *y + 5, 1, "record");
  mvwprintw(menuWin, *y + 6, 1, "%5d", gameInfo->highScore);
  (*y) += 8;
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

void printMenu(WINDOW *menuWin, GameInfo_t *gameInfo, int state) {

  int y = 1;
  mvwprintw(menuWin, y, 1, "game menu");
  y++;
  printPoints(menuWin, gameInfo, &y);
  printNextBrick(menuWin, &gameInfo->nextBrick, &y);
  mvwprintw(menuWin, y + 5, 1, "state%3d", state);
  wrefresh(menuWin);
}