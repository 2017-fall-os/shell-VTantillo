all: vSh

CFLAGS = -g -O2

vSh: vSh.o vToke.o
	cc -o vSh vSh.o vToke.o

vSh.o: vSh.c vToke.h
	cc -c vSh.c

vToke.o: vToke.c
	cc -c vToke.c

clean:
	rm -f *.o vSh *~
