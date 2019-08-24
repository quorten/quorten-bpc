/* test_dumunit2.c -- Perform test on `dumunit' that crashes the
   system.

   Public Domain 2019 Andrew Makousky

   See UNLICENSE file for un-license details.  */

#include "dumunit.h"

int
test_assert_sigsegv (void)
{
  int result = *(int *) 0;
  return DUM_ASSERT("expected result == 0", result == 0);
}

void
suite_test_dumunit2 (void)
{
  DUM_RUN_TEST(test_assert_sigsegv);
}

int
main (void)
{
  du_start_all_tests ();
  suite_test_dumunit2 ();
  du_end_all_tests ();
  return 0;
}
