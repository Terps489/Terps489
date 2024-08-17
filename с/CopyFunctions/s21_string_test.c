#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();

int main() {
#ifdef S21_STRLEN_TEST
    s21_strlen_test();
#elif defined(S21_STRCMP_TEST)
    s21_strcmp_test();
#elif defined(S21_STRCPY_TEST)
    s21_strcpy_test();
#elif defined(S21_STRCAT_TEST)
    s21_strcat_test();
#elif defined(S21_STRCHR_TEST)
    s21_strchr_test();
#endif
    return 1;
}

void s21_strlen_test() {
    const char *YES = "SUCCESS", *NO = "FAIL", *tests[] = {"Hello World", " ", ""};
    int test[3] = {11, 1, 0};
    for (int i = 0; i < 3; i++) {
        if (s21_strlen(tests[i]) == test[i])
            printf("%s %d %s", tests[i], test[i], YES);
        else
            printf("%s %d %s", tests[i], test[i], NO);
        if (i != 2) printf("\n");
    }
}
void s21_strcmp_test() {
    const char *YES = "SUCCESS", *NO = "FAIL", *tests1[] = {"abc", "ab", "bc"},
               *tests2[] = {"abc", "abc", "abc"};
    int test[3] = {0, -1, 1};
    for (int i = 0; i < 3; i++) {
        if (s21_strcmp(tests1[i], tests2[i]) == test[i])
            printf("%s %s %d %s", tests1[i], tests2[i], test[i], YES);
        else
            printf("%s %s %d %s", tests1[i], tests2[i], test[i], NO);
        if (i != 2) printf("\n");
    }
}

void s21_strcpy_test() {
    const char *YES = "SUCCESS", *NO = "FAIL", *tests[] = {"Hello World", "Oh, hi", "Bye Bye"};
    for (int i = 0; i < 3; i++) {
        char *buf = malloc((s21_strlen(tests[i]) + 1) * sizeof(char));
        if (buf == NULL) {
            printf("n/a");
            free(buf);
            return;
        }
        buf = s21_strcpy(buf, tests[i]);
        if (s21_strcmp(buf, tests[i]) == 0)
            printf("%s %s %s", buf, tests[i], YES);
        else
            printf("%s %s %s", buf, tests[i], NO);
        if (i != 2) printf("\n");
        free(buf);
    }
}
void s21_strcat_test() {
    char *tests1[] = {"abc", "ab", "bc"};
    const char *YES = "SUCCESS", *NO = "FAIL", *tests2[] = {"abc", "abc", "abc"},
               *tests3[] = {"abcabc", "ababc", "bcabc"};
    for (int i = 0; i < 3; i++) {
        char *buf = malloc((s21_strlen(tests1[i]) + 1) * sizeof(char));
        if (buf == NULL) {
            printf("n/a");
            free(buf);
            return;
        }
        buf = s21_strcpy(buf, tests1[i]);
        if (s21_strcmp(s21_strcat(buf, tests2[i]), tests3[i]) == 0)
            printf("%s %s %s", buf, tests3[i], YES);
        else
            printf("%s %s %s", buf, tests3[i], NO);
        if (i != 2) printf("\n");
        free(buf);
    }
}
void s21_strchr_test() {
    const char *YES = "SUCCESS", *NO = "FAIL", *tests[] = {"abcdefghijklmn", "BGHdsja0", "HEHE.. WHohohohha"},
               *test[] = {"bcdefghijklmn", "0", ""};
    for (int i = 0; i < 3; i++) {
        char *result = s21_strchr(tests[i], tests[0][0]);
        if ((result == NULL && test[i][0] == '\0') || (result != NULL && s21_strcmp(result, test[i]) == 0))
            printf("%s %s %s", result, test[i], YES);
        else
            printf("%s %s %s", result, test[i], NO);
        if (i != 2) printf("\n");
    }
}