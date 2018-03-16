# Dumpster Diving
- author: Jonathan Metzger
- date: 3/15/18

## RUN

This application will move files into the dumpster
 -f premanently (not moved to dumpster)
 -h help message
 -r include directories and anything inside

```
$ ./rm [ -f -h -r -d] file(s)
```


```
$ ./dump [ -h ]
```

## TASKS

- [x] rm : puts deleted files into seperate "dumpster" (hidden directory)

- [ ] dv : dive into "dumpster" to recover 

- [x] dump : removes all files in "dumpster"

- [ ] log all information into log.txt (Errors, messages, etc.)
- [x] if "dumpster" directory has not been created, error and exit.
