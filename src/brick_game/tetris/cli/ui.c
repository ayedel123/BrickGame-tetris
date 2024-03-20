#include "ui.h"

void drawField(WINDOW *win, GameManager *gm) {

  for (int i = 0; i < gm->winInfo.height; i++) {
    for (int j = 0; j < gm->winInfo.width; j++) {

      if (gm->field[i][j] != 0) {
        wrefresh(win);
        wattron(win, COLOR_PAIR(gm->field[i][j]));
        mvwprintw(win, i + 1, j + 1, "0");
        wattroff(win, COLOR_PAIR(gm->field[i][j]));
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
  char s[15];
  sprintf(s, "win %d", winNumber);
  mvprintw(starty - 1, startx + 2, s);

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

int inputHandler(int *direction, int *angle) {
  int ch = getch();
  int res = 0;
  *direction = 0;
  *angle = 0;
  ch = tolower(ch);
  switch (ch) {
  case KEY_LEFT:
    *direction = DIR_LEFT;
    break;
  case KEY_RIGHT:
    *direction = DIR_RIGHT;
    break;
  case KEY_UP:
    *direction = DIR_TOP;
    break;
  case KEY_DOWN:
    *direction = DIR_DOWN;
    break;
  case '0':
    res = 404;
    break;
  case 'e':
    *angle = -1;
    *direction = 0;
    break;
  case 'q':
    *angle = 1;
    *direction = 0;
    break;
  case ERR:
    res = ERR;
    break;
  default:
    res = 1;
    *direction = 0;
    *angle = 0;
    break;
  }
  return res;
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
