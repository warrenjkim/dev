#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

typedef struct Array {
    int data[ARRAY_SIZE];
    size_t size;

} Array;


void init_array(Array *arr) {
    arr->size = ARRAY_SIZE;

    for (size_t i = 0; i < arr->size; i++)
        *(arr->data + i) = 0;
}


const int get(const Array *arr, const size_t offset) {
    if (arr->size <= offset)
        exit(1);

    return *(arr->data + offset);
}


void set(Array *arr, size_t offset, const int value) {
    if (arr->size <= offset)
        exit(1);

    *(arr->data + offset) = value;
}


const size_t array_size(const Array *arr) {
    /* Equivalent to:
     *
     * if (arr != NULL)
     *    return arr->size;
     * else
     *     return 0;
     */
    return arr ? arr->size : 0;
}


void print_array(Array *arr) {
    for (size_t i = 0; i < arr->size; i++)
        printf("arr[%ld] = %d\n", i, *(arr->data + i));
}
