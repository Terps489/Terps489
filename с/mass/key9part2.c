#include <stdio.h>
#define FALSE 0
#define TRUE 99
#define LEN 100
int input(int *a, int *len);
void output(int *a, int n);
void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length, int *error);

int main() {
    int len1, len2, data[LEN], data2[LEN], result1[LEN], result2[LEN], result_length = 0, error = FALSE;
    if (input(data, &len1) == FALSE) {
        printf("n/a");
        return FALSE;
    };
    if (input(data2, &len2) == FALSE) {
        printf("n/a");
        return FALSE;
    };
    sum(data, len1, data2, len2, result1, &result_length);
    output(result1, result_length);
    sub(data, len1, data2, len2, result2, &result_length, &error);
    if (error == TRUE) {
        return TRUE;
    }
    output(result2, result_length);
    return TRUE;
}
int input(int *a, int *len) {
    int c = 0;
    for (int *p = a; p - a < LEN; p++) {
        int d;
        if (scanf("%d", p) != 1 || *p > 9 || *p < 0) {
            return FALSE;
        }
        c++;
        d = getchar();
        if (d == '\n') {
            *len = c;
            return TRUE;
        } else if (d != ' ') {
            return FALSE;
        }
    }
    return TRUE;
}
void output(int *a, int n) {
    int *p = a;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            p++;
        } else {
            i += n;
        }
    }
    for (; p - a < n; p++) {
        printf("%d ", *p);
    }
    printf("\n");
}
void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    result[0] = 0;
    if (len1 > len2) {
        for (int i = 1; i < len1 + 1; i++) {
            if (i >= len1 - len2 + 1) {
                result[i] = buff1[i - 1] + buff2[i - len1 + len2 - 1];
            } else {
                result[i] = buff1[i - 1];
            }
        }
        *result_length = len1 + 1;
    } else if (len1 == len2) {
        for (int i = 1; i < len1 + 1; i++) {
            result[i] = buff1[i - 1] + buff2[i - 1];
        }
        *result_length = len1 + 1;
    } else {
        for (int i = 1; i < len2 + 1; i++) {
            if (i >= len2 - len1 + 1) {
                result[i] = buff2[i - 1] + buff1[i - len2 + len1 - 1];
            } else {
                result[i] = buff2[i - 1];
            }
        }
        *result_length = len2 + 1;
    }
    for (int i = *result_length - 1; i >= 0; i--) {
        if (result[i] > 9) {
            result[i] -= 10;
            result[i - 1]++;
        }
    }
}
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length, int *error) {
    if (len1 > len2) {
        for (int i = 0; i < len1; i++) {
            if (i >= len1 - len2) {
                result[i] = buff1[i] - buff2[i - len1 + len2];
            } else {
                result[i] = buff1[i];
            }
        }
        *result_length = len1;
    } else if (len1 == len2) {
        int count = 0, count2mb = 0;
        for (int i = 0; i < len1; i++) {
            result[i] = buff1[i] - buff2[i];
            count++;
            if (buff1[i] < buff2[i]) {
                count++;
            } else if (buff1[i] > buff2[i]) {
                count -= 200;
            }
            if (count == i + 2) {
                printf("n/a");
                *error = TRUE;
                return;
            }
            if (buff1[i] == buff2[i]) {
                count2mb++;
            }
            if (count2mb == len1) {
                printf("0");
                *error = TRUE;
                return;
            }
        }
        *result_length = len1;
    } else {
        printf("n/a");
        *error = TRUE;
        return;
    }
    for (int i = *result_length; i >= 0; i--) {
        if (result[i] < 0) {
            result[i] += 10;
            result[i - 1]--;
        }
    }
}