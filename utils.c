// utility funcitons like sorting, listing files/ directories
#include "my_ls.h"

void bubble_sort(t_entry *entries, int count, int sort_time) {
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            int cmp = 0;
            if (sort_time) {
                if (entries[j].mtim.tv_sec < entries[j+1].mtim.tv_sec ||
                   (entries[j].mtim.tv_sec == entries[j+1].mtim.tv_sec &&
                    entries[j].mtim.tv_nsec < entries[j+1].mtim.tv_nsec)) {
                    cmp = 1;
                }
            } else {
                if (strcmp(entries[j].name, entries[j+1].name) > 0) {
                    cmp = 1;
                }
            }

            if (cmp) {
                t_entry tmp = entries[j];
                entries[j] = entries[j+1];
                entries[j+1] = tmp;
            }
        }
    }
}


void sort_entries(t_entry *entries, int count, int sort_time){
    bubble_sort(entries, count, sort_time);
}

void free_entries(t_entry *entries, int count){
    int i;
    for (i = 0; i < count; i++){
        free(entries[i].name);
    }
    free(entries);
}

void list_dir(const char *path, int show_all, int sort_time){
    DIR *dir = opendir(path);
    struct dirent *dp;
    t_entry *entries = NULL;
    int count = 0;

    if (!dir) return;

    while ((dp = readdir(dir))) {
        if (!show_all && dp->d_name[0] == '.') continue;

        entries = realloc(entries, sizeof(t_entry) * (count + 1));
        if (!entries) return;

        entries[count].name = strdup(dp->d_name);
        char full[1024];
        struct stat st;
        snprintf(full, sizeof(full), "%s/%s", path, dp->d_name);
        lstat(full, &st);
        entries[count].mtim = st.st_mtim;
        entries[count].is_dir = S_ISDIR(st.st_mode);
        count++;
    }
    closedir(dir);

    sort_entries(entries, count, sort_time);
    for (int i = 0; i < count; i++) {
        printf("%s\n", entries[i].name);
    }
    free_entries(entries, count);
}

void list_files(char **paths, int count, int show_all, int sort_time){
    t_entry *files = malloc(count * sizeof(t_entry));
    t_entry *dirs = malloc(count * sizeof(t_entry));
    int fcount = 0, dcount = 0;

    for (int i = 0; i < count; i++) {
        struct stat st;
        if (lstat(paths[i], &st) == -1) continue;

        if (S_ISDIR(st.st_mode)) {
            dirs[dcount].name = strdup(paths[i]);
            dirs[dcount].mtim = st.st_mtim;
            dirs[dcount].is_dir = 1;
            dcount++;
        } else {
            files[fcount].name = strdup(paths[i]);
            files[fcount].mtim = st.st_mtim;
            files[fcount].is_dir = 0;
            fcount++;
        }
    }

    sort_entries(files, fcount, sort_time);
    sort_entries(dirs, dcount, sort_time);

    for (int i = 0; i < fcount; i++) printf("%s\n", files[i].name);

    for (int i = 0; i < dcount; i++) {
        if (fcount + dcount > 1) {
            if (i != 0 || fcount > 0) {
                printf("\n");
            }
            printf("%s:\n", dirs[i].name);
        }
        list_dir(dirs[i].name, show_all, sort_time);
    }

    free_entries(files, fcount);
    free_entries(dirs, dcount);
}