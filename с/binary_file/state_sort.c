#include "state_sort.h"
int main() {
    int i = 0, flag = 1;
    char *str = NULL;
    size_t len = 0;

    if (getline(&str, &len, stdin) == -1) {
        printf("n/a");
        free(str);
        return 1;
    }
    str[strcspn(str, "\n")] = '\0';
    FILE *pfile = fopen(str, "rb");
    if (pfile == NULL) {
        printf("n/a");
        flag = 0;
    } else {
        fclose(pfile);
    }
#ifdef QUEST_1
    if (flag && scanf("%d", &i) != 1) {
        printf("n/a");
        flag = 0;
    }

    if (flag) {
        if (i == 0) {
            pfile = fopen(str, "rb");
            if (pfile == NULL) {
                printf("n/a");
                flag = 0;
            } else {
                fun0(pfile);
                fclose(pfile);
            }
        } else if (i == 1) {
            pfile = fopen(str, "r+b");
            if (pfile == NULL) {
                printf("n/a");
                flag = 0;
            } else {
                fun1(pfile);
                fun0(pfile);
                fclose(pfile);
            }
        } else if (i == 2) {
            pfile = fopen(str, "ab");
            if (pfile == NULL) {
                printf("n/a");
                flag = 0;
            } else if (fun2(pfile)) {
                fclose(pfile);
                pfile = fopen(str, "r+b");
                if (pfile != NULL) {
                    fun1(pfile);
                    fun0(pfile);
                    fclose(pfile);
                }
            }
        } else {
            printf("n/a");
        }
    }
#elif defined(QUEST_2)
    int j = -1, g = -1;
    if (flag && scanf("%d.%d.%d", &i, &j, &g) != 3) {
        printf("n/a");
        flag = 0;
    }
    if (flag) {
        if (test(i, j, g)) {
            pfile = fopen(str, "rb");
            int record_count = get_records_count_in_file(pfile);
            int value = -1;
            for (int index = 0; index < record_count && value == -1; ++index) {
                struct my_struct record = read_record_from_file(pfile, index);
                if (record.year == g && record.month == j && record.day == i) {
                    value = record.value;
                    printf("%d", value);
                }
            }
            if (value == -1) printf("n/a");
            fclose(pfile);
        } else {
            printf("n/a");
        }
    }
#elif defined(QUEST_3)
    int j = -1, g = -1, i1 = -1, j1 = -1, g1 = -1;
    if (flag && scanf("%d.%d.%d %d.%d.%d", &i, &j, &g, &i1, &j1, &g1) != 6) {
        printf("n/a");
        flag = 0;
    }
    if (flag) {
        if (test(i, j, g) && test(i1, j1, g1)) {
            if (g < g1 || (g == g1 && j < j1) || (g == g1 && j == j1 && i < i1)) {
                pfile = fopen(str, "r+b");
                if (!pfile) {
                    printf("n/a");
                    flag = 0;
                }
                if (flag) {
                    int record_count = get_records_count_in_file(pfile);
                    int write_index = 0;
                    for (int read_index = 0; read_index < record_count; ++read_index) {
                        struct my_struct record = read_record_from_file(pfile, read_index);
                        if (!(record.year * 10000 + record.month * 100 + record.day >=
                                  g * 10000 + j * 100 + i &&
                              record.year * 10000 + record.month * 100 + record.day <=
                                  g1 * 10000 + j1 * 100 + i1)) {
                            if (write_index != read_index) {
                                fseek(pfile, write_index * sizeof(struct my_struct), SEEK_SET);
                                fwrite(&record, sizeof(struct my_struct), 1, pfile);
                            }
                            write_index++;
                        }
                    }
                    ftruncate(fileno(pfile), write_index * sizeof(struct my_struct));
                    fun0(pfile);
                    fclose(pfile);
                }
            } else
                printf("n/a");
        } else
            printf("n/a");
    }
#endif
    free(str);
    return flag;
}
int test(int i, int j, int g) { return (i > 0 && i < 32 && j > 0 && j <= 12 && g >= 0 && g < 10000); }
int fun2(FILE *pfile) {
    struct my_struct record_to_write;
    int valid = 0;
    scanf("%d", &record_to_write.year);
    scanf("%d", &record_to_write.month);
    scanf("%d", &record_to_write.day);
    scanf("%d", &record_to_write.hour);
    scanf("%d", &record_to_write.minute);
    scanf("%d", &record_to_write.second);
    scanf("%d", &record_to_write.flag);
    scanf("%d", &record_to_write.value);

    valid = is_valid_data(record_to_write.year, record_to_write.month, record_to_write.day,
                          record_to_write.flag, record_to_write.value);
    if (!valid) {
        printf("n/a");
        return 0;
    }
    fwrite(&record_to_write, sizeof(struct my_struct), 1, pfile);
    fflush(pfile);
    return 1;
}
void fun1(FILE *pfile) {
    int record_count = get_records_count_in_file(pfile);
    for (int pass = 0; pass < record_count - 1; ++pass) {
        for (int j = 0; j < record_count - pass - 1; ++j) {
            struct my_struct record1 = read_record_from_file(pfile, j);
            struct my_struct record2 = read_record_from_file(pfile, j + 1);
            size_t count1 = record1.day * 24 * 60 * 60 * 60 + record1.hour * 60 * 60 + record1.minute * 60 +
                            record1.second;
            size_t count2 = record2.day * 24 * 60 * 60 * 60 + record2.hour * 60 * 60 + record2.minute * 60 +
                            record2.second;
            if (record1.year > record2.year ||
                (record1.year == record2.year && record1.month > record2.month) ||
                (record1.year == record2.year && record1.month == record2.month && count1 > count2)) {
                write_record_in_file(pfile, &record1, j + 1);
                write_record_in_file(pfile, &record2, j);
            }
        }
    }
}
void fun0(FILE *pfile) {
    int record_count = get_records_count_in_file(pfile);
    for (int index = 0; index < record_count; ++index) {
        struct my_struct record = read_record_from_file(pfile, index);
        print_record(&record);
    }
}
int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}
int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(struct my_struct);
}

struct my_struct read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(struct my_struct);
    fseek(pfile, offset, SEEK_SET);
    struct my_struct record;
    fread(&record, sizeof(struct my_struct), 1, pfile);
    rewind(pfile);
    return record;
}

void print_record(const struct my_struct *record) {
    printf("%d %d %d %d %d %d %d %d\n", record->year, record->month, record->day, record->hour,
           record->minute, record->second, record->flag, record->value);
}

void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index) {
    int offset = index * sizeof(struct my_struct);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(struct my_struct), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}
int is_valid_date(int year, int month, int day) {
    if (month < 1 || month > 12) return 0;
    int days_in_month;
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            days_in_month = 30;
            break;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                days_in_month = 29;
            } else {
                days_in_month = 28;
            }
            break;
        default:
            days_in_month = 31;
            break;
    }
    return (day >= 1 && day <= days_in_month);
}

int is_valid_data(int year, int month, int day, int flag, int value) {
    return (year >= 0 && year <= 9999 && month >= 1 && month <= 12 && is_valid_date(year, month, day) &&
            (flag == 0 || flag == 1) && value >= 100 && value <= 999);
}
