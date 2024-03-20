#include "../backTests.h"

START_TEST(drop_lines_case_1) {
  int width = 4;
  int height = 4;
  int **field;
  initField(&field, width, height);
  GameManager gm;
  gm.field = field;
  gm.winInfo.height = height;
  gm.winInfo.width = width;

  gm.field[0][0] = 1;
  gm.field[1][0] = 2;
  gm.field[2][0] = 3;
  gm.field[3][0] = 4;

  dropLines(&gm, 3, 1);

  ck_assert_int_eq(gm.field[0][0], 0);
  ck_assert_int_eq(gm.field[1][0], 1);
  ck_assert_int_eq(gm.field[2][0], 2);
  ck_assert_int_eq(gm.field[3][0], 3);

  deleteField(gm.field, height);
}
END_TEST

START_TEST(is_line_full_case_1) {
  int width = 4;
  int height = 4;
  int **field;
  initField(&field, width, height);
  GameManager gm;
  gm.field = field;
  gm.winInfo.height = height;
  gm.winInfo.width = width;

  gm.field[1][0] = 2;
  gm.field[1][1] = 3;
  gm.field[1][2] = 4;
  gm.field[1][3] = 5;

  int lineId = 1;
  int isFull = isLineFull(&gm, lineId);

  ck_assert_int_eq(isFull, 1);

  deleteField(gm.field, height);
}
END_TEST

Suite *drop_lines_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("LineHandlerSemiFuncs");
  tc = tcase_create("test");

  tcase_add_test(tc, drop_lines_case_1);
  tcase_add_test(tc, is_line_full_case_1);

  suite_add_tcase(s, tc);
  return s;
}