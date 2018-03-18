# Dumpster Diving
- author: Jonathan Metzger
- date: 3/15/18


## TASKS

- [x] rm : puts deleted files into seperate "dumpster" (hidden directory)

- [x] dv : dive into "dumpster" to recover 

- [x] dump : removes all files in "dumpster"

- [ ] log all information into log.txt (Errors, messages, etc.)

- [x] if "dumpster" directory has not been created, error and exit.


## RUN

This application will move files into the dumpster
 -f 	premanently (not moved to dumpster).
 -h 	help message.
 -r 	include directories and anything inside (recursive).
file(s) include files or directories for rm and dv.

```
$ ./rm [ -f -h -r -d] file(s)
```

```
$ ./dump [ -h ]
```

```
$ ./dv [ -h ] files(s)
```

## TOOL ACTIONS

1. 	Make the files

	$ make

	gcc -g3 -o rm rm.c common.c
	gcc -g3 -o dump dump.c common.c
	gcc -g3 -o dv dv.c common.c
	
	For Testing:
	Creating test file and directory
	mkdir test

2. 	Remove files to dumpster (-r is for directories)

	$ ./rm -r test test.txt

3. 	Move files back from dumpster

	$ ./dv test.txt

4. 	Force remove files (not to dumpster)

	$ ./rm -f test.txt

	Force remove directories (not to dumpster)

	$ ./rm -f -r test

5. 	Empty dumpster :)
	
	$ ./dump


	###########################################

		Welcome to Dumpster Diving
		Created by Jonathan Metzger
		{ dump } tool Utility

	###########################################

	> [ Deleting { test } directory permanently ... ]

	> [ Deleting { test.txt } file permanently ... ]

	** Dumpster is Empty :)  **

	###########################################


