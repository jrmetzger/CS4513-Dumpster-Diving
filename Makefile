all: rm dump dive


dump: dump.c
	gcc -g3 -o dump dump.c common.c

rm: rm.c
	gcc -g3 -o rm rm.c common.c


dive: dive.c
	gcc -g3 -o dive dive.c common.c

clean:
	-rm -f *.o
	-rm -f rm dump dive
