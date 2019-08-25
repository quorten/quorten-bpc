`dumunit`
=========

This is a dumb unit testing framework for C software.  Actually, the
high-level design is programming language independent.  The primary
function of this unit testing framework is to allow a standard means
to run a suite of tests and print the results to standard output, and
standard output is the **only** means for communicating test results.
This is so that it's possible to generate and load a unit test
firmware image onto your embedded target machine, execute them, send
the results back to the host over a UART serial communications
connection.

Communication Specification
---------------------------

This is the format of the output.

```

Start_Of_Tests

Test:strcmp_eq_pass
Result:Pass
Coverage:S10,S11,3*S12,S14,
Coverage:S17,S18,S19

Test:memcmp_eq_pass
Info:This is a user info debug string
Info:This is another user info debug string
Result:Pass

Test:strstr_check_null
Assert_Fail:L301:(3) != (5)
Result:Fail

...

Exception:Divide_By_Zero
Status:Abort_Test

...

End_Of_Tests
```

Or the alternate bad day scenario endings:

```
...

Exception:Bus_Error
Status:Fatal

End_Of_Tests
```

Note that it is also possible to embed the test summary user interface
into the target image and display that output in addition to, or in
place of, the primary test results output.  However, if you do this,
and there is memory corruption during a failed test, the summary
mechanism might fail.

The basic case of unit testing implies a "self-test" where all
necessary test data is embedded within the firmware image itself,
which would assume that such data may be reformatted to be compatible
with a particular programming language's tooling.  For true
programming language independent testing, chances are you want
standard format test data to be fed from a source independent of the
programming language, i.e. standard input on UART serial
communications.  A smart general-purpose solution to allow this would
be to add multiple UART serial communication channels, or multiplex
them over a single physical serial communication channel via SLIP
encapsulation or similar.  However, if you would like a standard input
and standard output communication channel without implementing a full
SLIP stack, then a simple protocol extension allows a test harness to
feed in the test data upon request.  Request data length and response
data length in bytes are the keys.

```
Target:RxDL:Any
Host:TxDL:32484
Host:<here follows data, and a newline after it>
Target:RxDL:123
Host:TxDL:123
Host:<here follows data, and a newline after it>
```

This can also be used for communication in the other direction, and in
fact, the data request headers are optional if you only want to
implement a UART communication channel as-is.

Okay, one last extension, for the sake of programmer friendliness.
Optionally, you can specify the data format in hex byte codes too.
Binary data format is the default.

```
DFMT:Bin
DFMT:Hex
00 01 02 03 04 1a 2a 3a 4b ...
```

----------------------------------------

How to use `dumunit`
--------------------

`dumunit`, as its name implies, is simple and easy to use.  An
individual test case is typically written like this:

```
int
test_my_code (void)
{
  /* Do stuff.  */
  return DUM_ASSERT("expected result != 3", result != 3);
}
```

If you are performing multiple asserts in one test case, you write the
code like this:

```
int
test_my_code (void)
{
  int retval = 1;
  /* Do stuff.  */
  retval &= DUM_ASSERT("expected result != 3", result != 3);
  /* Possibly do more stuff.  */
  retval &= DUM_ASSERT("expected result < 10", result < 10);
  return retval;
}
```

Note that if we want all asserts to be run (as intended in the
example), we use bit-wise AND since logical AND implements
short-circuit logic.

As a useful convention, multiple test cases are rolled up into a test
suite like this:

```
void
suite_test_dumunit1 (void)
{
  DUM_RUN_TEST(test_assert_pass);
  DUM_RUN_TEST(test_assert_fail);
  DUM_RUN_TEST(test_assert_div0);
  DUM_RUN_TEST(test_assert_info);
}
```

You can then write a main function that calls the suite from a
different source code file:

```
int
main (void)
{
  du_start_all_tests ();
  suite_test_dumunit1 ();
  du_end_all_tests ();
  return 0;
}
```

Or, you can then write additional suite functions to call sub-suites,
and link it all together into a single suite executor that runs all
suites.

Please note that due to the embedded system emphasis, the return value
of the suite executor is beyond the scope of the test system, which is
why we always return zero.  Also, note that for the sake of embedded
system testing, you can have additional setup code in the executor to
start a remote embedded system and redirect standard input and
standard output accordingly.

Once you have the executor compiled, you can run it from the reporter
like this:

```
du_reporter <EXECUTOR-NAME>
```

This will generate a nice Python `unittest` style report that looks
like this:

```
Running tests .FE.

============================== FAILURES ==============================

Test:test_assert_fail
Assert_Fail:test_dumunit1.c:21:expected 1 == 0

============================= EXCEPTIONS =============================

Test:test_assert_div0
Exception:Floating point exception
Status:Abort_Test

================================ Info ================================

Test:test_assert_info
Info:Testing debug info message.

======================================================================

Summary: 4 run, 2 passed, 1 failed, 1 exceptions
```

----------------------------------------

Please note that `dumunit` is not unique.  Here is a list of other
similar and inspirational C unit testing frameworks, including some
for embedded systems.

20171120/DuckDuckGo unit testing c  
20171120/https://stackoverflow.com/questions/65820/unit-testing-c-code#65845  
20171120/http://check.sourceforge.net/doc/check_html/check_2.html#SEC3

