
/*
 * rm.c
 * 
 * Jonathan Metzger
 * Spring 2018
 *
 * Project for CS4513 Distributed Computing Systems
 *
 * source: http://stackoverflow.com/questions/8465006/how-to-concatenate-2-strings-in-c
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

/* checks if -f flag is present */
void check_f_flag(char* file);
/* checks if -r flag is present */
void check_r_flag();
/* check to see if dumpster same directory */
void check_dumpster();
/* ERROR call for mkdir() */
void ERROR_mkdir_call();
/* ERROR call for rmdir() */
void ERROR_rmdir_call();
/* ERROR call for unlink() */
void ERROR_unlink_call();
/* ERROR call for open() */
void ERROR_open_call();
/* ERROR call for open() */
void ERROR_chmod_call();
/* ERROR call for utime() */
void ERROR_utime_call();
/* ERROR call for stat() */
void ERROR_stat_call();
/* ERROR call for remove() */
void ERROR_remove_call();
/* ERROR when dumpster limit reached */
void ERROR_limit_dumpster(int number);
/* ERROR call */
void ERROR_call();
/* seperator line */
void end_line();
/* title of the program */
void program_title();
/* prints help message and quit */
void usage();
/* takes flags from input */
void flag_check(int argc, char **argv);
/* checks if no file is present */
void nofile_check(int argc);
/* set dumpster */
void set_dumpster();
/* set file */
void set_file(char* file);
// Get the extension for a given path.
char* get_extension(char* path);
// Get the file path in dumpster for a given file.
void get_dumpsterPath(char* file, char* dumpster_path, char** new_path);
// Concatinate two strings.
char* concat(char* c1, char* c2);
// Copy a file to dumpster across partition.
void copyto_dump(char* file, char* dumpster_path, struct stat file_stat);
// Remove a directory recursivly.
void remove_directory(char* currPath, char* currdumpster_path, int isSamePtn);
// Remove a directory perminently. This is used when -f is specified.
void remove_force(char* directory);

/* initialize FILE */
FILE* src;
FILE* tar;

/* initialize DIR */
DIR* dir;

/* initialize structs */
struct stat dumpster_stat;
struct stat file_stat;
struct stat source_dir;

/* initialize integers */
int number = 0;
int mkdir_call = 0;
int rename_call = 0;
int unlink_call = 0;
int count_file = 0;
int rmdir_call = 0;
int stat_call = 0;
int utime_call = 0;
int chmod_call = 0;
int remove_call = 0;
int i = 0;
int f_flag = 0;
int r_flag = 0;
int tot_flag = 0;    

/* initialize characters */
char* dumpster_name = "dumpster"; /* must match directory in current location */
char* dumpster_path = NULL;
char* new_path = NULL;

/* main */
int main(int argc, char** argv)
{   
    end_line();

    program_title();

    flag_check(argc, argv);

    nofile_check(argc);

    set_dumpster();

    count_file = argc - optind;

    char* files[count_file];
    
    /* create for multiple files */
    for(i = 0; i < count_file; i++)
    {
        files[i] = argv[i + optind];
    }

    /* move file(s) */
    for(i = 0; i < count_file; i ++)
    {
        char* file = files[i];
        /* get file */
        set_file(file);
        if(f_flag)
        {
            /* see if -f flag */
            check_f_flag(file);
        }
        else {
            /* check dumpster */
            check_dumpster(file);
        }
    }

    end_line();
    return 0;
}

/* force remove file */
void remove_force(char* directory)
{
    struct dirent* d;
    dir = opendir(directory);

    if(dir == NULL)
    {
        fprintf(stderr, "** ERROR: open() call failed. ** \n");
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

        struct stat file_stat;
        char* file = concat(directory, "/");
        file = concat(file, d->d_name);
        stat_call = stat(file, &file_stat);
        ERROR_stat_call();
        
        if(S_ISREG(file_stat.st_mode))
        {
            remove_call = remove(file);
            ERROR_remove_call();
        }
        else if(S_ISDIR(file_stat.st_mode))
        {
            remove_force(file);
            rmdir_call = rmdir(file);
            ERROR_rmdir_call();
        }
        free(file);
        d = readdir(dir);
    }
    closedir(dir);
}

