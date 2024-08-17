#include <stdio.h>
#include <stdlib.h>

#define TRUE 99
#define FALSE 0

int input(int *a, int n);
void output(int *a, int n);
void sort(int *a, int n);
void pre_sort(int *c1, int *c2);

int main() {
    int n = 0;
    if (scanf("%d", &n) != 1 || n <= 0 || getchar() != '\n') {
        printf("n/a");
        return FALSE;
    }
    int *data = (int *)calloc(n, sizeof(int));
    if (data == NULL) {
        printf("n/a");
        return FALSE;
    }

    if (input(data, n) == FALSE) {
        printf("n/a");
        free(data);
        data = NULL;
        return FALSE;
    }

    sort(data, n);
    output(data, n);

    free(data);
    data = NULL;
    return TRUE;
}

int input(int *a, int n) {
    int flag = TRUE;
    for (int *p = a; p - a < n; p++) {
        if (scanf("%d", p) != 1 || *p != (int)*p) {
            flag = FALSE;
        }
    }
    return flag;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i != n - 1)
            printf("%d ", a[i]);
        else
            printf("%d", a[i]);
    }
}

void sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                pre_sort(&a[j], &a[j + 1]);
            }
        }
    }
}

void pre_sort(int *c1, int *c2) {
    int temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}
