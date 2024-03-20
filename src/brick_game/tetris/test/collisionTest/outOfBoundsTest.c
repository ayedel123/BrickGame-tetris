#include "../backTests.h"

START_TEST(case_1) {
  
  int width = 20;
  int height = 20;
  Brick brick = BRICKS_TYPES[0];
  bornBrick(&brick, 1, 0, 0, 7);
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status =
        (status == 0) ? checkOutOfBounds(&brick, i, width, height) : status;
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
    status =
        (status == 0) ? checkOutOfBounds(&brick, i, width, height) : status;
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
    status =
        (status == 0) ? checkOutOfBounds(&brick, i, width, height) : status;
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
    status =
        (status == 0) ? checkOutOfBounds(&brick, i, width, height) : status;
  }
  ck_assert_int_eq(status, COL_STATE_COL);
}
END_TEST



Suite *out_of_bounds_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("collision_bot");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);
  tcase_add_test(tc, case_3);
  tcase_add_test(tc, case_4);

  suite_add_tcase(s, tc);
  return s;
}
