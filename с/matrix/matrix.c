#include <stdio.h>
#include <stdlib.h>

#define TRUE 99
#define FALSE 0
#define NMAX 100
int MatrixType1(int str, int col);
int MatrixType2(int str, int col);
int MatrixType3(int str, int col);
int MatrixType4(int str, int col);

int main() {
    int n = 0, len[2];

    if (scanf("%d", &n) != 1 || n <= 0 || n > 4 || getchar() != '\n') {
        printf("n/a");
        return FALSE;
    }

    for (int i = 0; i < 2; i++) {
        if (scanf("%d", &len[i]) != 1 || len[i] <= 0 || len[i] > NMAX) {
            printf("n/a");
            return FALSE;
        }
    }

    if (n == 1) {
        if (MatrixType1(len[0], len[1]) == FALSE) {
            printf("n/a");
            return FALSE;
        }
    } else if (n == 2) {
        if (MatrixType2(len[0], len[1]) == FALSE) {
            printf("n/a");
            return FALSE;
        }
    } else if (n == 3) {
        if (MatrixType3(len[0], len[1]) == FALSE) {
            printf("n/a");
            return FALSE;
        }
    } else {
        if (MatrixType4(len[0], len[1]) == FALSE) {
            printf("n/a");
            return FALSE;
        }
    }
    return TRUE;
}

int MatrixType1(int str, int col) {
    int array[NMAX][NMAX];
    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            if (scanf("%d", &array[i][j]) != 1) {
                return FALSE;
            }
        }
    }

    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            if (j == col - 1)
                printf("%d", array[i][j]);
            else
                printf("%d ", array[i][j]);
        }
        if (i + 1 != str) {
            printf("\n");
        }
    }
    return TRUE;
}

int MatrixType2(int str, int col) {
    int** pointer_array = calloc(str, sizeof(int*));
    if (pointer_array == NULL) {
        return FALSE;
    }

    for (int i = 0; i < str; i++) {
        pointer_array[i] = calloc(col, sizeof(int));
        if (pointer_array[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(pointer_array[k]);
            }
            free(pointer_array);
            return FALSE;
        }
    }

    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            if (scanf("%d", &pointer_array[i][j]) != 1) {
                for (int k = 0; k < str; k++) {
                    free(pointer_array[k]);
                }
                free(pointer_array);
                return FALSE;
            }
        }
    }

    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            if (j == col - 1)
                printf("%d", pointer_array[i][j]);
            else
                printf("%d ", pointer_array[i][j]);
        }
        if (i + 1 != str) {
            printf("\n");
        }
    }
    for (int i = 0; i < str; i++) {
        free(pointer_array[i]);
    }
    free(pointer_array);

    return TRUE;
}

int MatrixType3(int str, int col) {
    int** pointer_array = calloc(str, sizeof(int*));
    if (pointer_array == NULL) {
        return FALSE;
    }
    int* values_array = calloc(str * col, sizeof(int));
    if (values_array == NULL) {
        free(pointer_array);
        return FALSE;
    }

    for (int i = 0; i < str; i++) {
        pointer_array[i] = values_array + col * i;
    }

    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            if (scanf("%d", &pointer_array[i][j]) != 1) {
                free(values_array);
                free(pointer_array);
                return FALSE;
            }
        }
    }

    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            if (j == col - 1)
                printf("%d", pointer_array[i][j]);
            else
                printf("%d ", pointer_array[i][j]);
        }
        if (i + 1 != str) {
            printf("\n");
        }
    }
    free(values_array);
    free(pointer_array);

    return TRUE;
}

int MatrixType4(int str, int col) {
    int* single_array_matrix = calloc(str * col, sizeof(int));
    if (single_array_matrix == NULL) {
        return FALSE;
    }
    int** ptr = calloc(str, sizeof(int*));
    if (ptr == NULL) {
        free(single_array_matrix);
        return FALSE;
    }
    for (int i = 0; i < str; i++) {
        ptr[i] = single_array_matrix + col * i;
    }

    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            if (scanf("%d", &ptr[i][j]) != 1) {
                free(single_array_matrix);
                free(ptr);
                return FALSE;
            }
        }
    }

    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            if (j == col - 1)
                printf("%d", ptr[i][j]);
            else
                printf("%d ", ptr[i][j]);
        }
        if (i + 1 != str) {
            printf("\n");
        }
    }
    free(single_array_matrix);
    free(ptr);
    return TRUE;
}