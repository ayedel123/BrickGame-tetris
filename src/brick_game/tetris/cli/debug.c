// #include "debug.h"


// void printField(WINDOW *debugWin, GameManager *gameManager, int *y) {
//   *y = 1;
//   for (int i = 0; i < gameManager->winInfo.height; i++) {
//     for (int j = 0; j < gameManager->winInfo.width; j++) {
//       if (gameManager->field[i][j] == 0) {
//        // mvwprintw(debugWin, i + 1 + *y, j + 1, "0");
//       } else {
//         mvwprintw(debugWin, i + 1 + *y, j + 1, "1");
//       }
//     }
//   }
// }

// void debugInfo(WINDOW *debugWin, GameManager *gameManager, int direction,
//                long long time) {
//   char s[255];
//   int y = 2;
//   printField(debugWin, gameManager, &y);
//   wrefresh(debugWin);
// }
