#include "../backTests.h"

START_TEST(case_1) {
  int width = 10;
  int height = 10;
  int **field;
  initField(&field, width, height);
  Brick brick1 = BRICKS_TYPES[0];
  bornBrick(&brick1, 1, 0, 0, 7);
  field[0][4] = 1;
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0) ? checkCollisionBrick(field, &brick1, i, DIR_RIGHT)
                           : status;
  }
  ck_assert_int_eq(status, COL_STATE_COL);
  deleteField(field, height);
}
END_TEST

START_TEST(case_2) {
  int width = 10;
  int height = 10;
  int **field;
  initField(&field, width, height);
  Brick brick1 = BRICKS_TYPES[0];
  bornBrick(&brick1, 1, 1, 0, 7);
  field[1][4] = 1;
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0) ? checkCollisionBrick(field, &brick1, i, DIR_DOWN)
                           : status;
  }
  ck_assert_int_eq(status, COL_STATE_CRIT);
  deleteField(field, height);
}
END_TEST

START_TEST(case_3) {
  int width = 10;
  int height = 10;
  int **field;
  initField(&field, width, height);
  Brick brick1 = BRICKS_TYPES[0];
  bornBrick(&brick1, 1, 0, 0, 7);
  field[0][4] = 1;
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0) ? checkCollisionBrick(field, &brick1, i, DIR_TOP)
                           : status;
  }
  ck_assert_int_eq(status, COL_STATE_COL);
  deleteField(field, height);
}
END_TEST

START_TEST(case_4) {
  int width = 10;
  int height = 10;
  int **field;
  initField(&field, width, height);
  Brick brick1 = BRICKS_TYPES[0];
  bornBrick(&brick1, 1, 0, 0, 7);
  field[0][1] = 1;
  int status = 0;
  status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0) ? checkCollisionBrick(field, &brick1, i, DIR_LEFT)
                           : status;
  }
  ck_assert_int_eq(status, COL_STATE_COL);
  deleteField(field, height);
}
END_TEST

Suite *collision_brick_suite(void) {
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
