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
#define EXTENSION ".1";

// Concatinate two strings.
char* concat(char* c1, char* c2);
/* seperator line */
void end_line();
/* title of the program */
void program_title();
/* prints help message and quit */
void usage();
/* takes flags from input */
void flag_check(int argc, char **argv);
/* checks if -f flag is present */
void check_f_flag(char* file);
/* checks if -r flag is present */
void check_r_flag();
/* set dumpster */
void set_dumpster();
/* check to see if dumpster same directory */
void check_dumpster();
/* set file */
void set_file(char* file);
/* get extension of path */
char* get_extension(char* path);
/* dumpster path for file */
void get_dumpsterPath(char* file, char* dumpster_path, char** new_path);

/* remove directory with -r */
void move_directory(char* current_path, char* current_dumpster_path, int same);
/* remove permanently with -f */
void remove_force(char* directory);

/* ERROR call */
void ERROR_call();
/* checks if no file is present */
void ERROR_no_file(int argc);
/* ERROR call for rename() */
void ERROR_rename_call();
/* ERROR call for remove() */
void ERROR_remove_call();
/* ERROR call for fopen() */
void ERROR_fopen_call();
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
void ERROR_limit_dumpster();
/* ERROR call for stat() */
void ERROR_stat_call();
/* ERROR call for open() */
void ERROR_chmod_call();
/* ERROR call for utime() */
void ERROR_utime_call();
/* ERROR call for unlink() */
void ERROR_unlink_call();
/* ERROR call for reading and writing files */
void ERROR_rw_file();
/* ERROR call for getcwd() */
void ERROR_getcwd_call();
/* ERROR call for fileNotFound() */
void ERROR_fileNotFound(char* source_path);