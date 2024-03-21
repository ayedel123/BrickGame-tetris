#include "../backTests.h"

START_TEST(move_brick_case_1) {
  int width = 10;
  int height = 10;
  int **field;
  initField(&field, height, width);
  GameInfo_t gameInfo;
  baseInitGameInfo(&gameInfo);
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  Brick brick = BRICKS_TYPES[0];
  gameInfo.currentBrick = brick;
  bornBrick(&brick, 1, 0, 0, 7);

  int status = moveBrick(&gameInfo, &brick, DIR_RIGHT, 0);

  ck_assert_int_eq(status, COL_STATE_NO);
  ck_assert_int_eq(brick.x, 2);
  ck_assert_int_eq(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(
        field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
        brick.color);
  }
  deleteField(field, height);
}
END_TEST

START_TEST(move_brick_case_2) {
  int width = 5;
  int height = 5;
  int **field;
  initField(&field, height, width);
  GameInfo_t gameInfo;
  baseInitGameInfo(&gameInfo);
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  Brick brick = BRICKS_TYPES[0];
  gameInfo.currentBrick = brick;

  bornBrick(&brick, 1, 0, 0, 7);
  Brick brick2 = brick;
  int status = moveBrick(&gameInfo, &brick, DIR_RIGHT, 0);
  ck_assert_int_eq(status, COL_STATE_COL);
  ck_assert_int_eq(brick.x, 1);
  ck_assert_int_eq(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(
        field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
        brick.color);
    ck_assert_int_eq(brick.cords[i][0], brick2.cords[i][0]);
    ck_assert_int_eq(brick.cords[i][1], brick2.cords[i][1]);
  }
  deleteField(field, height);
}
END_TEST

START_TEST(move_brick_case_3) {
  int width = 10;
  int height = 10;
  int **field;
  initField(&field, height, width);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  Brick brick = BRICKS_TYPES[0];
  gameInfo.currentBrick = brick;

  bornBrick(&brick, 0, 0, 0, 7);
  Brick brick2;
  bornBrick(&brick2, 0, 0, 0, 7);
  brick2.cords[0][0] = 0;
  brick2.cords[0][1] = 0;
  brick2.cords[1][0] = 0;
  brick2.cords[1][1] = 1;
  brick2.cords[2][0] = 0;
  brick2.cords[2][1] = 2;
  brick2.cords[3][0] = 0;
  brick2.cords[3][1] = 3;
  int status = moveBrick(&gameInfo, &brick, DIR_STATE, -1);

  ck_assert_int_eq(status, COL_STATE_NO);
  ck_assert_int_eq(brick.x, 0);
  ck_assert_int_eq(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(
        field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
        brick.color);
    ck_assert_int_eq(brick.cords[i][0], brick2.cords[i][0]);
    ck_assert_int_eq(brick.cords[i][1], brick2.cords[i][1]);
  }
  deleteField(field, height);
}

START_TEST(move_brick_case_4) {
  int width = 10;
  int height = 3;
  int **field;
  initField(&field, height, width);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  Brick brick = BRICKS_TYPES[0];
  gameInfo.currentBrick = brick;

  bornBrick(&brick, 0, 0, 0, 7);
  Brick brick2 = brick;

  int status = moveBrick(&gameInfo, &brick, DIR_STATE, -1);

  ck_assert_int_eq(status, COL_STATE_COL);
  ck_assert_int_eq(brick.x, 0);
  ck_assert_int_eq(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(
        field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
        brick.color);
    ck_assert_int_eq(brick.cords[i][0], brick2.cords[i][0]);
    ck_assert_int_eq(brick.cords[i][1], brick2.cords[i][1]);
  }
  deleteField(field, height);
}

Suite *move_brick_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("moveBrick");
  tc = tcase_create("test");

  tcase_add_test(tc, move_brick_case_1);
  tcase_add_test(tc, move_brick_case_2);
  tcase_add_test(tc, move_brick_case_3);
  tcase_add_test(tc, move_brick_case_4);

  suite_add_tcase(s, tc);
  return s;
}
