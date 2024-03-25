#include "../backTests.h"

START_TEST(drop_lines_case_1) {
  int width = 4;
  int height = 4;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;

  gameInfo.field[0][0] = 1;
  gameInfo.field[1][0] = 2;
  gameInfo.field[2][0] = 3;
  gameInfo.field[3][0] = 4;

  dropLines(&gameInfo, 3, 1);

  ck_assert_int_eq(gameInfo.field[0][0], 0);
  ck_assert_int_eq(gameInfo.field[1][0], 1);
  ck_assert_int_eq(gameInfo.field[2][0], 2);
  ck_assert_int_eq(gameInfo.field[3][0], 3);

  deleteField(gameInfo.field, height);
}
END_TEST

START_TEST(is_line_full_case_1) {
  int width = 4;
  int height = 4;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;

  gameInfo.field[1][0] = 2;
  gameInfo.field[1][1] = 3;
  gameInfo.field[1][2] = 4;
  gameInfo.field[1][3] = 5;

  int lineId = 1;
  int isFull = isLineFull(&gameInfo, lineId);

  ck_assert_int_eq(isFull, 1);

  deleteField(gameInfo.field, height);
}
END_TEST

START_TEST(reset_brick_case_1) {
  int width = 10;
  int height = 10;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  initGameInfo(&gameInfo, field, 10, 10);
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  Brick secondBrick = gameInfo.nextBrick;

  int status = resetBrick(&gameInfo);
  ck_assert_int_eq(gameInfo.currentBrick.x, secondBrick.x);
  ck_assert_int_eq(gameInfo.currentBrick.y, secondBrick.y);
  ck_assert_int_eq(gameInfo.currentBrick.color, secondBrick.color);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(gameInfo.currentBrick.cords[i][0],
                     secondBrick.cords[i][0]);
    ck_assert_int_eq(gameInfo.currentBrick.cords[i][1],
                     secondBrick.cords[i][1]);
  }
  ck_assert_int_eq(status, 0);

  deleteField(gameInfo.field, height);
}
END_TEST

Suite *semi_linehandler_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("LineHandlerSemiFuncs");
  tc = tcase_create("test");

  tcase_add_test(tc, drop_lines_case_1);
  tcase_add_test(tc, is_line_full_case_1);
  tcase_add_test(tc, reset_brick_case_1);

  suite_add_tcase(s, tc);
  return s;
}