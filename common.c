
/*
 * common.c
 * 
 * Jonathan Metzger
 * Spring 2018
 *
 * Project for CS4513 Distributed Computing Systems
 * Source: https://stackoverflow.com/questions/8465006/how-do-i-concatenate-two-strings-in-c
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

/* concate two strings */
char* concat(char* s1, char* s2)
{
    char* result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/* (optional) end line */
void end_line()
{ printf("###########################################\n\n"); 
}