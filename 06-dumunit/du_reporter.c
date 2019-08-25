/* du_reporter.c -- Run a `dumunit' test suite, analyze, and report
   the results in a user-friendly format.

Public Domain 2019 Andrew Makousky

See the file "UNLICENSE" in the top level directory for details.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "../05-algos2/exparray.h"

EA_TYPE(char);

int
main (int argc, char *argv[])
{
  int retval = 0;
  char *prog_name;
  char linebuf[256];

  unsigned tests_run = 0;
  unsigned tests_passed = 0;
  unsigned tests_failed = 0;
  unsigned tests_except = 0;
  char test_name[64];
  unsigned char fail_showed_name = 0;
  unsigned char except_showed_name = 0;
  unsigned char info_showed_name = 0;
  unsigned char tests_info = 0;
  unsigned char fatal_exception = 0;

  char_array failed_text;
  char_array except_text;
  char_array info_text;

  if (argc == 1) {
    fprintf(stderr, "Usage: $s <DUMUNIT-SUITE>\n", argv[0]);
    return 1;
  }
  prog_name = argv[1];

  { /* Spawn the `dumunit' suite and setup pipe communications.  */
    int out_pipefd[2];
    pid_t child_pid;
    if (pipe (out_pipefd) == -1) {
      perror ("pipe");
      return 1;
    }
    child_pid = fork ();
    if (child_pid == 0) { /* child */
      /* Redirect standard output to the pipe.  */
      if (close (out_pipefd[0]) == -1) {
        perror ("close");
        exit (1);
      }
      if (dup2 (out_pipefd[1], STDOUT_FILENO) == -1) {
        perror ("dup2");
        exit (1);
      }
      execlp (prog_name, prog_name, NULL);
    } else { /* parent */
      /* Redirect standard input to the pipe.  */
      if (close (out_pipefd[1]) == -1) {
        perror ("close");
        exit (1);
      }
      if (dup2 (out_pipefd[0], STDIN_FILENO) == -1) {
        perror ("dup2");
        exit (1);
      }
    }
  }

  /* Parse the output as the tests are running.  */
  EA_INIT(failed_text, 16);
  EA_INIT(except_text, 16);
  EA_INIT(info_text, 16);
  while (fgets (linebuf, 256, stdin) != NULL) {
    if (!strcmp (linebuf, "\n")) {
      continue;
    } else if (!strcmp (linebuf, "Start_Of_Tests\n")) {
      fputs ("Running tests ", stdout);
    } else if (!strncmp (linebuf, "Test:", 5)) {
      unsigned end_len = strlen (linebuf);
      if (linebuf[end_len-1] == '\n')
        linebuf[end_len-1] = '\0';
      strncpy (test_name,  linebuf + 5, 64);
      test_name[63] = '\0';
      fail_showed_name = 0;
      except_showed_name = 0;
      info_showed_name = 0;
      tests_run++;
    } else if (!strncmp (linebuf, "Result:", 7)) {
      if (!strcmp (linebuf + 7, "Pass\n")) {
        putc ('.', stdout);
        tests_passed++;
      } else { /* Fail */
        putc ('F', stdout);
        tests_failed++;
        retval = 1;
      }
    } else if (!strncmp (linebuf, "Assert_Fail:", 12)) {
      unsigned linebuf_len = strlen (linebuf);
      if (!fail_showed_name) {
        unsigned name_len = strlen (test_name);
        fail_showed_name = 1;
        EA_APPEND_MULT(failed_text, "\nTest:", 6);
        EA_APPEND_MULT(failed_text, test_name, name_len);
        EA_APPEND(failed_text, '\n');
      }
      EA_APPEND_MULT(failed_text, linebuf, linebuf_len);
    } else if (!strncmp (linebuf, "Info:", 5)) {
      unsigned linebuf_len = strlen (linebuf);
      tests_info = 1;
      if (!info_showed_name) {
        unsigned name_len = strlen (test_name);
        info_showed_name = 1;
        EA_APPEND_MULT(info_text, "\nTest:", 6);
        EA_APPEND_MULT(info_text, test_name, name_len);
        EA_APPEND(info_text, '\n');
      }
      EA_APPEND_MULT(info_text, linebuf, linebuf_len);
    } else if (!strncmp (linebuf, "Exception:", 10)) {
      unsigned linebuf_len = strlen (linebuf);
      putc ('E', stdout);
      tests_except++;
      retval = 1;
      if (!except_showed_name) {
        unsigned name_len = strlen (test_name);
        except_showed_name = 1;
        EA_APPEND_MULT(except_text, "\nTest:", 6);
        EA_APPEND_MULT(except_text, test_name, name_len);
        EA_APPEND(except_text, '\n');
      }
      EA_APPEND_MULT(except_text, linebuf, linebuf_len);
    } else if (!strncmp (linebuf, "Status:", 7)) {
      unsigned linebuf_len = strlen (linebuf);
      if (!strcmp (linebuf + 7, "Fatal\n"))
        fatal_exception = 1;
      EA_APPEND_MULT(except_text, linebuf, linebuf_len);
    } else if (!strcmp (linebuf, "End_Of_Tests\n")) {
      putchar ('\n');
    }
  }
  EA_APPEND(failed_text, '\0');
  EA_APPEND(except_text, '\0');
  EA_APPEND(info_text, '\0');

  /* Display test failures and exceptions.  */
  if (tests_failed > 0) {
    fputs (
  "\n============================== FAILURES ==============================\n",
           stdout);
    fputs (failed_text.d, stdout);
  }
  if (tests_except > 0) {
    fputs (
  "\n============================= EXCEPTIONS =============================\n",
           stdout);
    fputs (except_text.d, stdout);
  }
  if (tests_info > 0) {
    fputs (
  "\n================================ Info ================================\n",
           stdout);
    fputs (info_text.d, stdout);
  }
  if (tests_failed > 0 || tests_except > 0 || tests_info > 0) {
    /* Show a nice big divider before the final summary.  */
    fputs (
  "\n======================================================================\n",
           stdout);
  }

  /* Print the final test results summary.  */
  fprintf (stdout, "\nSummary: %d run, %d passed, %d failed, "
           "%d exceptions\n",
           tests_run, tests_passed, tests_failed, tests_except);
  if (fatal_exception) {
    fputs ("Some tests were skipped due to the fatal exception.\n",
           stdout);
  }

  /* Cleanup.  */
  EA_DESTROY(failed_text);
  EA_DESTROY(except_text);
  EA_DESTROY(info_text);

  return retval;
}
