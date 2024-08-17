#include <stdio.h>
#include <stdlib.h>

#define TRUE 99
#define FALSE 0
#define NMAX 100
int MatrixType1(int str, int col);
int MatrixType2(int str, int col);
int MatrixType3(int str, int col);
int MatrixType4(int str, int col);
void max(int str, int col, int array[NMAX][NMAX]);
void min(int str, int col, int array[NMAX][NMAX]);
void max2(int str, int col, int** array);
void min2(int str, int col, int** array);
void max34(int str, int col, int** array, int* bonus_array);
void min34(int str, int col, int** array, int* bonus_array);

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
    max(str, col, array);
    min(str, col, array);
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
    max2(str, col, pointer_array);
    min2(str, col, pointer_array);
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
    max34(str, col, pointer_array, values_array);
    min34(str, col, pointer_array, values_array);
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
    max34(str, col, ptr, single_array_matrix);
    min34(str, col, ptr, single_array_matrix);
    free(single_array_matrix);
    free(ptr);
    return TRUE;
}
void max(int str, int col, int array[NMAX][NMAX]) {
    printf("\n");
    for (int i = 0; i < str; i++) {
        int max_count = array[i][0];
        for (int j = 0; j < col; j++) {
            if (max_count < array[i][j]) max_count = array[i][j];
        }
        if (i == str - 1)
            printf("%d", max_count);
        else
            printf("%d ", max_count);
    }
}
void min(int str, int col, int array[NMAX][NMAX]) {
    printf("\n");
    for (int i = 0; i < col; i++) {
        int min_count = 2147483647;
        for (int j = 0; j < str; j++) {
            if (min_count > array[j][i]) min_count = array[j][i];
        }
        if (i == col - 1)
            printf("%d", min_count);
        else
            printf("%d ", min_count);
    }
}
void max2(int str, int col, int** array) {
    printf("\n");
    for (int i = 0; i < str; i++) {
        int max_count = array[i][0];
        for (int j = 0; j < col; j++) {
            if (max_count < array[i][j]) max_count = array[i][j];
        }
        if (i == str - 1)
            printf("%d", max_count);
        else
            printf("%d ", max_count);
    }
}
void min2(int str, int col, int** array) {
    printf("\n");
    for (int i = 0; i < col; i++) {
        int min_count = 2147483647;
        for (int j = 0; j < str; j++) {
            if (min_count > array[j][i]) min_count = array[j][i];
        }
        if (i == col - 1)
            printf("%d", min_count);
        else
            printf("%d ", min_count);
    }
}
void max34(int str, int col, int** array, int* bonus_array) {
    printf("\n");
    for (int i = 0; i < str; i++) {
        array[i] = bonus_array + col * i;
    }
    for (int i = 0; i < str; i++) {
        int max_count = array[i][0];
        for (int j = 0; j < col; j++) {
            if (max_count < array[i][j]) max_count = array[i][j];
        }
        if (i == str - 1)
            printf("%d", max_count);
        else
            printf("%d ", max_count);
    }
}
void min34(int str, int col, int** array, int* bonus_array) {
    printf("\n");
    for (int i = 0; i < str; i++) {
        array[i] = bonus_array + col * i;
    }
    for (int i = 0; i < col; i++) {
        int min_count = 2147483647;
        for (int j = 0; j < str; j++) {
            if (min_count > array[j][i]) min_count = array[j][i];
        }
        if (i == col - 1)
            printf("%d", min_count);
        else
            printf("%d ", min_count);
    }
}