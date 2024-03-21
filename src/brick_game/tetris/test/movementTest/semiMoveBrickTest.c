#include "../backTests.h"

START_TEST(move_brick_cords_case_1) {
  Brick brick = BRICKS_TYPES[0];
  bornBrick(&brick, 1, 0, 0, 7);
  moveBrickCords(&brick, DIR_RIGHT);
  ck_assert_int_eq(brick.x, 2);
  ck_assert_int_eq(brick.y, 0);
}
END_TEST

START_TEST(move_brick_cords_case_2) {
  Brick brick = BRICKS_TYPES[0];
  bornBrick(&brick, 1, 0, 0, 7);
  moveBrickCords(&brick, DIR_DOWN);
  ck_assert_int_eq(brick.x, 1);
  ck_assert_int_eq(brick.y, 1);
}
END_TEST

START_TEST(rotate_brick_cords_case_1) {
  Brick brick1 = BRICKS_TYPES[0];
  Brick brick2 = BRICKS_TYPES[0];
  bornBrick(&brick1, 0, 0, 0, 7);
  bornBrick(&brick2, 0, 0, 0, 7);
  brick2.cords[0][0] = 0;
  brick2.cords[0][1] = 0;
  brick2.cords[1][0] = 0;
  brick2.cords[1][1] = 1;
  brick2.cords[2][0] = 0;
  brick2.cords[2][1] = 2;
  brick2.cords[3][0] = 0;
  brick2.cords[3][1] = 3;
  rotateBrickCords(&brick1, -1);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(brick1.cords[i][0], brick2.cords[i][0]);
    ck_assert_int_eq(brick1.cords[i][1], brick2.cords[i][1]);
  }
}
END_TEST

START_TEST(rotate_brick_cords_case_2) {
  Brick brick1 = BRICKS_TYPES[0];
  Brick brick2 = BRICKS_TYPES[0];
  bornBrick(&brick1, 0, 0, 0, 7);
  bornBrick(&brick2, 0, 0, 0, 7);
  brick2.cords[0][0] = 0;
  brick2.cords[0][1] = 0;
  brick2.cords[1][0] = 0;
  brick2.cords[1][1] = -1;
  brick2.cords[2][0] = 0;
  brick2.cords[2][1] = -2;
  brick2.cords[3][0] = 0;
  brick2.cords[3][1] = -3;
  rotateBrickCords(&brick1, 1);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(brick1.cords[i][0], brick2.cords[i][0]);
    ck_assert_int_eq(brick1.cords[i][1], brick2.cords[i][1]);
  }
}
END_TEST

START_TEST(rotate_brick_cords_case_3) {
  Brick brick1 = BRICKS_TYPES[0];
  Brick brick2 = BRICKS_TYPES[0];
  bornBrick(&brick1, 0, 0, 6, 7);
  bornBrick(&brick2, 0, 0, 6, 7);
  brick2.cords[0][0] = 0;
  brick2.cords[0][1] = 0;
  brick2.cords[1][0] = 0;
  brick2.cords[1][1] = 1;
  brick2.cords[2][0] = -1;
  brick2.cords[2][1] = 1;
  brick2.cords[3][0] = -1;
  brick2.cords[3][1] = 2;
  rotateBrickCords(&brick1, -1);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(brick1.cords[i][0], brick2.cords[i][0]);
    ck_assert_int_eq(brick1.cords[i][1], brick2.cords[i][1]);
  }
}
END_TEST

START_TEST(move_in_field_case_1) {
  Brick brick1 = BRICKS_TYPES[0];
  bornBrick(&brick1, 0, 0, 3, 7);
  int **field;
  int rows = 10;
  int cols = 10;
  initField(&field, rows, cols);
  moveBrickInField(field, &brick1);
  ck_assert_int_eq(field[brick1.y][brick1.x], brick1.color);
  ck_assert_int_eq(field[brick1.y][brick1.x + 1], brick1.color);
  ck_assert_int_eq(field[brick1.y + 1][brick1.x], brick1.color);
  ck_assert_int_eq(field[brick1.y + 1][brick1.x + 1], brick1.color);
  deleteField(field, rows);
}
END_TEST

START_TEST(delete_from_field_case_1) {
  Brick brick1 = BRICKS_TYPES[0];
  bornBrick(&brick1, 0, 0, 5, 7);
  int **field;
  int rows = 10;
  int cols = 10;
  initField(&field, rows, cols);
  moveBrickInField(field, &brick1);
  ck_assert_int_eq(field[brick1.y][brick1.x + 1], brick1.color);
  ck_assert_int_eq(field[brick1.y + 1][brick1.x], brick1.color);
  ck_assert_int_eq(field[brick1.y + 1][brick1.x + 1], brick1.color);
  ck_assert_int_eq(field[brick1.y + 1][brick1.x + 2], brick1.color);
  deleteFromField(field, &brick1);
  ck_assert_int_eq(field[brick1.y][brick1.x + 1], 0);
  ck_assert_int_eq(field[brick1.y + 1][brick1.x], 0);
  ck_assert_int_eq(field[brick1.y + 1][brick1.x + 1], 0);
  ck_assert_int_eq(field[brick1.y + 1][brick1.x + 2], 0);
  deleteField(field, rows);
}
END_TEST

Suite *semi_move_brick_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("collision_bot");
  tc = tcase_create("test");

  tcase_add_test(tc, move_brick_cords_case_1);
  tcase_add_test(tc, move_brick_cords_case_2);
  tcase_add_test(tc, rotate_brick_cords_case_1);
  tcase_add_test(tc, rotate_brick_cords_case_2);
  tcase_add_test(tc, rotate_brick_cords_case_3);
  tcase_add_test(tc, move_in_field_case_1);
  tcase_add_test(tc, delete_from_field_case_1);

  suite_add_tcase(s, tc);
  return s;
}
