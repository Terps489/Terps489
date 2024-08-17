#ifndef STATE_SORT_H
#define STATE_SORT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct my_struct {
    int year, month, day, hour, minute, second, flag, value;
};

int test(int i, int j, int g);
void fun0(FILE *pfile);
void fun1(FILE *pfile);
int fun2(FILE *pfile);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
struct my_struct read_record_from_file(FILE *pfile, int index);
void print_record(const struct my_struct *record);
void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index);
int is_valid_date(int year, int month, int day);
int is_valid_data(int year, int month, int day, int flag, int value);

#endif