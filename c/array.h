#ifndef ARRAY_H_
#define ARRAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct ARRAY {
    int size;
    int length;
    int values[];
};

typedef struct ARRAY Array;
void print_error_and_exit();
void clear_array(Array* array);
Array *empty_array(int size);
Array *resize_array(Array *array);
Array *append(Array *array, int value);
Array *append_pad(Array *array, int value);
Array *array_from_int(int value);
Array *array_from_array(int copy[], int copy_length);
Array *extend(Array *target, Array *copy);
Array *extend_pad(Array *target, Array *copy);
void print_array(Array *array);
int sum_array(Array *array);
void inspect_array(Array *array);
void println(int i);
#endif
