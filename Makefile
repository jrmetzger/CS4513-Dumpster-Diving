all: rm

rm.o: rm.c
	gcc -g3 -c rm.c -o rm.o

rm: rm.o
	gcc -g3 rm.o -o rm

clean:
	-rm -f rm.o
	-rm -f rm
