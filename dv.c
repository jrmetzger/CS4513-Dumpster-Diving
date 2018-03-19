
/*
 * rm.c
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

// Print the usage of this function.
void usage(void);
// Remove a folder.
void remove_directory(char* current_path, char* file, int same);
/* copy to targetget */
void copyto_target(char* source_path, char* curr_target_path, struct stat file_stat);

/* ERROR call */
void ERROR_call();
/* no file present */
void ERROR_no_file(int argc);
/* ERROR call for mkdir() */
void ERROR_mkdir_call();
/* ERROR call for rmdir() */
void ERROR_rmdir_call();
/* ERROR call for open() */
void ERROR_chmod_call();
/* ERROR call for stat() */
void ERROR_stat_call();
/* ERROR call for getcwd() */
void ERROR_getcwd_call();
/* ERROR call for rename() */
void ERROR_rename_call();
/* ERROR call for unlink() */
void ERROR_unlink_call();
/* ERROR call for utime() */
void ERROR_utime_call();
/* ERROR call for fopen() */
void ERROR_fopen_call();
/* ERROR call for reading and writing files */
void ERROR_rw_file();
/* ERROR call for fileNotFound() */
void ERROR_fileNotFound(char* source_path);
/* Title of the Program */
void program_title();
/* sets dumpster path and stat */
void set_dumpster();
/* checks flag of input */
void flag_check(int argc, char **argv);

/* initialize DIR and FILE */
DIR* dir;
FILE* source;
FILE* target;

size_t bytes;


/* Integers */
int tot_flag = 0;
int i = 0;
int stat_call = 0;
int chmod_call = 0;
int unlink_call = 0;
int rmdir_call = 0;
int mkdir_call = 0;
int rename_call = 0;
int utime_call = 0;
int count_file = 0;
int access_call = 0;

/* initialize structs */
struct stat dumpster_stat;
struct stat current_dir_stat;
struct stat source_file_stat;
struct dirent* d;
struct stat srcFolderStat;

/* initialize characters */
char* dumpster_name = DUMPSTER;
char* dumpster_path = NULL;
char* getcwd_call = NULL;
char* curr_target_path = NULL;
char* file = NULL;
char* source_path = NULL;
char* buf[1024];
char* base = NULL;

/* main */
int main(int argc, char** argv)
{
	printf("\n");

    // end_line();

    // program_title();

    flag_check(argc, argv);

    ERROR_no_file(argc);

	set_dumpster();
	
    count_file = argc - optind;

    char* files[count_file];
    
    /* create for multiple files */
    for(i = 0; i < count_file; i++)
    {
        files[i] = argv[i + optind];
    }

	/* dumpster stats */
	struct stat dumpster_stat;
	stat_call = stat(dumpster_path, &dumpster_stat);
	ERROR_stat_call();
	
    char current_dir[1024];
	getcwd_call = getcwd(current_dir, 1024);
	ERROR_getcwd_call();
	
    stat_call = stat(current_dir, &current_dir_stat);
	ERROR_stat_call();
	
    for(i = 0; i < count_file; i++)
	{
		char* file = files[i];
		int access_call = access(file, F_OK);
		source_path = concat(dumpster_path, "/");
		source_path = concat(source_path, file);
		char* dumpster_path = strdup(file);
		char* target_file;
		char* token;
		while((token = strsep(&dumpster_path, "/"))){
			target_file = strdup(token);
		}
		ERROR_fileNotFound(source_path);
		int stat_call = stat(source_path, &source_file_stat);
		ERROR_stat_call();
		if(dumpster_stat.st_dev == current_dir_stat.st_dev)
		{
			base = basename(source_path);
			if(S_ISREG(source_file_stat.st_mode))
			{
				rename_call = rename(source_path, target_file);
                ERROR_rename_call();
                chmod_call = chmod(target_file, source_file_stat.st_mode);
                ERROR_chmod_call();
               	//printf("> [ Moving { %s } file back from dumpster ... ]\n\n", base);
			}
			else if(S_ISDIR(source_file_stat.st_mode))
			{
				// Recursively add new folder back to current directory.
				remove_directory(source_path, target_file, 1);
				rmdir_call = rmdir(source_path);
                ERROR_rmdir_call();
                //printf("> [ Moving { %s } directory back from dumpster ... ]\n\n", base);
			}
		}
		else
		{
			if(S_ISREG(source_file_stat.st_mode))
			{
				copyto_target(source_path, target_file, source_file_stat);
				unlink_call = unlink(source_path);
				ERROR_unlink_call();
			}
			else if(S_ISDIR(source_file_stat.st_mode))
			{
				remove_directory(source_path, target_file, 0);
				rmdir_call = rmdir(source_path);
				ERROR_rmdir_call();
			}
		}
		
	}
	// end_line();

}

