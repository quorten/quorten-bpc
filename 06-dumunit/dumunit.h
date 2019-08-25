/* dumunit.h -- Another simple unit testing framework for embedded
   systems.

Public Domain 2019 Andrew Makousky

See the file "UNLICENSE" in the top level directory for details.

*/

#ifndef DUMUNIT_H
#define DUMUNIT_H

#include <stdio.h>

typedef int (*DUTestCode)(void);

#define DU_E_ABORT_TEST 0
#define DU_E_FATAL 1

#define DU_INB_ANY ((unsigned long)-1)

#define DUM_STRINGIFY(x) #x
#define DUM_TOSTRING(x) DUM_STRINGIFY(x)

#define DUM_ASSERT(message, test_value) \
  du_assert (__FILE__ ":" DUM_TOSTRING(__LINE__) ":" message, (test_value))

#define DUMA_ASSERT(test_value) \
  DUM_ASSERT("expected " DUM_STRINGIFY(test_value), (test_value))

#define DUM_RUN_TEST(test_code) \
  du_run_test (#test_code, (DUTestCode) test_code)

extern FILE *du_test_out;
extern FILE *du_test_in;

void du_start_all_tests (void);
void du_end_all_tests (void);
void du_run_test (const char *test_name, DUTestCode test_code);
void du_start_test (const char *test_name);
void du_end_test (int result);
int du_assert (const char *message, int test_value);
int du_info (const char *message);
void du_exception (const char *except_name, int status);
void du_sig_handler (int signum);
void du_init_sigs (void);

void du_hdr_write (unsigned long size);
void du_hdr_read (unsigned long size);

#endif /* not DUMUNIT_H */
