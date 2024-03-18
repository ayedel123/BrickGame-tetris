#include "ui.h"

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

void drawField(WINDOW *win, GameManager *gameManager) {

  for (int i = 0; i < gameManager->winInfo.height; i++) {
    for (int j = 0; j < gameManager->winInfo.width; j++) {

      if (gameManager->field[i][j] == 0) {
        mvwprintw(win, i + 1, j + 1, " ");
      } else {
        wattron(win, COLOR_PAIR(gameManager->field[i][j]));
        mvwprintw(win, i + 1, j + 1, "0");
        wattroff(win, COLOR_PAIR(gameManager->field[i][j]));
      }
    }
  }

  wrefresh(win);
}

WINDOW *setUpWindow(WinInfo *WinInfo, int winNumber) {

  int height = GAME_WINDOW_HEIGHT + 2;
  int width = GAME_WINDOW_WIDTH + 2;
  int starty = (LINES - height) / 2;
  int startx = 2 + width * winNumber;
  char s[15];
  sprintf(s, "win %d", winNumber);
  mvprintw(starty - 1, startx + 2, s);

  refresh();
  WINDOW *localWindow = create_newwin(height, width, starty, startx);
  return localWindow;
}

void *setUpBrickGameWindows(WinInfo *winInfo, WINDOW **windows, int winCount) {
  for (int i = 0; i < winCount; i++) {
    windows[i] = setUpWindow(&winInfo[i], i);
  }
}

int inputHandler(int *direction, int *angle) {
  int ch = getch();
  int res = 0;
  *direction = 0;
  *angle = 0;
  const char str[2] = {
      ch,
  };
  ch = tolower(ch);
  switch (ch) {
  case KEY_LEFT:
    *direction = left;
    break;
  case KEY_RIGHT:
    *direction = right;
    break;
  case KEY_UP:
    *direction = top;
    break;
  case KEY_DOWN:
    *direction = down;
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
