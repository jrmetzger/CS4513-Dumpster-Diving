#README

## RUN

The application will remove the file
 -f premanently
 -h help message
 -r directories
 -d specific dumpster

```

$ ./rm [ -f -h -r -d] file(s)

```

## TASKS

- [x] rm : puts deleted files into seperate "dumpster" (hidden directory)

	- [x] dumpster replaces /bin/rm
	- [x] create dumpster is not present
	- [x] rename() : moves files to directory specified
	- [x] remove()
	- [x] mkdir() :
	- [x] rmdir() :
	- [x] unlink() : 
	- [x] remove() :
	- [x] duplicate file adds ".1" to extension and not just replaces
	- [x] stat() : gather values 
	- [x] chmod(): set
	- [x] touch() : set
	- [x] open() :
	- [x] utime() :
	- [x] stat() :

	- [x] Flags: rm -f -h -r -d /path/file [file ...]
	- [x] -f force complete removal
	- [x] -h display help and usage message
	- [x] -r copy directories recursively (remove directories)
	- [x] file [file...] one or more files

- [ ] dv : dive into "dumpster" to recover 


- [ ] dump : removes all files in "dumpster"

- [ ] log all information into log.txt (Errors, messages, etc.)
- [ ] if "dumpster" directory has not been created, error and exit.