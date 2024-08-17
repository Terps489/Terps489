#include <stdio.h>
#include <stdlib.h>

#define TRUE 99
#define FALSE 0

int input(int **matrix, int n, int m);
void output(int **matrix, int n, int m);
int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);
int transpose(int ***matrix, int *n, int *m);
int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);

int main() {
    int n = 0, len1[2], len2[2], len3[2];

    if (scanf("%d", &n) != 1 || n <= 0 || n > 3 || getchar() != '\n') {
        printf("n/a");
        return FALSE;
    }

    for (int i = 0; i < 2; i++) {
        if (scanf("%d", &len1[i]) != 1 || len1[i] <= 0) {
            printf("n/a");
            return FALSE;
        }
    }
    int **array_1 = calloc(len1[0], sizeof(int *));
    if (array_1 == NULL) {
        return FALSE;
    }

    for (int i = 0; i < len1[0]; i++) {
        array_1[i] = calloc(len1[1], sizeof(int));
        if (array_1[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(array_1[k]);
            }
            free(array_1);
            return FALSE;
        }
    }
    input(array_1, len1[0], len1[1]);

    int **array_2 = NULL;
    if (n != 3) {
        for (int i = 0; i < 2; i++) {
            if (scanf("%d", &len2[i]) != 1 || len2[i] <= 0) {
                printf("n/a");
                return FALSE;
            }
        }
        if ((n == 1 && (len1[1] != len2[1] || len1[0] != len2[0])) || (n == 2 && len1[1] != len2[0])) {
            printf("n/a");
            return FALSE;
        }
        array_2 = calloc(len2[0], sizeof(int *));
        if (array_2 == NULL) {
            return FALSE;
        }

        for (int i = 0; i < len2[0]; i++) {
            array_2[i] = calloc(len2[1], sizeof(int));
            if (array_2[i] == NULL) {
                for (int k = 0; k < i; k++) {
                    free(array_2[k]);
                }
                free(array_2);
                return FALSE;
            }
        }
        input(array_2, len2[0], len2[1]);
    }

    int **array_3 = calloc(len1[0], sizeof(int *));
    if (array_3 == NULL) {
        return FALSE;
    }

    if (n == 1) {
        sum(array_1, len1[0], len1[1], array_2, len2[0], len2[1], array_3, &len3[0], &len3[1]);
        output(array_3, len3[0], len3[1]);
    } else if (n == 2) {
        mul(array_1, len1[0], len1[1], array_2, len2[0], len2[1], array_3, &len3[0], &len3[1]);
        output(array_3, len3[0], len3[1]);
    } else {
        transpose(&array_1, &len1[0], &len1[1]);
        output(array_1, len1[0], len1[1]);
    }

    for (int i = 0; i < len1[0]; i++) {
        free(array_1[i]);
        free(array_3[i]);
    }
    free(array_1);
    free(array_3);

    if (array_2 != NULL) {
        for (int i = 0; i < len2[0]; i++) {
            free(array_2[i]);
        }
        free(array_2);
    }

    return TRUE;
}

int input(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                for (int k = 0; k < n; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                return FALSE;
            }
        }
    }
    return TRUE;
}

int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    int flag = TRUE;
    if (n_second != m_second || n_first != m_first) {
        flag = FALSE;
    }
    for (int i = 0; i < n_first; i++) {
        matrix_result[i] = calloc(m_first, sizeof(int));
        if (matrix_result[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix_result[k]);
            }
            free(matrix_result);
            flag = FALSE;
        }
    }
    *n_result = n_first;
    *m_result = m_first;
    for (int i = 0; i < n_first; i++) {
        for (int j = 0; j < m_first; j++) {
            matrix_result[i][j] = matrix_first[i][j] + matrix_second[i][j];
        }
    }
    return flag;
}

int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    if (n_second == 0) return FALSE;
    *n_result = n_first;
    *m_result = m_second;
    for (int i = 0; i < n_first; i++) {
        matrix_result[i] = calloc(m_second, sizeof(int));
        if (matrix_result[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix_result[k]);
            }
            free(matrix_result);
            return FALSE;
        }
    }
    for (int i = 0; i < n_first; i++) {
        for (int j = 0; j < m_second; j++) {
            matrix_result[i][j] = 0;
            for (int k = 0; k < m_first; k++) {
                matrix_result[i][j] += matrix_first[i][k] * matrix_second[k][j];
            }
        }
    }
    return TRUE;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j != m - 1)
                printf("%d ", matrix[i][j]);
            else
                printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}

int transpose(int ***matrix, int *n, int *m) {
    int **transposed = calloc(*m, sizeof(int *));
    if (transposed == NULL) {
        return FALSE;
    }

    for (int i = 0; i < *m; i++) {
        transposed[i] = calloc(*n, sizeof(int));
        if (transposed[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(transposed[k]);
            }
            free(transposed);
            return FALSE;
        }
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            transposed[j][i] = (*matrix)[i][j];
        }
    }

    for (int i = 0; i < *n; i++) {
        free((*matrix)[i]);
    }
    free(*matrix);

    *matrix = transposed;

    int temp = *n;
    *n = *m;
    *m = temp;

    return TRUE;
}
