#include <check.h>
#include <limits.h>
#include <math.h>

#include "../back/back.h"

#define TEST_CASES                                                             \
  out_of_bounds_suite(), collision_brick_suite(), collision_suite(),           \
      semi_move_brick_suite(), move_brick_suite(), semi_linehandler_suite(),   \
      linehandler_suite(), add_points_suite()

Suite *out_of_bounds_suite();
Suite *collision_brick_suite();
Suite *collision_suite();
Suite *semi_move_brick_suite();
Suite *move_brick_suite();
Suite *semi_linehandler_suite();
Suite *linehandler_suite();
Suite *add_points_suite();