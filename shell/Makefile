all: vSh

CFLAGS = -g -O2

vSh: vSh.o vToc.o
	cc -o vSh vSh.o vToc.o

vSh.o: vSh.c vToc.h
	cc -c vSh.c

vToc.o: vToc.c
	cc -c vToc.c

clean:
	rm -f *.o vSh *~