/* remove directory */
void remove_directory(char* currPath, char* currdumpster_path, int isSamePtn)
{
    struct dirent* d;
    char* newdumpster_path;
    get_dumpsterPath(currPath, currdumpster_path, &newdumpster_path);

    stat_call = stat(currPath, &source_dir);
    ERROR_stat_call();

    // Create a new directory in dumpster and update currdumpster_path.
    mkdir_call = mkdir(newdumpster_path, source_dir.st_mode);

    dir = opendir(currPath);
    if(dir == NULL)
    {
        perror("open() call failed");
        exit(-1);
    }
    d = readdir(dir);
    while(d)
    {
        if((strcmp(d->d_name, "..") == 0) || (strcmp(d->d_name, ".") == 0))
        {
            d = readdir(dir);
            continue;
        }
        struct stat currStat;
        char* file = concat(currPath, "/");
        file = concat(file, d->d_name);
        int stat_call = stat(file, &currStat);
        if(stat_call)
        {
            fprintf(stderr, "** ERROR: stat() call failed ... **\n");
            exit(-1);
        }
        if(S_ISREG(currStat.st_mode))
        {
            if(isSamePtn)
            {
                
                get_dumpsterPath(file, newdumpster_path, &new_path);
                int rename_call = rename(file, new_path);
                if(rename_call)
                {
                    fprintf(stderr, "** ERROR: rename() call failed ... **\n");
                    ERROR_call();
                }
                int chmod_call = chmod(new_path, currStat.st_mode);
                if(chmod_call)
                {
                    perror("chmod() call failed");
                    exit(chmod_call);
                }
            }
            else
            {
                copyto_dump(file, newdumpster_path, currStat);
                int unlink_call = unlink(file);
                if(unlink_call)
                {
                    perror("unlink() call failed");
                    exit(-1);
                }
            }
        } 
        else if(S_ISDIR(currStat.st_mode))
        {
            remove_directory(file, newdumpster_path, isSamePtn);
            int rmdir_call = rmdir(file);
            if(rmdir_call)
            {
                perror("rmdir() call failed");
                exit(-1);
            }
        }
        free(file);
        d = readdir(dir); 
    }
    closedir(dir);
    chmod_call = chmod(newdumpster_path, source_dir.st_mode);
    ERROR_chmod_call();

    const struct utimbuf srcTim = {source_dir.st_atime, source_dir.st_mtime};
    utime_call = utime(newdumpster_path, &srcTim);
    ERROR_utime_call();
    free(newdumpster_path);
}