/* copy to temp path to recover */
void copyto_target(char* curr_source_path, char* curr_target_path, struct stat file_stat)
{

	source = fopen(curr_source_path, "r");
	ERROR_fopen_call(source);
	
	target = fopen(curr_target_path, "w");
	ERROR_fopen_call(target);

    ERROR_rw_file();

	fclose(source);
	fclose(target);

	chmod_call = chmod(curr_target_path, file_stat.st_mode);
	ERROR_chmod_call();

	const struct utimbuf source_time = {file_stat.st_atime, file_stat.st_mtime};
	
	utime_call = utime(curr_target_path, &source_time);
	ERROR_utime_call();
}


/* remove directory */
void remove_directory(char* current_path, char* file, int same)
{

	curr_target_path = file;
    stat_call = stat(current_path, &srcFolderStat);
    ERROR_stat_call();

    mkdir_call = mkdir(curr_target_path, srcFolderStat.st_mode);
    ERROR_mkdir_call();
    dir = opendir(current_path);
   	ERROR_opendir_call();
    d = readdir(dir);
    while(d)
    {
    	if((strcmp(d->d_name, "..") == 0) ||
    		(strcmp(d->d_name, ".") == 0))
    	{
    		d = readdir(dir);
    		continue;
    	}
    	struct stat current_stat;
    	char* current_file = concat(current_path, "/");
    	current_file = concat(current_file, d->d_name);
    	stat_call = stat(current_file, &current_stat);
    	ERROR_stat_call();
    	char* new_target_path = concat(curr_target_path, "/");
    	new_target_path = concat(new_target_path, d->d_name);
    	if(S_ISREG(current_stat.st_mode))
    	{
    		if(same)
    		{
    			rename_call = rename(current_file, new_target_path);
    			ERROR_rename_call();

                chmod_call = chmod(new_target_path, current_stat.st_mode);
               	ERROR_chmod_call();
    		}
    		else
    		{
    			// Copy file to new_target_path.
    			copyto_target(current_file, new_target_path, current_stat);
    			unlink_call = unlink(current_file);
				ERROR_unlink_call();
    		}
    	}
    	else if(S_ISDIR(current_stat.st_mode))
    	{
    		remove_directory(current_file, new_target_path, same);
    		rmdir_call = rmdir(current_file);
            ERROR_rmdir_call();
    	}
    	free(current_file);
    	free(new_target_path);
        d = readdir(dir); 
    }
    closedir(dir);
    chmod_call = chmod(curr_target_path, srcFolderStat.st_mode);
    ERROR_chmod_call();
}

/* Title of the Program */
void program_title()
{
    printf("\tWelcome to Dumpster Diving\n");
    printf("\tCreated by Jonathan Metzger\n");
    printf("\t{ dv } tool Utility\n\n");
    end_line();
}


