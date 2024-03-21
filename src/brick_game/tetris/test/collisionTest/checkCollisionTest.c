#include "../backTests.h"

START_TEST(case_1) {
  int width = 10;
  int height = 10;
  int **field;
  initField(&field, width, height);

  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  Brick brick1 = BRICKS_TYPES[0];
  gameInfo.currentBrick = brick1;
  bornBrick(&brick1, 1, 0, 0, 7);

  field[0][4] = 1;
  int status = 0;
  status = checkCollision(&gameInfo, &brick1, DIR_RIGHT);
  ck_assert_int_eq(status, COL_STATE_COL);
  deleteField(field, height);
}
END_TEST

START_TEST(case_2) {
  int width = 10;
  int height = 10;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  Brick brick1 = BRICKS_TYPES[0];
  gameInfo.currentBrick = brick1;
  bornBrick(&brick1, 1, 1, 0, 7);
  field[1][4] = 1;
  int status = 0;
  status = checkCollision(&gameInfo, &brick1, DIR_DOWN);
  ck_assert_int_eq(status, COL_STATE_CRIT);
  deleteField(field, height);
}
END_TEST

START_TEST(case_3) {
  int width = 10;
  int height = 10;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  Brick brick1 = BRICKS_TYPES[0];
  gameInfo.currentBrick = brick1;
  bornBrick(&brick1, 1, 0, 0, 7);
  field[0][4] = 1;
  int status = checkCollision(&gameInfo, &brick1, DIR_TOP);
  ck_assert_int_eq(status, COL_STATE_COL);
  deleteField(field, height);
}

END_TEST

START_TEST(case_4) {

  int width = 10;
  int height = 10;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  Brick brick1 = BRICKS_TYPES[0];
  gameInfo.currentBrick = brick1;
  bornBrick(&brick1, 1, 0, 0, 7);
  field[0][1] = 1;
  int status = checkCollision(&gameInfo, &brick1, DIR_LEFT);
  ck_assert_int_eq(status, COL_STATE_COL);
  deleteField(field, height);
}
END_TEST

START_TEST(case_5) {
  int width = 10;
  int height = 10;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  Brick brick = BRICKS_TYPES[0];
  gameInfo.currentBrick = brick;
  bornBrick(&brick, 1, 0, 0, 7);
  int status = checkCollision(&gameInfo, &brick, DIR_LEFT);

  ck_assert_int_eq(status, COL_STATE_NO);
  deleteField(field, height);
}
END_TEST

START_TEST(case_6) {
  int width = 4;
  int height = 3;
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  Brick brick = BRICKS_TYPES[0];
  gameInfo.currentBrick = brick;
  bornBrick(&brick, 1, 0, 0, 7);
  int status = checkCollision(&gameInfo, &brick, DIR_LEFT);

  ck_assert_int_eq(status, COL_STATE_COL);
  deleteField(field, height);
}
END_TEST

START_TEST(case_7) {
  int width = 4;
  int height = 1;
  Brick brick = BRICKS_TYPES[0];
  bornBrick(&brick, 1, 0, 4, 7);
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  gameInfo.currentBrick = brick;

  int status = checkCollision(&gameInfo, &brick, DIR_DOWN);
  ck_assert_int_eq(status, COL_STATE_CRIT);
  deleteField(field, height);
}
END_TEST

START_TEST(case_8) {
  int width = 4;
  int height = 3;
  Brick brick = BRICKS_TYPES[0];
  bornBrick(&brick, -1, 0, 0, 7);
  int **field;
  initField(&field, width, height);
  GameInfo_t gameInfo;
  gameInfo.field = field;
  gameInfo.winInfo.height = height;
  gameInfo.winInfo.width = width;
  gameInfo.currentBrick = brick;

  int status = checkCollision(&gameInfo, &brick, DIR_DOWN);
  ck_assert_int_eq(status, COL_STATE_COL);
  deleteField(field, height);
}
END_TEST

START_TEST(case_9) {
  int width = 4;
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
  int status = checkCollision(&gameInfo, &brick, DIR_RIGHT);
  ck_assert_int_eq(status, COL_STATE_COL);
  ck_assert_int_eq(brick.x, 1);
  ck_assert_int_eq(brick.y, 0);
  deleteField(field, height);
}
END_TEST

Suite *collision_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("Collision");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);
  tcase_add_test(tc, case_3);
  tcase_add_test(tc, case_4);
  tcase_add_test(tc, case_5);
  tcase_add_test(tc, case_6);
  tcase_add_test(tc, case_7);
  tcase_add_test(tc, case_8);
  tcase_add_test(tc, case_9);

  suite_add_tcase(s, tc);
  return s;
}