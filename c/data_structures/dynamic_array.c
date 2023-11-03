#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define SCALE 1.5
#define THRESHOLD 10


typedef struct DynamicArray {
    int *data;
    size_t size;
    size_t capacity;
} DynamicArray;

void init_darray(DynamicArray *darr, const size_t capacity) {
    darr->capacity = capacity;
    darr->size = 0;

    darr->data = (int *)calloc(capacity, sizeof(int));

    assert(darr->data);
}


void free_darray(DynamicArray *darr) {
    if (!darr)
        return;

    free(darr->data);
    darr->data = NULL;
    darr->size = 0;
    darr->capacity = 0;
}


const int get(const DynamicArray *darr, const size_t offset) {
    assert(darr);
    assert(offset < darr->capacity);

    return *(darr->data + offset);
}


void resize(DynamicArray *darr, const size_t to_capacity) {
    int *temp = (int *)realloc(darr->data, to_capacity * sizeof(int));

    assert(temp);

    darr->data = temp;
    darr->capacity = to_capacity;

    for (size_t i = darr->size; i < darr->capacity; i++)
        darr->data[i] = 0;
}


void push_back(DynamicArray *darr, const int value) {
    assert(darr);

    if (darr->size == darr->capacity) {
        size_t to_capacity = darr->capacity < THRESHOLD ? darr->capacity << 1 : (size_t)(darr->capacity * SCALE);
        resize(darr, to_capacity);
    }

    darr->data[darr->size++] = value;
}


void pop_back(DynamicArray *darr) {
    assert(darr);

    if (darr->size == 0)
        return;
    
    darr->size--;
}


const bool empty(const DynamicArray *darr) {
    assert(darr);
    return darr->size == 0;
}


int front(const DynamicArray *darr) {
    assert(darr);
    assert(0 < darr->size);

    return *(darr->data);
}


int back(const DynamicArray *darr) {
    assert(darr);
    assert(0 < darr->size);

    return darr->data[darr->size - 1];
}


void clear(DynamicArray *darr) {
    assert(darr);

    for (size_t i = 0; i < darr->size; i++)
        darr->data[i] = 0;
    darr->size = 0;
}
