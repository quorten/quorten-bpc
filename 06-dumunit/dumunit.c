/* dumunit.c -- Another simple unit testing framework for embedded
   systems.

Public Domain 2019 Andrew Makousky

See the file "UNLICENSE" in the top level directory for details.

*/

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>

#include "dumunit.h"

FILE *du_test_out;
FILE *du_test_in;

static jmp_buf du_except_return;

void
du_start_all_tests (void)
{
  du_test_out = stdout;
  du_test_in = stdin;
  fputs ("\nStart_Of_Tests\n\n", du_test_out);
  du_init_sigs ();
}

void
du_end_all_tests (void)
{
  fputs ("End_Of_Tests\n", du_test_out);
}

void
du_run_test (const char *test_name, DUTestCode test_code)
{
  int result;
  if (setjmp (du_except_return) == 0) {
    du_start_test (test_name);
    result = test_code ();
    du_end_test (result);
  } /* else Move on to next test.  */
}

void
du_start_test (const char *test_name)
{
  fputs ("Test:", du_test_out);
  fputs (test_name, du_test_out);
  putc ('\n', du_test_out);
}

/* TODO: Add code coverage reporting for embedded systems.  */
void
du_end_test (int result)
{
  if (result) {
    fputs ("Result:Pass\n\n", du_test_out);
  } else {
    fputs ("Result:Fail\n\n", du_test_out);
  }
}

int
du_assert (const char *message, int test_value)
{
  if (!test_value) {
    fputs ("Assert_Fail:", du_test_out);
    fputs (message, du_test_out);
    putc ('\n', du_test_out);
  }
  return test_value;
}

int
du_info (const char *message)
{
  fputs ("Info:", du_test_out);
  fputs (message, du_test_out);
  putc ('\n', du_test_out);
}

void
du_exception (const char *except_name, int status)
{
  static const char *status_strs[] = {
    "Abort_Test",
    "Fatal"
  };
  fputs ("\nException:", du_test_out);
  fputs (except_name, du_test_out);
  fputs ("\nStatus:", du_test_out);
  fputs (status_strs[status], du_test_out);
  fputs ("\n\n", du_test_out);
  if (status == DU_E_FATAL) {
    du_end_all_tests ();
    abort ();
  } else { /* if (status == DU_E_ABORT_TEST) */
    longjmp (du_except_return, 1);
  }
}

/********************************************************************/
/* POSIX-specific code */

void
du_sig_handler (int signum)
{
  const char *except_name = strsignal (signum);
  int status = DU_E_ABORT_TEST;
  if (signum == SIGINT ||
      signum == SIGSEGV ||
      signum == SIGBUS ||
      signum == SIGILL)
    status = DU_E_FATAL;
  du_exception (except_name, status);
}

void
du_init_sigs (void)
{
  struct sigaction sa;
  sa.sa_handler = du_sig_handler;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = SA_RESETHAND;
  sigaction (SIGFPE, &sa, NULL);
  sigaction (SIGINT, &sa, NULL);
  sigaction (SIGSEGV, &sa, NULL);
  sigaction (SIGBUS, &sa, NULL);
  sigaction (SIGILL, &sa, NULL);
}

/********************************************************************/
/* Extension 1: In-band standard input and standard output.  */

void
du_hdr_read (unsigned long size)
{
  if (size == DU_INB_ANY)
    fputs ("RxDL:Any\n", du_test_out);
  else
    fprintf (du_test_out, "RxDL:%ld\n", size);
}

void
du_hdr_write (unsigned long size)
{
  fprintf (du_test_out, "TxDL:%ld\n", size);
}

/********************************************************************/
/* Extension 2: Encode/decode hexadecimal in-band data.  */

int
du_hex_read (void *buffer, unsigned long count)
{
  unsigned char *curbuf = (unsigned char *) buffer;
  while (count > 0) {
    int rchar;
    if (fscanf (du_test_in, " %02x", &rchar) != 1)
      return -1;
    *curbuf = (unsigned char) rchar;
    curbuf++;
    count--;
  }
  if (getc (du_test_in) != '\n')
    return -1;
  return count;
}

int
du_hex_write (void *buffer, unsigned long count)
{
  unsigned char *curbuf = (unsigned char *) buffer;
  if (fputs ("DFMT:Hex\n", du_test_out) == EOF)
    return -1;
  while (count > 0) {
    if (fprintf (du_test_out, " %02x", *curbuf) < 0)
      return -1;
    curbuf++;
    count--;
  }
  if (putc ('\n', du_test_out) == EOF)
    return -1;
  return count;
}

/* Read in-band data, independent of encoding.  */
int
du_inb_read (void *buffer, unsigned long count)
{
  char linebuf[256];
  int read_count;
  int is_hex;
  while (1) { /* while (read_hdrs) */
    fgets (linebuf, 256, du_test_in);
    if (!strncmp (linebuf, "TxDL:", 5)) {
      sscanf (linebuf, "TxDL:%d\n", read_count);
    } else if (!strncmp (linebuf, "DFMT:Bin", 5)) {
      is_hex = 0;
    } else if (!strncmp (linebuf, "DFMT:Hex", 5)) {
      is_hex = 1;
    } else {
      /* Start reading the first few bytes fetched in the line
	 buffer.  */
      /* Done reading headers.  */
      break;
    }
  }
  /* Read the remainder of the data.  */
  /* TODO */
}

/* Write in-band data.  The `hex' flag indicates whether hexadecimal
   encoding should be used.  */
int
du_inb_write (int hex, void *buffer, unsigned long count)
{
  if (fprintf (du_test_out, "TxDL:%d\n", count) < 0)
    return -1;
  if (!hex) {
    if (fputs ("DFMT:Bin\n", du_test_out) == EOF)
      return -1;
    if (fwrite (buffer, count, 1, du_test_out) != 1)
      return -1;
    if (putc ('\n', du_test_out) == EOF)
      return -1;
  } else {
    du_hex_write (buffer, count);
  }
  return count;
}
