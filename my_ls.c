// program logic and argument parsing
#include "my_ls.h"

int is_option(const char *arg, char c) {
    int i = 1;
    while (arg[i]){
        if (arg[i] == c)
            return 1;
        i++;
    }
    return 0;
}

int main(int argc, char **argv) {
    int i, show_all = 0, sort_time = 0, file_count = 0;
    char **files = malloc(argc * sizeof(char *));

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (is_option(argv[i], 'a')) show_all = 1;
            if (is_option(argv[i], 't')) sort_time = 1;
        } else {
            files[file_count++] = argv[i];
        }
    }

    if (file_count == 0) {
        list_dir(".", show_all, sort_time);
    } else if (file_count == 1){
        struct stat st;
        if (lstat(files[0], &st) == 0 && S_ISDIR(st.st_mode)) {
            list_dir(files[0], show_all, sort_time);
        } else {
            list_files(files, file_count, show_all, sort_time);
        }
    } else {
        list_files(files, file_count, show_all, sort_time);
    }

    free(files);
    return 0;
}
