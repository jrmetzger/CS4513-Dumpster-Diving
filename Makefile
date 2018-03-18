all: rm dump dv

dump: dump.c
	gcc -g3 -o dump dump.c common.c

rm: rm.c
	gcc -g3 -o rm rm.c common.c


dv: dv.c
	gcc -g3 -o dv dv.c common.c

clean:
	-rm -f *.o
	-rm -f -r rm dump dv test test.txt
