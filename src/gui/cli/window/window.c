#include "window.h"

WINDOW *createNewWin(int height, int width, int starty, int startx) {
  WINDOW *localWin;

  localWin = newwin(height, width, starty, startx);
  box(localWin, 0, 0);
  wrefresh(localWin);

  return localWin;
}
