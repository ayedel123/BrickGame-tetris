#ifndef __WINDOW__
#define __WINDOW__

#include <ncurses.h>

// typedef struct _win_border_struct {
// 	chtype 	ls, rs, ts, bs,
// 	 	tl, tr, bl, br;
// }MY_WIN_BORDER;

typedef struct WinInfo {
  int startx, starty;
  int height, width;
} WinInfo;

// void init_win_params(WIN *p_win);
// void print_win_params(WIN *p_win);
// void create_box(WIN *WIN, bool flag);


WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

#endif