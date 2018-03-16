all: rm dump dv

	@echo For Testing
	@echo Creating test file and directory
	@echo "test file" > test.txt
	mkdir test

dump: dump.c
	gcc -g3 -o dump dump.c common.c

rm: rm.c
	gcc -g3 -o rm rm.c common.c


dv: dv.c
	gcc -g3 -o dv dv.c common.c

clean:
	-rm -f *.o
	-rm -f rm dump dv
