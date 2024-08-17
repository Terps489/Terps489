#include <stdio.h>

int del(int a);
int funfun(int b);
int main() {
    int x;
    if (scanf("%d", &x) != 1 || x == 0 || x == -1 || x == 1) {
        printf("n/a\n");
        return 1;
    } else {
        char d;
        if ((d = getchar()) != '\n') {
            printf("n/a\n");
            return 2;
        } else {
            printf("%d\n", del(x));
            return 0;
        }
    }
}
int del(int a) {
    int i, m;
    if (a > 0) {
        for (i = a - 1; i >= 0; i--) {
            if (i < 2) {
                printf("%");
                return a;
            }
            m = a;
            while (m > 0) {
                m = m - i;
                if (m == 0 && funfun(i) == 0) {
                    return i;
                }
            }
        }
    } else {
        for (i = a + 2; i < 3; i++) {
            if (i >= -1) {
                printf("%");
                return -a;
            }
            m = a;
            while (m < 0) {
                m = m - i;
                if (m == 0 && funfun(-i) == 0) {
                    return -i;
                }
            }
        }
    }
}

int funfun(int b) {
    int j, k;
    for (j = 2; j <= b; j++) {
        if (j == b) {
            return 0;
        }
        k = b;
        while (k > 0) {
            k = k - j;
            if (k == 0) {
                return 99;
            }
        }
    }
}
