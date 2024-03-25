#include "../backTests.h"

START_TEST(case_1) {
  int width = 10;
  int height = 2;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  initGameInfo(&gameInfo, field, 10, 10);
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  addPoints(&gameInfo, 600);
  ck_assert_int_eq(gameInfo.points, 600);
  ck_assert_int_eq(gameInfo.level, 2);
  deleteField(gameInfo.field, height);
}
END_TEST

START_TEST(case_2) {
  int width = 10;
  int height = 2;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  initGameInfo(&gameInfo, field, 10, 10);
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  addPoints(&gameInfo, 1500);
  ck_assert_int_eq(gameInfo.points, 1500);
  ck_assert_int_eq(gameInfo.level, 3);
  deleteField(gameInfo.field, height);
}
END_TEST

Suite *add_points_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("AdPointsTest");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);

  suite_add_tcase(s, tc);
  return s;
}