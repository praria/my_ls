// function and struct declarations


#ifndef MY_LS_H
#define MY_LS_H

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct s_entry {
    char *name;
    struct timespec mtim; // Note: timespec mtim may not be supported in some MacOS versions
    int is_dir;
} t_entry;

void list_dir(const char* path, int show_all, int sort_time);
void list_files(char **paths, int count, int show_all, int sort_time);
void sort_entries(t_entry *entries, int count, int sort_time);
void free_entries(t_entry *entries, int count);

#endif