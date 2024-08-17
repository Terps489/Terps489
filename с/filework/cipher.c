#include "dop.h"
#include "logger.h"
int start();
int main() { return start(); }

int start() {
    if (log_init("program.log") != 0) {
        printf("Ошибка открытия файла лога\n");
        return 1;
    }
    logcat(debug, "Начало работы");
    int i = 0, flag = 1;
    char *str = NULL;
    size_t len = 0;
    FILE *file = NULL;
    while (i != -1 && flag) {
        if (scanf("%d", &i) != 1) {
            printf("n/a");
            logcat(error, "Ошибка ввода числа");
            return 0;
        }
        if (i == 1) {
            fflush(stdin);
            if (str != NULL) str = NULL;
            getline(&str, &len, stdin);
            if (str == NULL) {
                free(str);
                printf("n/a");
                logcat(error, "Ошибка выделения памяти под строку");
                return 0;
            }
            str[strcspn(str, "\n")] = '\0';
            fun1(&file, &str);
            free(str);
        } else if (i == 2) {
            fun2(&file, str);
        } else if (i == 3) {
            fun3();
        } else if (i == 3) {
            fun3();
        } else if (i == -1) {
            logcat(debug, "Конец работы");
        } else
            logcat(trace, "Введено значение, не соответствующее операциям");
        if (i != -1) printf("\n");
    }
    if (file != NULL) {
        fclose(file);
        logcat(info, "Файл закрыт");
    }
    log_close();
    return flag;
}