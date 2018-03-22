

/*
 * dump.c
 * 
 * Jonathan Metzger
 * Spring 2018
 *
 * Project for CS4513 Distributed Computing Systems
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>
#include <utime.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#include <string.h>
#include <errno.h>

#include "common.h"


/* remove perminently. used with -f flag */
void remove_force(char* directory);
/* sets dumpster path and stat */
void set_dumpster();


/* takes flags from input */
void flag_check(int argc, char **argv);
/* prints help message and quit */
void usage();
/* title of the program */
void program_title();

/* characters */
char* dumpster_path = NULL;
char* dumpster_name = DUMPSTER;

/* initialize structs */
struct stat dumpster_stat;
struct dirent* d;
struct stat file_stat;

/* integers */
int tot_flag = 0;
int dir_empty = 0;
int remove_call = 0;
int mkdir_call = 0;
int rmdir_call = 0; 
int stat_call = 0;

int main(int argc, char** argv)
{
    printf("\n");

//     end_line();

//     program_title();

    flag_check(argc, argv);
    
    set_dumpster();

    remove_force(dumpster_path);

    //puts("** Dumpster is Empty :)  **\n");

    //end_line();
}

/* force remove file */
void remove_force(char* directory)
{
    DIR* dir;
    dir = opendir(directory);
    if(dir == NULL)
    {
        fprintf(stderr, "** ERROR: opendir() call failed. ** \n");
        ERROR_call();
    }
    d = readdir(dir);
    while(d)
    {
        if((strcmp(d->d_name, "..") == 0) || (strcmp(d->d_name, ".") == 0))
        {
            d = readdir(dir);
            continue;
        }
        char* file = concat(directory, "/");
        file = concat(file, d->d_name);
        stat_call = stat(file, &file_stat);
        ERROR_stat_call();

        if(S_ISREG(file_stat.st_mode))
        {
            remove_call = remove(file);
            //printf("> [ Deleting { %s } file permanently ... ]\n\n", d->d_name);
            ERROR_remove_call();
        }
        else if(S_ISDIR(file_stat.st_mode))
        {
            remove_force(file);
            rmdir_call = rmdir(file);
            char* dir_name = basename(file);
            //printf("> [ Deleting { %s } directory permanently ... ]\n\n", dir_name);
            ERROR_rmdir_call();

        }
        free(file);
        d = readdir(dir);
    }
    closedir(dir);
}


/* sets dumpster path and stat */
void set_dumpster()
{
    dumpster_path = strcat(getenv("PWD"), "/");
    strcat(dumpster_path, dumpster_name);

    if(!dumpster_path)
    {
        fprintf(stderr, "** ERROR: dumpster does not exist ... **\n\n");
        ERROR_call();
    }
    
    stat_call = stat(dumpster_path, &dumpster_stat);
    ERROR_stat_call();
}

/* checks flag of input */
void flag_check(int argc, char **argv)
{
    int option;
    while ((option = getopt (argc, argv, "h")) != -1)
    {
        switch (option)
        {
        /* -h show help message */
        case 'h':
        tot_flag++;
        usage();
        exit(-1);
        break;

        default:
        exit(-1);

        }
    }
}

/* Prints help message and quit */
void usage()
{
    fprintf(stderr, "dump - clears dumpster\n\n");
    fprintf(stderr, "usage: ./dump -h\n");
    fprintf(stderr, "  -h:\tusage message\n");
    end_line();
    exit(1);
}

/* Title of the Program */
void program_title()
{
    printf("\tWelcome to Dumpster Diving\n");
    printf("\tCreated by Jonathan Metzger\n");
    printf("\t{ dump } tool Utility\n\n");
    end_line();
}

/* ERROR call */
void ERROR_call()
{
    end_line();
    usage();
    exit(-1);
}

/* ERROR call for stat() */
void ERROR_stat_call()
{
    if(stat_call)
    {
        fprintf(stderr, "** ERROR: stat() call failed. ** \n");
        ERROR_call();
    }
}

/* ERROR call for remove() */
void ERROR_remove_call()
{
    if(rmdir_call)
    {
        fprintf(stderr, "** ERROR: remove() call failed. ** \n");
        ERROR_call();
    }
}

/* ERROR call for rmdir() */
void ERROR_rmdir_call()
{

    if(rmdir_call)
    {
        fprintf(stderr, "** ERROR: rmdir() call failed. ** \n");
        ERROR_call();
    }
}



