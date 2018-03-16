/*
 * common.h
 * 
 * Jonathan Metzger
 * Spring 2018
 *
 * Project for CS4513 Distributed Computing Systems
 *
 */

/* must match dumpster directory in current location */
#define DUMPSTER "dumpster";
#define EXTENSION "-ext";

// Concatinate two strings.
char* concat(char* c1, char* c2);
/* seperator line */
void end_line();
/* remove directory */
void remove_directory(char* current_path, char* currdumpster_path, int isSamePtn);




/* ERROR call */
void ERROR_call();
/* checks if no file is present */
void ERROR_no_file(int argc);
/* ERROR call for rename() */
void ERROR_rename_call();
/* ERROR call for remove() */
void ERROR_remove_call();
/* ERROR call for open() */
void ERROR_open_call();
/* ERROR call for opendir() */
void ERROR_opendir_call();
/* ERROR call for mkdir() */
void ERROR_mkdir_call();
/* sets directory to extension */
void ERROR_duplicate_dir();
/* ERROR call for rmdir() */
void ERROR_rmdir_call();
/* ERROR when dumpster limit reached */
void ERROR_limit_dumpster(int number);
/* ERROR call for stat() */
void ERROR_stat_call();
/* ERROR call for open() */
void ERROR_chmod_call();
/* ERROR call for utime() */
void ERROR_utime_call();
/* ERROR call for unlink() */
void ERROR_unlink_call();