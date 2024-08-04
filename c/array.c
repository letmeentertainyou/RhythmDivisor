/* 
    This is a portable resizable Array library built with the ability to import regular C arrays 
    into an Array struct. This version stores an array of ints in Array->values.
*/

#include "array.h"

/* Call this anytime an allocation returns NULL to determine the cause and then exit. */
void print_error_and_exit() {
    if (errno != 0) {
        printf("Program halted because: %s\n", strerror(errno));
        exit(errno);
    }
}

/* Resets all the filled values in the array to zero and resets array->length to zero. */
void clear_array(Array* array) {
    memset(array->values, 0, array->length * sizeof(int));
    if (!array->values) {
        print_error_and_exit();
    }
    array->length = 0;
}

/* Initializes an empty Array of size=size. */
Array *empty_array(int size) {
    Array *array = (Array *)calloc(1, sizeof(Array) + size * sizeof(int));
    if (!array) {
        print_error_and_exit();
    }
    *array = (Array){size, 0};  // This sets the size and length fields.
    return array;
}

/* Copies the contents of the array into a larger one, and then frees original array. */
Array *resize_array(Array *array) {
    Array *new_array = empty_array(array->size * 2);
    new_array->length = array->length;
    memcpy(new_array->values, array->values, array->length * sizeof(int));
    if (!new_array->values) {
        print_error_and_exit();
    }
    free(array);
    return new_array;
}

/* Appends the given value into array and resizes the array if it's full. */
Array *append(Array *array, int value) {
    if (array->length < array->size) {
        array->values[array->length] = value;
        array->length++;
        return array;
    } else {
        return append(resize_array(array), value);
    }
}

/* Appends the given value into array and then pads it with a zero. */
Array *append_pad(Array *array, int value) {
    return append(append(array, value), 0);
}

/* Initializes an Array with the given value in it. */
Array *array_from_int(int value) {
    return append(empty_array(1), value);
}

/* This initializes an Array with a regular C array and it's length. */
Array *array_from_array(int copy[], int copy_length) {
    Array *target = empty_array(copy_length);
    for (int i = 0; i < copy_length; i++) {
        target = append(target, copy[i]);
    }
    return target;
}

/* Iterates over the copy array and appends each element into the target array. */
Array *extend(Array *target, Array *copy) {
    for (int i = 0; i < copy->length; i++) {
        target = append(target, copy->values[i]);
    }
    return target;
}

/* Extends the target array with the copy array and then pads the target with a zero. */
Array *extend_pad(Array *target, Array *copy) {
    return append(extend(target, copy), 0);
}

/* Prints an array for easy reading. */
void print_array(Array *array) {
    if (array->length < 1) {
        printf("Can't print an empty array.\n");
        return;    
    }
    for (int i = 0; i < (array->length); i++) {
        printf("%d ", array->values[i]);
    }
    printf("\n");
}

/* Sums an array. */
int sum_array(Array *array) {
    int sum = 0;
    for (int i = 0; i <array->length; i++){
        sum += array->values[i];
    }
    return sum;
}

/*Prints the size and length an array for debugging. */
void inspect_array(Array *array) {
    printf("size: %i, length: %i.\n", array->size, array->length);
}

/* Print an int and a new line for debugging. */
void println(int i) {
    printf("%i\n", i);
}
