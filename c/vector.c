#include <stdio.h>
#include <stddef.h>
#include <sys/mman.h>
#include "dynamic_array.c"

typedef struct Vector {
    void* data;
    size_t len;
    size_t capacity;
    size_t elem_size;
} Vector;

Vector create(size_t elem_size) {
    return (Vector){
        .data = NULL,
        .len = 0,
        .capacity = 0,
        .elem_size = elem_size
    };
}

void vector_push_back(Vector* vec, void* elem) {
    if (vec->len >= vec->capacity) {
        size_t new_capacity = vec->capacity == 0 ? 4 : vec->capacity * 2;
        void* new_data = my_realloc(vec->data, new_capacity * vec->elem_size);
        if (!new_data) return;
        vec->data = new_data;
        vec->capacity = new_capacity;
    }

    char* dst = (char*)vec->data + vec->len * vec->elem_size;
    char* src = (char*)elem;
    for (size_t i = 0; i < vec->elem_size; i++) {
        dst[i] = src[i];
    }
    vec->len++;
}

void* vector_get(Vector* vec, size_t i) {
    if (i >= vec->len) return NULL;
    return (char*)vec->data + i * vec->elem_size;
}

void vector_pop_back(Vector* vec) {
    if (vec->len > 0) vec->len--;
}

void vector_free(Vector* vec) {
    my_free(vec->data);
    vec->data = NULL;
    vec->len = 0;
    vec->capacity = 0;
}

int main() {
    Vector arr = create(sizeof(int));
    int x = 42;
    vector_push_back(&arr, &x);
    x = 31;
    vector_push_back(&arr, &x);
    int* l = arr.data;
    for (int i = 0; i < arr.len; i++) {
        printf("%d\n", l[i]);
    }
    print_heap();
}