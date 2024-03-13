#include "ui.h"
#include "../back/back.h"
#include "debug.h"

void fixCursor(int *x, int *y, int rs, int ls);
void drawBrick(WINDOW *win, Brick *brick);
void setUp(WinInfo *winInfo, WINDOW **windows, int winCount,
           GameManager *gameManager, Brick *bricks);
WINDOW *setUpWindow(WinInfo *WinInfo, int winNumber);
int inputHandler(int *direction);

int main(int argc, char *argv[]) {
  // debug
  char s[255];
  srand(time(0));

  // setUp
  WINDOW *windows[3];
  WinInfo winInfo[3];
  int ch = 0;
  refresh();
  Brick bricks[100];
  int currentBrick = 0;
  GameManager gameManager;
  setUp(winInfo, windows, 3, &gameManager, bricks);
  int direction = 0;
  born_brick(&bricks[0], 1, 1, 0);
  calcBrickBordesrs(&gameManager);

  while (ch != 'O' && ch != 'o') {
    int angle = inputHandler(&direction);
    if (angle) {
      rotate(&gameManager, angle);
      calcBrickBordesrs(&gameManager);
    }
    debugInfo(windows[debugWin], &gameManager, direction);
    wclear(windows[gameWin]);
    windows[gameWin] = setUpWindow(&winInfo[gameWin], gameWin);
    int check = move_brick(&gameManager, direction);
    for (int i = 0; i <= gameManager.current_brick; i++) {
      drawBrick(windows[gameWin], &bricks[i]);
    }
    if (check == COL_STATE_CRIT) {
      resetBrick(&gameManager);
    }
  }

  endwin(); /* End curses mode		  */
  return 0;
}

int inputHandler(int *direction) {
  int ch = getch();
  int angle = 0;
  const char str[2] = {
      ch,
  };
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
    break;
  case 'Q':
    angle = 1;
    *direction = 0;
    break;
  case 'E':
    angle = -1;
    *direction = 0;
    break;
  default:
    *direction = 0;
    break;
  }

  return angle;
}

void drawBrick(WINDOW *win, Brick *brick) {
  for (int i = 0; i < 4; i++) {
    mvwprintw(win, brick->anchor_y + brick->cords[i][1],
              brick->anchor_x + brick->cords[i][0], "O");
  }
  wmove(win, brick->anchor_y, brick->anchor_x);
  wrefresh(win);
}

void fixCursor(int *x, int *y, int rs, int ls) {

  *x = (*x >= GAME_WINDOW_WIDTH - 1 - rs) ? GAME_WINDOW_WIDTH - 2 - rs
       : (*x <= 0)                        ? 1
                                          : *x;
  *y = (*y >= GAME_WINDOW_HEIGHT - 1 - ls) ? GAME_WINDOW_HEIGHT - 2 - ls
       : (*y <= 0)                        ? 
                                           : *y;
}

void refreshAllWin(WINDOW **wins, int winCount) {
  for (int i = 0; i < winCount; i++) {
    wrefresh(wins[i]);
  }
}

void cursesSetUp() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}
WINDOW *setUpWindow(WinInfo *WinInfo, int winNumber) {

  int height = GAME_WINDOW_HEIGHT;
  int width = GAME_WINDOW_WIDTH;
  int starty = (LINES - height) / 2;
  // int startx = (COLS - width) / 2 + width * winNumber;
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

void setUpGameManager(GameManager *gameManager, Brick *bricks) {
  init_game_manager(gameManager);
  gameManager->current_brick = 0;
  gameManager->bricks = bricks;
  gameManager->cursor.x = 1;
  gameManager->cursor.y = 1;
  gameManager->winInfo.height = GAME_WINDOW_HEIGHT;
  gameManager->winInfo.width = GAME_WINDOW_WIDTH;
  gameManager->winInfo.startx = GAME_WINDOW_STARTX;
  gameManager->winInfo.starty = GAME_WINDOW_STARTY;
  // calcBrickBordesrs(&gameManager);
}

void setUp(WinInfo *winInfo, WINDOW **windows, int winCount,
           GameManager *gameManager, Brick *bricks) {
  cursesSetUp();
  setUpBrickGameWindows(winInfo, windows, winCount);
  setUpGameManager(gameManager, bricks);
}
