#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_files(char *directory) {
    struct dirent *file;
    DIR *files = opendir(directory);

    if (files == NULL) {
        printf("n/a");
        return;
    }

    while ((file = readdir(files))) {
        char *dot = strrchr(file->d_name, '.');
        if (dot && strcmp(dot, ".h") == 0 || dot && strcmp(dot, ".c") == 0) {
            printf("%s/%s\n", directory, file->d_name);
        }
    }
    closedir(files);
}

int main() {
    char *directory = "../src/ai_modules";

    find_files(directory);

    return 0;
}