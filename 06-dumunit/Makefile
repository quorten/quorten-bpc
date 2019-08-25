CC = cc
CFLAGS =
LD = cc
LDFLAGS =
X =

TARGETS = dumunit.o du_reporter$(X) test_dumunit1$(X) test_dumunit2$(X)

all: $(TARGETS)

dumunit.o: dumunit.c dumunit.h
	$(CC) $(CFLAGS) -o $@ -c $<

du_reporter.o: du_reporter.c \
	../05-algos2/exparray.h ../05-algos2/xmalloc.h
	$(CC) $(CFLAGS) -o $@ -c $<

test_dumunit1.o: test_dumunit1.c dumunit.h
	$(CC) $(CFLAGS) -o $@ -c $<

test_dumunit2.o: test_dumunit2.c dumunit.h
	$(CC) $(CFLAGS) -o $@ -c $<

du_reporter$(X): du_reporter.o ../05-algos2/xmalloc.c
	$(LD) $(LDFLAGS) -o $@ $^

test_dumunit1$(X): test_dumunit1.o dumunit.o
	$(LD) $(LDFLAGS) -o $@ $^

test_dumunit2$(X): test_dumunit2.o dumunit.o
	$(LD) $(LDFLAGS) -o $@ $^

check test: du_reporter$(X) test_dumunit1$(X) test_dumunit2$(X)
	-./du_reporter$(X) ./test_dumunit1$(X)
	-./du_reporter$(X) ./test_dumunit2$(X)

mostlyclean:
	rm -f du_reporter.o test_dumunit1.o test_dumunit2.o

clean: mostlyclean
	rm -f $(TARGETS)
