/* test_dumunit1.c -- Perform all tests on `dumunit' that do not crash
   the system.

   Public Domain 2019 Andrew Makousky

   See UNLICENSE file for un-license details.  */

#include "dumunit.h"

int
test_assert_pass (void)
{
  return DUM_ASSERT("expected 1 == 1", 1 == 1);
}

int
test_assert_fail (void)
{
  return DUM_ASSERT("expected 1 == 0", 1 == 0);
}

int
test_assert_div0 (void)
{
  int result = 3;
  result /= 0;
  return DUM_ASSERT("expected result != 3", result != 3);
}

int
test_assert_info (void)
{
  du_info ("Testing debug info message.");
  return 1;
}

void
suite_test_dumunit1 (void)
{
  DUM_RUN_TEST(test_assert_pass);
  DUM_RUN_TEST(test_assert_fail);
  DUM_RUN_TEST(test_assert_div0);
  DUM_RUN_TEST(test_assert_info);
}

int
main (void)
{
  du_start_all_tests ();
  suite_test_dumunit1 ();
  du_end_all_tests ();
  return 0;
}
