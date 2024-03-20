#include <check.h>
#include <limits.h>
#include <math.h>

#include "../back/back.h"

#define TEST_CASES                                                             \
  out_of_bounds_suite(), collision_brick_suite(), collision_suite(),           \
      semi_function_suite(), move_brick_suite(), drop_lines_suite()

Suite *out_of_bounds_suite();
Suite *collision_brick_suite();
Suite *collision_suite();
Suite *semi_function_suite();
Suite *move_brick_suite();

Suite *drop_lines_suite();

//MoveBrick tests need fixing