/* dumunit_runner.c -- Run a `dumunit' test suite, analyze, and report
   the results in a user-friendly format.

   Public Domain 2019 Andrew Makousky

   See UNLICENSE file for un-license details.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int
main (int argc, char *argv[])
{
  int retval = 0;
  char *prog_name;
  unsigned tests_run = 0;
  unsigned tests_passed = 0;
  unsigned tests_failed = 0;
  unsigned tests_except = 0;
  char linebuf[256];
  char test_name[64];

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
  while (fgets (linebuf, 256, stdin) != NULL) {
    if (!strcmp (linebuf, "\n")) {
      continue;
    } else if (!strcmp (linebuf, "Start_Of_Tests\n")) {
      fputs ("Running tests ", stdout);
    } else if (!strncmp (linebuf, "Test:", 5)) {
      strncpy (test_name,  linebuf + 5, 64);
      test_name[63] = '\0';
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
    } else if (!strncmp (linebuf, "Exception:", 10)) {
	putc ('E', stdout);
	tests_except++;
	retval = 1;
    } else if (!strcmp (linebuf, "End_Of_Tests\n")) {
      putchar ('\n');
    }
  }

  /* TODO: Display test failures and exceptions.  */

  /* Print the final test results summary.  */
  fprintf (stdout, "\nSummary: %d run, %d passed, %d failed, "
	   "%d exceptions\n",
	   tests_run, tests_passed, tests_failed, tests_except);

  return retval;
}
