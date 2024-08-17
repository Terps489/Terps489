#include <stdio.h>
#define TRUE 99
#define FALSE 0

int input(int *a, int n);
void output(int *a, int n);
void quick_sort(int *a, int first, int last);
void shell_sort(int *a, int n);
void swap(int *c1, int *c2);

int main() {
    int n = 10, data[n];
    if (input(data, n)) {
        shell_sort(data, n);
        printf("\n");
        quick_sort(data, 0, n - 1);
        output(data, n);
    };
    return FALSE;
}

int input(int *a, int n) {
    int flag = TRUE;
    for (int *p = a; p - a < n; p++) {
        if (scanf("%d", p) != 1) {
            printf("n/a");
            flag = FALSE;
        }
    }
    return flag;
}
void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d ", *p);
    }
}

void quick_sort(int *a, int first, int last) {
    if (first < last) {
        int left = first, right = last, middle = a[(left + right) / 2];
        do {
            while (a[left] < middle) left++;
            while (a[right] > middle) right--;
            if (left <= right) {
                swap(a + left, a + right);
                left++;
                right--;
            }
        } while (left <= right);
        quick_sort(a, first, right);
        quick_sort(a, left, last);
    }
}
void swap(int *c1, int *c2) {
    int b = *c1, c = *c2;
    *c2 = b;
    *c1 = c;
}

void shell_sort(int *a, int n) {
    for (int s = n / 2; s > 0; s /= 2) {
        for (int i = s; i < n; ++i) {
            for (int j = i - s; j >= 0 && a[j] > a[j + s]; j -= s) {
                swap(a + j, a + j + s);
            }
        }
    }
    output(a, n);
}
