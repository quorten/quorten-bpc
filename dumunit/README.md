This is a dumb unit testing framework for C software.  Actually, the
high-level design is programming language independent.  The primary
function of this unit testing framework is to allow a standard means
to run a suite of tests and print the results to standard output, and
standard output is the **only** means for communicating test results.
This is so that it's possible to generate and load a unit test
firmware image onto your embedded target machine, execute them, send
the results back to the host over a UART serial communications
connection.

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
Status:Terminate_Test

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
place of, the primary test results output.

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
data length are the keys.

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

That's all you need to know.
