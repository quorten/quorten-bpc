CC = cc
CFLAGS =
LD = cc
LDFLAGS =
O = .o
X =

TARGETS = dumunit$(O) du-reporter$(X) test_dumunit1$(X) test_dumunit2$(X)

all: $(TARGETS)

dumunit$(O): dumunit.c dumunit.h
	$(CC) $(CFLAGS) -o $@ -c $<

du-reporter$(O): du-reporter.c \
	../05-algos2/exparray.h ../05-algos2/xmalloc.h
	$(CC) $(CFLAGS) -o $@ -c $<

test_dumunit1$(O): test_dumunit1.c dumunit.h
	$(CC) $(CFLAGS) -o $@ -c $<

test_dumunit2$(O): test_dumunit2.c dumunit.h
	$(CC) $(CFLAGS) -o $@ -c $<

du-reporter$(X): du-reporter$(O) ../05-algos2/xmalloc.c
	$(LD) $(LDFLAGS) -o $@ $^

test_dumunit1$(X): test_dumunit1$(O) dumunit$(O)
	$(LD) $(LDFLAGS) -o $@ $^

test_dumunit2$(X): test_dumunit2$(O) dumunit$(O)
	$(LD) $(LDFLAGS) -o $@ $^

check test: du-reporter$(X) test_dumunit1$(X) test_dumunit2$(X)
	-./du-reporter$(X) ./test_dumunit1$(X)
	-./du-reporter$(X) ./test_dumunit2$(X)

mostlyclean:
	rm -f du-reporter$(O) test_dumunit1$(O) test_dumunit2$(O)

clean: mostlyclean
	rm -f $(TARGETS)
