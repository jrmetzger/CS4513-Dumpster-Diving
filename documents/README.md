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

- [ ] rm : puts deleted files into seperate "dumpster" (hidden directory)

	- [x] dumpster replaces /bin/rm
	- [x] create dumpster is not present
	- [x] rename() : moves files to directory specified
	- [ ] unlink() : 
	- [x] remove() :
	- [ ] duplicate file adds ".1" to extension and not just replaces
	- [ ] stat() : gather values 
	- [ ] chmod(): set
	- [ ] touch() : set

	- [ ] Flags: rm -f -h -r -d /path/file [file ...]
	- [x] -f force complete removal
	- [x] -h display help and usage message
	- [ ] -r copy directories recursively (remove directories)
	- [x] file [file...] one or more files
	- [ ] -d allows removal to different dumpster specified by name

- [ ] dv : dive into "dumpster" to recover 



- [ ] dump : removes all files in "dumpster"

- [ ] log all information into log.txt (Errors, messages, etc.)
- [ ] if "dumpster" directory has not been created, error and exit.