/* concate two strings */
char* concat(char* s1, char* s2)
{
    char* result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/* copy to dumpster */
void copyto_dump(char* file, char* dumpster_path, struct stat file_stat)
{
    get_dumpsterPath(file, dumpster_path, &new_path);

    size_t bytes;
    char buf[1024];
    ERROR_open_call(file, &new_path);
    while(bytes = fread(buf, 1, 1024, src))
    {
        fwrite(buf, 1, bytes, tar);
    }
    if(ferror(src) || ferror(tar))
    {
        printf("Error reading and writing file");
        exit(-1);
    }
    fclose(src);
    fclose(tar);
    chmod_call = chmod(new_path, file_stat.st_mode);
    ERROR_chmod_call();

    const struct utimbuf srcTim = {file_stat.st_atime, file_stat.st_mtime};
    int utime_call = utime(new_path, &srcTim);
    ERROR_utime_call();

    free(new_path);
    return;
}

/* get dumpster path */
void get_dumpsterPath(char* file, char* dumpster_path, char** new_path)
{
    char* basec = strdup(file);
    char* bname = basename(basec);
    *new_path = concat(dumpster_path, "/");
    *new_path = concat(*new_path, bname);
    char* ext = get_extension(*new_path);
    if(strcmp(ext, ".0")) { *new_path = concat(*new_path, ext); }
}

/* get extension */
char* get_extension(char* path)
{
    char* temp_path = path;
    int duplicate = 0;
    number = 1;
    char array[2];
    array[1] = '\0';
    
    while(access(temp_path, F_OK) != -1)
    {
        duplicate = 1;
        array[0] = number + 48;
        temp_path = concat(path, concat(".", array));
        ERROR_limit_dumpster(number);
    }

    if(!duplicate)
    {
        array[0] = 48;
        return concat(".", array);
    }
    array[0] = number - 1 + 48;
    free(temp_path);
    return concat(".", array);
}

/* end line */
void end_line(){ printf("\n###########################################\n\n"); }

/* Title of the Program */
void program_title()
{
    end_line();
    printf("\tWelcome to Dumpster Diving\n");
    printf("\tCreated by Jonathan Metzger\n");
    printf("\t{ rm } tool Utility\n");
    end_line();
}

/* Prints help message and quit */
void usage()
{
    printf("rm - Moves files to the dumpster\n\n");
    printf("usage: ./rm -f -h -r < file(s) ... > \n");
    printf("  -f:\tforce a complete remove\n");
    printf("  -h:\tusage message\n");
    printf("  -r:\tremove any subdirectories\n");
    end_line();
    exit(1);
}

/* checks flag of input */
void flag_check(int argc, char **argv)
{
    int option;
    while ((option = getopt (argc, argv, "fhr")) != -1)
    {
        switch (option)
        {

        /* Set to force remove */
            case 'f':
            f_flag++; 
            tot_flag++;
            break;

        /* -h show help message */
            case 'h':
            tot_flag++;
            usage();
            exit(-1);
            break;

        /* Set to copy directories recursively */
            case 'r':
            r_flag++; 
            tot_flag++;
            break;

            default:
            exit(-1);

        }
    }
}

/* no file present */
void nofile_check(int argc)
{
    if (optind == argc)
    {
        fprintf(stderr, "** ERROR: no file present ... **\n");
        end_line();
        usage();
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

/* sets file path and stat */
void set_file(char* file)
{
    if(access(file, F_OK) == -1)
    {
        fprintf(stderr, "** ERROR: file(s) do not exist ... **\n");
        end_line();
        usage();
        exit(-1);
    }

    stat_call = stat(file, &file_stat);
    if(stat_call)
    {
        fprintf(stderr, "** ERROR: stat() call failed. ** \n");
        end_line();
        usage();
        exit(-1);
    }
}

/* checks if -r flag is present */
void check_r_flag()
{
    if(!r_flag)
    {
        printf("** ERROR: -r option missing for directory. **\n");
        ERROR_call();
    }
}

/* checks if -f flag is present */
void check_f_flag(char* file)
{
    /* with f flag */
    if(f_flag)
    {
        if(S_ISREG(file_stat.st_mode))
        {
            /* remove file */
            rmdir_call = remove(file);
            printf("> [ Deleting { %s } file perminently ... ]\n\n", file);
            ERROR_remove_call();
        }

        else if(S_ISDIR(file_stat.st_mode))
        {   
            /* checks if -r is present */
            check_r_flag();
            /* remove directory */
            remove_force(file);
            rmdir_call = remove(file);
            printf("> [ Deleting { %s } directory perminently ... ]\n\n", file);
            ERROR_rmdir_call();
        }
    }
}

/* checks if dumpster in directory */
void check_dumpster(char* file)
{


    if(file_stat.st_dev == dumpster_stat.st_dev)
    {
        if(S_ISREG(file_stat.st_mode))
        {
            char* new_path;
            get_dumpsterPath(file, dumpster_path, &new_path);
            rename(file, new_path);
            printf("> [ Moving { %s } file to dumpster ... ]\n\n", file);
        }
        else if(S_ISDIR(file_stat.st_mode))
        {
            check_r_flag();
            remove_directory(file, dumpster_path, 1);
            rmdir_call = rmdir(file);
            printf("> [ Moving { %s } directory to dumpster ... ]\n\n", file);
            ERROR_rmdir_call();
        }
    }
    else
    {
        // Check for file or directory.
        if(S_ISREG(file_stat.st_mode))
        {
            copyto_dump(file, dumpster_path, file_stat);
            unlink_call = unlink(file);
            ERROR_unlink_call();
        }
        else if(S_ISDIR(file_stat.st_mode))
        {
            check_r_flag();
            remove_directory(file, dumpster_path, 0);
            rmdir_call = rmdir(file);
            ERROR_rmdir_call();
        }
    }
}

/* ERROR call */
void ERROR_call()
{    
    end_line();
    usage();
    exit(-1);
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

/* ERROR call for utime() */
void ERROR_utime_call()
{
    if(utime_call)
    {
        fprintf(stderr, "** ERROR: utime() call failed. ** \n");
        ERROR_call();
    }
}
/* ERROR call for open() */
void ERROR_open_call(char* file, char* new_path)
{


    src = fopen(file, "r");
    if(src == NULL)
    {
        fprintf(stderr, "** ERROR: cannot open { %s } file. ** \n", file);
        ERROR_call();
    }

    tar = fopen(new_path, "w");
    if(tar == NULL)
    {
        fprintf(stderr, "** ERROR: cannot open { %s } file. ** \n", new_path);
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

/* ERROR call for mkdir() */
void ERROR_mkdir_call()
{
    if(mkdir_call)
    {
        fprintf(stderr, "** ERROR: mkdir() call failed. ** \n");
        ERROR_call();
    }
}

/* limits the dumpster size */
void ERROR_limit_dumpster(int number)
{
	if(number == 10)
    {
        printf("Dumpster is full!");
        exit(-1);
    }
    number ++;
}



