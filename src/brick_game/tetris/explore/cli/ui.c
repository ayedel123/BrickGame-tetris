#include "ui.h"
#include "../back/back.h"

void fixCursor(int *x, int *y, int rs, int ls);
void drawBrick(WINDOW *win, Brick *brick);
//void calcBrickBordesrs(Brick *brick, int *rs, int *ls);
void resset_brick(Brick *new_brick, int *currnet_brick, int *cx, int *cy);

int main(int argc, char *argv[]) {
  srand(time(0));
  WINDOW *my_win;
  int startx, starty, width, height;
  int ch = 0;

  initscr(); /* Start curses mode 		*/
  cbreak();  /* Line buffering disabled, Pass on
              * everty thing to me 		*/
  noecho();
  keypad(stdscr, TRUE);
  height = 22;
  width = 12;
  starty = (LINES - height) / 2;
  startx = (COLS - width) / 2;

  int cursor_x = 2;
  int cursor_y = 2;

  printw("Press ESC to exit");
  refresh();
  my_win = create_newwin(height, width, starty, startx);
  WINDOW *menu = create_newwin(height, width, starty, startx + width);
  char s[255];

  Brick bricks[100];
  int currentBrick = 0;
  born_brick(&bricks[0], cursor_x, cursor_y, -1);
  int brick_ls = 0;
  int brick_rs = 0;
  //calcBrickBordesrs(&bricks[0], &brick_rs, &brick_ls);

  GameManager gameManager;
  init_game_manager(&gameManager);
  gameManager.current_brick = 0;
  gameManager.bricks = bricks;
  gameManager.cursor.x = 2;
  gameManager.cursor.y = 2;
  gameManager.winInfo.height = GAME_WINDOW_HEIGHT;
  gameManager.winInfo.width = GAME_WINDOW_WIDTH;
  gameManager.winInfo.startx = GAME_WINDOW_STARTX;
  gameManager.winInfo.starty = GAME_WINDOW_STARTY;
  // gameManager.brickBorder.right = brick_rs;
  // gameManager.brickBorder.left = brick_ls;
  // gameManager.brickBorder.top = 0;
  // gameManager.brickBorder.bottom = 0;
  calcBrickBordesrs(&gameManager);

  int direction = 0;
  // wrefresh(my_win);
  while (ch != 'O' && ch != 'o') {
    ch = getch();
    const char str[2] = {
        ch,
    };
    switch (ch) {
    case KEY_LEFT:
      // cursor_x--;
      direction = left;
      mvwprintw(menu, 3, 1, "LEFT ");
      break;
    case KEY_RIGHT:
      // cursor_x++;
      direction = right;
      mvwprintw(menu, 3, 1, "RIGHT");
      break;
    case KEY_UP:
      // cursor_y--;
      direction = top;
      mvwprintw(menu, 3, 1, "UP   ");
      break;
    case KEY_DOWN:
      // cursor_y++;
      direction = down;
      mvwprintw(menu, 3, 1, "DOWN ");
      break;
    case '0':
      cursor_y = height / 2;
      cursor_x = width / 2;
      break;
    }
    wclear(my_win);
    my_win = create_newwin(height, width, starty, startx);

    sprintf(s, "%3d %3d", gameManager.cursor.x, gameManager.cursor.y);
    mvwprintw(menu, 2, 2, s);
    sprintf(s, "bd %3d %3d", gameManager.brickBorder.right,
            gameManager.brickBorder.left);
    mvwprintw(menu, 5, 1, s);
    sprintf(s, "aw %3d %3d",
            gameManager.bricks[gameManager.current_brick].anchor_x,
            gameManager.winInfo.width);
    mvwprintw(menu, 6, 1, s);
    int check = move_brick(&gameManager, direction);
    sprintf(s, "check %3d", check);
    mvwprintw(menu, 7, 1, s);
    wrefresh(menu);

    wattron(my_win, A_REVERSE);
    // fixCursor(&cursor_x, &cursor_y, brick_rs, brick_ls);
    // set_anchor(&bricks[currentBrick], cursor_x, cursor_y);
    //  mvwprintw(my_win, cursor_y, cursor_x, " ");
    wrefresh(my_win);

    for (int i = 0; i <= currentBrick; i++) {
      drawBrick(my_win, &bricks[i]);
    }

    wattroff(my_win, A_REVERSE);
    wmove(my_win, cursor_y, cursor_x);

    // if (cursor_y + brick_ls >= GAME_WINDOW_HEIGHT - 2 ||
    //     check_collision_bot(bricks, currentBrick)) {
    //   resset_brick(&bricks[currentBrick + 1], &currentBrick, &cursor_x,
    //                &cursor_y);
    // }
  }

  endwin(); /* End curses mode		  */
  return 0;
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

// void calcBrickBordesrs(Brick *brick, int *rs, int *ls) {
//   int lrs = 0;
//   int lls = 0;

//   for (int i = 0; i < 4; i++) {
//     lrs = (lrs > brick->cords[i][0]) ? lrs : brick->cords[i][0];
//     lls = (lls > brick->cords[i][1]) ? lls : brick->cords[i][1];
//   }
//   *rs = lrs;
//   *ls = lls;
// }

void resset_brick(Brick *new_brick, int *currnet_brick, int *cx, int *cy) {
  (*currnet_brick)++;
  *cx = 1;
  *cy = 1;
  born_brick(new_brick, *cx, *cy, -1);
}
