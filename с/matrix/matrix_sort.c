#include <stdio.h>
#include <stdlib.h>

#define TRUE 99
#define FALSE 0
#define NMAX 100

int Matrix(int str, int col);
void pre_sort(int str, int col, int** pointer_array);
void sort(int str, int col, int** pointer_array, int* sum_numbers);

int main() {
    int len[2];

    for (int i = 0; i < 2; i++) {
        if (scanf("%d", &len[i]) != 1 || len[i] <= 0 || len[i] > NMAX) {
            printf("n/a");
            return FALSE;
        }
    }
    if (Matrix(len[0], len[1]) == FALSE) {
        printf("n/a");
        return FALSE;
    }
    return 0;
}

int Matrix(int str, int col) {
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

    pre_sort(str, col, pointer_array);

    for (int i = 0; i < str; i++) {
        free(pointer_array[i]);
    }
    free(pointer_array);
    return TRUE;
}

void pre_sort(int str, int col, int** pointer_array) {
    int* sum_numbers = calloc(str, sizeof(int));
    if (sum_numbers == NULL) {
        return;
    }

    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            sum_numbers[i] += pointer_array[i][j];
        }
    }

    sort(str, col, pointer_array, sum_numbers);
    free(sum_numbers);
}

void sort(int str, int col, int** pointer_array, int* sum_numbers) {
    for (int i = 0; i < str - 1; i++) {
        for (int j = i + 1; j < str; j++) {
            if (sum_numbers[i] > sum_numbers[j]) {
                int* temp_ptr = pointer_array[i];
                pointer_array[i] = pointer_array[j];
                pointer_array[j] = temp_ptr;

                int temp_sum = sum_numbers[i];
                sum_numbers[i] = sum_numbers[j];
                sum_numbers[j] = temp_sum;
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
        if (i != str - 1) printf("\n");
    }
}
