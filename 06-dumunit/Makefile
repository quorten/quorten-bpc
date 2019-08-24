CC = cc
CFLAGS =
LD = cc
LDFLAGS =
X =

TARGETS = dumunit.o dumunit_runner$(X) test_dumunit1$(X) test_dumunit2$(X)

all: $(TARGETS)

dumunit.o: dumunit.c dumunit.h
	$(CC) $(CFLAGS) -o $@ -c $<

dumunit_runner.o: dumunit_runner.c \
	../05-algos2/exparray.h ../05-algos2/xmalloc.h
	$(CC) $(CFLAGS) -o $@ -c $<

test_dumunit1.o: test_dumunit1.c dumunit.h
	$(CC) $(CFLAGS) -o $@ -c $<

test_dumunit2.o: test_dumunit2.c dumunit.h
	$(CC) $(CFLAGS) -o $@ -c $<

dumunit_runner$(X): dumunit_runner.o ../05-algos2/xmalloc.c
	$(LD) $(LDFLAGS) -o $@ $^

test_dumunit1$(X): test_dumunit1.o dumunit.o
	$(LD) $(LDFLAGS) -o $@ $^

test_dumunit2$(X): test_dumunit2.o dumunit.o
	$(LD) $(LDFLAGS) -o $@ $^

check test: dumunit_runner$(X) test_dumunit1$(X) test_dumunit2$(X)
	-./dumunit_runner$(X) ./test_dumunit1$(X)
	-./dumunit_runner$(X) ./test_dumunit2$(X)

mostlyclean:
	rm -f dumunit_runner.o test_dumunit1.o test_dumunit2.o

clean: mostlyclean
	rm -f $(TARGETS)
