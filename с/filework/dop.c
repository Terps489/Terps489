#include "dop.h"

#include "logger.h"
void fun1(FILE **file, char *str[]) {
    if (*file != NULL) {
        fclose(*file);
    }
    *file = fopen(*str, "r");
    int flag = 1;
    if (*file == NULL) {
        printf("n/a");
        logcat(error, "Файл не открыт :С");
        free(*str);
        *str = NULL;
        flag = 0;
    }
    if (flag) {
        logcat(info, "Файл открыт успешно");
        char ch = fgetc(*file);
        if (ch == EOF) {
            printf("n/a");
            flag = 0;
            logcat(info, "Файл пустой, но все ещё открыт успешно");
        }
        ungetc(ch, *file);
        if (flag) {
            while ((ch = fgetc(*file)) != EOF) {
                putchar(ch);
            }
            logcat(info, "Файл прочитан успешно");
        }
    }
}

void fun2(FILE **file, char str[]) {
    fflush(stdin);
    if (*file != NULL) {
        fclose(*file);
    }

    char *new_str = NULL;
    size_t len = 0;
    getline(&new_str, &len, stdin);
    if (str == NULL) {
        printf("n/a");
        logcat(error, "Строка не инициализирована");
        free(new_str);
        return;
    }
    if (new_str == NULL) {
        printf("n/a");
        logcat(error, "Ошибка выделения памяти для новой строки");
        free(new_str);
        return;
    }

    *file = fopen(str, "a");
    if (*file == NULL) {
        printf("n/a");
        logcat(error, "Ошибка открытия файла для записи");
        free(new_str);
        return;
    }

    fprintf(*file, "%s", new_str);
    size_t needed = snprintf(NULL, 0, "Запись в файл %s строки %s прошла успешно", str, new_str) + 1;
    char *abc = malloc(needed);
    snprintf(abc, needed, "Запись в файл %s строки %s прошла успешно", str, new_str);
    logcat(info, abc);
    free(abc);
    free(new_str);

    fclose(*file);
    *file = fopen(str, "r");
    if (*file == NULL) {
        printf("n/a");
        logcat(error, "Ошибка открытия файла для чтения");
        return;
    }
    char ch;
    while ((ch = fgetc(*file)) != EOF) {
        putchar(ch);
    }
    logcat(info, "Файл прочитан успешно");
}
void fun3() {
    fflush(stdin);
    char *str = NULL;
    size_t len = 0;
    getline(&str, &len, stdin);
    size_t needed = snprintf(NULL, 0, "Выбрана директория %s", str) + 1;
    char *abc = malloc(needed);
    snprintf(abc, needed, "Выбрана директория %s", str);
    logcat(info, abc);
    free(abc);
    if (str == NULL) {
        free(str);
        printf("n/a");
        logcat(error, "Ошибка выбора директории");
        return;
    }
    str[strcspn(str, "\n")] = '\0';
    change_files(str);
    free(str);
}

void change_files(char *directory) {
    int n = 0;
    fflush(stdin);
    logcat(debug, "выбор символа шифрования");
    if (scanf("%d", &n) != 1) {
        printf("n/a");
        logcat(error, "Не удалось нажать на символ");
        fflush(stdin);
        return;
    }
    n = n % 256;
    struct dirent *file;
    DIR *files = opendir(directory);

    if (files == NULL) {
        printf("n/a");
        logcat(error, "Файлы не найдены");
        return;
    }

    while ((file = readdir(files))) {
        char *dot = strrchr(file->d_name, '.');
        if (dot && strcmp(dot, ".h") == 0) {
            size_t dir_len = strlen(directory);
            size_t file_len = strlen(file->d_name);
            size_t path_len = dir_len + file_len + 2;
            char *filepath = malloc(path_len);
            size_t needed = snprintf(NULL, 0, "Открытие файла %s", filepath) + 1;
            char *abc = malloc(needed);
            snprintf(abc, needed, "Открытие файла %s", filepath);
            logcat(debug, abc);
            free(abc);
            if (filepath == NULL) {
                free(filepath);
                printf("n/a");
                logcat(error, "Ошибка!!!");
                return;
            }
            snprintf(filepath, path_len, "%s/%s", directory, file->d_name);
            FILE *remove = fopen(filepath, "w");
            if (remove == NULL) {
                free(remove);
                printf("n/a");
                continue;
            }
            const char *new_str = "";
            fprintf(remove, "%s", new_str);
            size_t needed2 = snprintf(NULL, 0, "Очистка файла %s", filepath) + 1;
            char *abc2 = malloc(needed2);
            snprintf(abc2, needed2, "Очистка файла %s", filepath);
            logcat(debug, abc2);
            free(abc2);
            fclose(remove);
            free(filepath);
        }
        if (dot && strcmp(dot, ".c") == 0) {
            size_t dir_len = strlen(directory);
            size_t file_len = strlen(file->d_name);
            size_t path_len = dir_len + file_len + 2;
            char *filepath = malloc(path_len);
            size_t needed = snprintf(NULL, 0, "Открытие файла %s", filepath) + 1;
            char *abc = malloc(needed);
            snprintf(abc, needed, "Открытие файла %s", filepath);
            logcat(debug, abc);
            free(abc);
            if (filepath == NULL) {
                free(filepath);
                printf("n/a");
                return;
            }
            snprintf(filepath, path_len, "%s/%s", directory, file->d_name);
            FILE *change = fopen(filepath, "r");
            if (change == NULL) {
                free(change);
                printf("n/a");
                logcat(error, "Ошибка!!!");
                continue;
            }
            FILE *temp = fopen("tempfile.txt", "w");
            if (temp == NULL) {
                logcat(error, "Временный файл не создался!!!");
                fclose(change);
                printf("n/a");
            }
            char ch;
            while ((ch = fgetc(change)) != EOF) {
                if (ch != ' ' && ch != '\t' && ch != '\n') {
                    ch = (ch + n) % 256;
                }
                fputc(ch, temp);
            }
            size_t needed1 = snprintf(NULL, 0, "Изменеие файла %s на %d символов", filepath, n) + 1;
            char *abc1 = malloc(needed1);
            snprintf(abc1, needed1, "Изменеие файла %s на %d символов", filepath, n);
            logcat(debug, abc1);
            free(abc1);
            fclose(change);
            fclose(temp);
            remove(filepath);
            rename("tempfile.txt", filepath);
            free(filepath);
        }
    }
    closedir(files);
}