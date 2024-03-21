#include "../backTests.h"

START_TEST(case_1) {

  int width = 20;
  int height = 20;
  Brick brick = BRICKS_TYPES[0];
  bornBrick(&brick, 1, 0, 0, 7);
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0)
                 ? checkOutOfBounds(&brick, i, width, height, DIR_RIGHT)
                 : status;
  }
  ck_assert_int_eq(status, COL_STATE_NO);
}
END_TEST

START_TEST(case_2) {

  int width = 4;
  int height = 3;
  Brick brick = BRICKS_TYPES[0];
  bornBrick(&brick, 1, 0, 0, 7);
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0)
                 ? checkOutOfBounds(&brick, i, width, height, DIR_RIGHT)
                 : status;
  }
  ck_assert_int_eq(status, COL_STATE_COL);
}
END_TEST

START_TEST(case_3) {

  int width = 4;
  int height = 1;
  Brick brick = BRICKS_TYPES[0];
  bornBrick(&brick, 1, 0, 4, 7);
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0)
                 ? checkOutOfBounds(&brick, i, width, height, DIR_DOWN)
                 : status;
  }
  ck_assert_int_eq(status, COL_STATE_CRIT);
}
END_TEST

START_TEST(case_4) {

  int width = 4;
  int height = 3;
  Brick brick = BRICKS_TYPES[0];
  bornBrick(&brick, -1, 0, 0, 7);
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0)
                 ? checkOutOfBounds(&brick, i, width, height, DIR_DOWN)
                 : status;
  }
  ck_assert_int_eq(status, COL_STATE_COL);
}
END_TEST

START_TEST(case_5) {
  int width = 4;
  int height = 5;
  int **field;
  initField(&field, height, width);
  Brick brick = BRICKS_TYPES[0];
  bornBrick(&brick, 1, 0, 0, 7);
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = checkOutOfBounds(&brick, i, width, height, DIR_DOWN);
  }
  ck_assert_int_eq(status, COL_STATE_COL);
  // for (int i = 0; i < 4; i++) {
  //   ck_assert_int_eq(
  //       field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
  //       brick.color);
  //   ck_assert_int_eq(brick.cords[i][0], brick2.cords[i][0]);
  //   ck_assert_int_eq(brick.cords[i][1], brick2.cords[i][1]);
  // }
  deleteField(field, height);
}
END_TEST

Suite *out_of_bounds_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("outOfBound");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);
  tcase_add_test(tc, case_3);
  tcase_add_test(tc, case_4);
  tcase_add_test(tc, case_5);

  suite_add_tcase(s, tc);
  return s;
}
