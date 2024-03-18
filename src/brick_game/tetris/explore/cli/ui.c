#include "ui.h"

#include "uiFan.h"
#include <sys/time.h>

long long GetTimeInMS() {
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}
void setUp(WinInfo *winInfo, WINDOW **windows, int winCount,
           GameManager *gameManager, Brick *bricks, int **field);
WINDOW *setUpWindow(WinInfo *WinInfo, int winNumber);
int inputHandler(int *direction, int *angle);

int initField(int ***field, int rows, int cols) {
  *field = (int **)calloc(rows, sizeof(int *));
  for (int i = 0; i < rows; i++) {
    (*field)[i] = (int *)calloc(cols, sizeof(int));
  }
  return 0;
}

int main(int argc, char *argv[]) {
  // debug
  char s[255];
  srand(time(0));
  timeout(0);
  // setUp
  WINDOW *windows[3];
  WinInfo winInfo[3];
  int ch = 0;
  refresh();
  Brick bricks[100];
  int currentBrick = 0;
  GameManager gameManager;

  int **field = NULL;
  initField(&field, 100, 100);
  setUp(winInfo, windows, 3, &gameManager, bricks, field);

  int direction = 0;
  born_brick(&bricks[0], 1, 1, 1, COLOR_COUNT);

  // wprintw("Время выполнения программы: %f секунд\n", cpu_time_used);
  int collision = 0;
  long long startTime = GetTimeInMS();
  long long endTime = 0;
  int angle = 0;
  int forcedMove = 0;
  windows[gameWin] = setUpWindow(&winInfo[gameWin], gameWin);
  while (ch != 'O' && ch != 'o') {

    int keyVal = inputHandler(&direction, &angle);
    // debugInfo(windows[debugWin], &gameManager, direction, endTime -
    // startTime);
    //windows[gameWin] = setUpWindow(&winInfo[gameWin], gameWin);
    drawField(windows[gameWin], &gameManager);
    endTime = GetTimeInMS();

    collision = handleAction(&gameManager, direction, angle);

    if (endTime - startTime >= 300) {
      collision = (handleAction(&gameManager, down, 0) == COL_STATE_CRIT)
                      ? COL_STATE_CRIT
                      : collision;
      startTime = GetTimeInMS();
    }

    if (collision == COL_STATE_CRIT) {
      resetBrick(&gameManager);
      fullLineHandler(&gameManager);
      // deleteDots(&gameManager);
    }
  }

  endwin(); /* End curses mode		  */

  return 0;
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
void refreshAllWin(WINDOW **wins, int winCount) {
  for (int i = 0; i < winCount; i++) {
    wrefresh(wins[i]);
  }
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
  timeout(2);
}
WINDOW *setUpWindow(WinInfo *WinInfo, int winNumber) {

  int height = GAME_WINDOW_HEIGHT + 2;
  int width = GAME_WINDOW_WIDTH + 2;
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

void setUpGameManager(GameManager *gameManager, Brick *bricks, int **field) {
  init_game_manager(gameManager);
  gameManager->current_brick = 0;
  gameManager->bricks = bricks;
  gameManager->winInfo.height = GAME_WINDOW_HEIGHT;
  gameManager->winInfo.width = GAME_WINDOW_WIDTH;
  gameManager->winInfo.startx = GAME_WINDOW_STARTX;
  gameManager->winInfo.starty = GAME_WINDOW_STARTY;
  gameManager->colorCount = COLOR_COUNT;
  gameManager->field = field;
  // calcBrickBordesrs(&gameManager);
}

void setUp(WinInfo *winInfo, WINDOW **windows, int winCount,
           GameManager *gameManager, Brick *bricks, int **field) {
  cursesSetUp();
  setUpBrickGameWindows(winInfo, windows, winCount);
  setUpGameManager(gameManager, bricks, field);
}
