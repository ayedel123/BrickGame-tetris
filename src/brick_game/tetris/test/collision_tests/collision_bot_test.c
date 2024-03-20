#include "../back_tests.h"

START_TEST(case_1) {
  int vertexesCount = 0;
  int facesCount = 0;
  Brick bricks[] = {BRICKS_TYPES[0], BRICKS_TYPES[0]};
  bricks[0].anchor_y = 1;
  int status = check_collision_bot(bricks, 1);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(case_2) {
  int vertexesCount = 0;
  int facesCount = 0;
  Brick bricks[] = {BRICKS_TYPES[0], BRICKS_TYPES[0]};
  bricks[0].anchor_y = 2;
  int status = check_collision_bot(bricks, 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

Suite *collision_bot_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("collision_bot");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);

  suite_add_tcase(s, tc);
  return s;
}
