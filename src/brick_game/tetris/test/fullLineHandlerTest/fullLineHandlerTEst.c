#include "../backTests.h"

START_TEST(case_1) {
  int width = 4;
  int height = 4;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  clearField(field, height, width);
  gameInfo.field[1][0] = 1;
  gameInfo.field[1][1] = 2;
  gameInfo.field[1][2] = 3;
  gameInfo.field[1][0] = 4;

  int points = fullLineHandler(&gameInfo);
  ck_assert_int_eq(points, 0);
  deleteField(gameInfo.field, height);
}
END_TEST

START_TEST(case_2) {
  int width = 4;
  int height = 4;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  clearField(field, height, width);
  gameInfo.field[0][0] = 1;
  gameInfo.field[0][1] = 2;
  gameInfo.field[0][2] = 3;
  gameInfo.field[0][3] = 0;
  gameInfo.field[1][0] = 1;
  gameInfo.field[1][1] = 2;
  gameInfo.field[1][2] = 3;
  gameInfo.field[1][3] = 4;

  int fullLines = fullLineHandler(&gameInfo);
  ck_assert_int_eq(field[1][0], 1);
  ck_assert_int_eq(field[1][1], 2);
  ck_assert_int_eq(field[1][2], 3);
  ck_assert_int_eq(field[1][3], 0);
  ck_assert_int_eq(fullLines, 1);

  deleteField(gameInfo.field, height);
}
END_TEST

START_TEST(case_3) {
  int width = 4;
  int height = 4;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  clearField(field, height, width);
  gameInfo.field[0][0] = 1;
  gameInfo.field[0][1] = 2;
  gameInfo.field[0][2] = 3;
  gameInfo.field[0][3] = 0;
  gameInfo.field[1][0] = 1;
  gameInfo.field[1][1] = 2;
  gameInfo.field[1][2] = 3;
  gameInfo.field[1][3] = 4;
  gameInfo.field[2][0] = 1;
  gameInfo.field[2][1] = 2;
  gameInfo.field[2][2] = 3;
  gameInfo.field[2][3] = 4;
  int fullLines = fullLineHandler(&gameInfo);
  ck_assert_int_eq(field[2][0], 1);
  ck_assert_int_eq(field[2][1], 2);
  ck_assert_int_eq(field[2][2], 3);
  ck_assert_int_eq(field[2][3], 0);
  ck_assert_int_eq(fullLines, 2);

  deleteField(gameInfo.field, height);
}
END_TEST

Suite *linehandler_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("LineHandler");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);
  tcase_add_test(tc, case_3);

  suite_add_tcase(s, tc);
  return s;
}