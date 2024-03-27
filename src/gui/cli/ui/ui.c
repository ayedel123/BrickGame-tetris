#include "ui.h"

void drawField(WINDOW *win, GameInfo_t *gameInfo) {

  for (int i = 0; i < gameInfo->winInfo.height; i++) {
    for (int j = 0; j < gameInfo->winInfo.width; j++) {

      if (gameInfo->field[i][j] != 0) {
        wrefresh(win);
        wattron(win, COLOR_PAIR(gameInfo->field[i][j]));
        mvwprintw(win, i + 1, j + 1, "0");
        wattroff(win, COLOR_PAIR(gameInfo->field[i][j]));
      } else
        mvwprintw(win, i + 1, j + 1, " ");
    }
  }

  wrefresh(win);
}

WINDOW *setUpWindow(int winNumber) {

  int height = GAME_WINDOW_HEIGHT + 2;
  int width = GAME_WINDOW_WIDTH + 2;
  int starty = (LINES - height) / 2;
  int startx = 2 + width * winNumber;
  refresh();
  WINDOW *localWindow = createNewWin(height, width, starty, startx);
  return localWindow;
}

int *setUpBrickGameWindows(WINDOW **windows, int winCount) {
  for (int i = 0; i < winCount; i++) {
    windows[i] = setUpWindow(i);
  }
  return 0;
}

void initColors() {
  init_color(2, 0, 1000, 0);
  init_color(7, 1000, 400, 0);
  init_color(4, 200, 200, 1000);
  init_color(1, 1000, 200, 200);
  init_pair(1, COLOR_WHITE, 1);
  init_pair(2, COLOR_WHITE, 2);
  init_pair(3, COLOR_WHITE, 3);
  init_pair(4, COLOR_WHITE, 4);
  init_pair(5, COLOR_WHITE, 5);
  init_pair(6, COLOR_WHITE, 6);
  init_pair(7, COLOR_WHITE, 7);
}

void cursesSetUp() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  start_color();
  use_default_colors();
  curs_set(0);
  initColors();
  timeout(0);
}

void gameOverMessage(WINDOW *win, int width, int height) {
  mvwprintw(win, height / 2, 1, "game over");
  mvwprintw(win, height / 2 + 1, 1, "  press ");
  mvwprintw(win, height / 2 + 2, 1, " any key ");
  mvwprintw(win, height / 2 + 3, 1, "to start ");
  mvwprintw(win, height / 2 + 4, 1, " or 0 ");
  mvwprintw(win, height / 2 + 5, 1, "to exit ");

  wrefresh(win);
}

void startMessage(WINDOW *win, int width, int height) {
  mvwprintw(win, height / 2, 2, "  press ");
  mvwprintw(win, height / 2 + 1, 2, " any key ");
  mvwprintw(win, height / 2 + 2, 2, "to start ");
  mvwprintw(win, height / 2 + 3, 2, "  or 0 ");
  mvwprintw(win, height / 2 + 4, 2, " to exit ");
  wrefresh(win);
}