/*Print the usage of the command*/
void usage(void)
{
    end_line();
    fprintf(stderr, "dv - retrive file or directory from dumpster\n\n");
    fprintf(stderr, "usage: ./dv [-h] < file(s) ... >\n");
    fprintf(stderr, "  -h:\tusage message\n\n");
    end_line();
    exit(-1);
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

/* ERROR call */
void ERROR_call()
{
	// end_line();
    usage();
    exit(-1);
}

/* no file present */
void ERROR_no_file(int argc)
{
    if (optind == argc)
    {
        fprintf(stderr, "** ERROR: no file present ... **\n\n");
        ERROR_call();
    }
}

/* ERROR call for rename() */
void ERROR_rename_call()
{
    if(rename_call)
    {
        fprintf(stderr, "** ERROR: rename() call failed ... **\n");
        ERROR_call();
    }
}

/* ERROR call for rmdir() */
void ERROR_getcwd_call()
{
    if(!getcwd_call)
    {
        fprintf(stderr, "** ERROR: rmdir() call failed. ** \n");
        ERROR_call();
    }
}

/* ERROR call for mkdir() */
void ERROR_mkdir_call()
{
    if(mkdir_call)
    {   
        fprintf(stderr, "** ERROR: mkdir() call failed. ** \n\n");
        ERROR_call();
    }
}

/* ERROR call for fopen() */
void ERROR_fopen_call(FILE* file)
{
	if(file == NULL)
	{
		fprintf(stderr, "** ERROR: can't open file. **\n");
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

/* ERROR call for unlink() */
void ERROR_unlink_call()
{
    if(unlink_call)
    {
        fprintf(stderr, "** ERROR: unlink() call failed. ** \n");
        ERROR_call();
    }
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

/* ERROR call for chmod() */
void ERROR_chmod_call()
{
	if(chmod_call)
    {
        fprintf(stderr, "** ERROR: chmod() call failed. ** \n");
        ERROR_call();
    }
}

/* ERROR call for utime() */
void ERROR_utime_call()
{
    if(utime_call)
    {
        fprintf(stderr, "** ERROR: utime() call failed. ** \n");
        ERROR_call();
    }
}

/* ERROR call for access() */
void ERROR_access_call()
{
	if(access_call == 0)
	{
		printf("** ERROR: already exists in current directory. **\n");
		ERROR_call();
	}
}

/* ERROR call for opendir() */
void ERROR_opendir_call()
{
    if(dir == NULL)
    {
        fprintf(stderr, "** ERROR: opendir() call failed. ** \n\n");
        ERROR_call();
    }
}

/* ERROR call for fileNotFound() */
void ERROR_fileNotFound(char* source_path)
{
	if(access(source_path, F_OK) == -1)
	{
		char* p = basename(source_path);
		printf("** ERROR: does not exist in the dumpster. **\n\n");
		ERROR_call();
	}
}

/* ERROR call for reading and writing files */
void ERROR_rw_file()
{
	while(bytes = fread(buf, 1, 1024, source))
	{
		fwrite(buf, 1, bytes, target);
	}
    if(ferror(source) || ferror(target))
    {
        fprintf(stderr, "** ERROR: cannot read and write file. **");
        exit(-1);
    }
}

/* sets dumpster path and stat */
void set_dumpster()
{
    dumpster_path = strcat(getenv("PWD"), "/");
    strcat(dumpster_path, dumpster_name);
    dir = opendir(dumpster_path);
    if(dir == NULL)
    {
    	fprintf(stderr, "** ERROR: dumpster does not exist ... **\n");
        printf("> [ Creating new dumpster directory ... ]\n\n");
        mkdir(dumpster_path, 0700);
    }
    if(!dumpster_path)
    {
        fprintf(stderr, "** ERROR: dumpster does not exist ... **\n\n");
		ERROR_call();
    }
    stat_call = stat(dumpster_path, &dumpster_stat);
    if(stat_call)
    {
        fprintf(stderr, "** ERROR: stat() call failed. ** \n");
		ERROR_call();
    }
}