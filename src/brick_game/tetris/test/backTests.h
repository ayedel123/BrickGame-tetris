#include <check.h>
#include <limits.h>
#include <math.h>

#include "../back/back.h"

#define TEST_CASES                                                             \
  out_of_bounds_suite(), collision_brick_suite(), collision_suite()

Suite *out_of_bounds_suite();
Suite *collision_brick_suite();
Suite *collision_suite();
