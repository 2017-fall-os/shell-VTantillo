all: vSh

CFLAGS = -g -O2

test: test.o vLib.o
	cc -o test test.o vLib.o

vSh: vSh.o vToke.o vLib.o
	cc -o vSh vSh.o vToke.o vLib.o

vSh.o: vSh.c vToke.h vLib.h
	cc -c vSh.c

vToke.o: vToke.c vLib.h
	cc -c vToke.c

test.o: test.c vLib.h
	cc -c test.c

vLib.o: vLib.c vLib.h
	cc -c vLib.c

clean:
	rm -f *.o vSh *~ test *.txt
