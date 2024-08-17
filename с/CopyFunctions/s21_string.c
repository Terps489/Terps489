#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

int s21_strlen(const char *str) { return (*str) ? s21_strlen(++str) + 1 : 0; }
int s21_strcmp(const char *str1, const char *str2) {
    int flag = 0;
    while ((*str1 || *str2) && flag == 0) {
        if (*str1 < *str2) {
            flag = -1;
        }
        if (*str1 > *str2) {
            flag = 1;
        }
        str1++;
        str2++;
    }
    return flag;
}
char *s21_strcpy(char *str_new, const char *str) {
    char *start = str_new;
    while (*str) {
        *str_new = *str;
        str++;
        str_new++;
    }
    *str_new = '\0';
    return start;
}
char *s21_strcat(char *str1, const char *str2) {
    char *start = str1;
    while (*str1) {
        str1++;
    }
    while (*str2) {
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
    return start;
}
char *s21_strchr(const char *str, char n) {
    while (*str && *str != n) {
        str++;
    }
    return (*str == n) ? (char *)str + 1 : NULL;
}