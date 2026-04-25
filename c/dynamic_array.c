#include <stdio.h>
#include <stddef.h>
#include <sys/mman.h>

#define HEAP_SIZE (1024 * 1024)
#define ALIGN8(size) (((size) + 7) & ~7)
#define HEADER_SIZE ALIGN8(sizeof(Block))
#define get_element(arr, i, type) \
    (((type*)(arr).data)[i])

typedef struct {
    int* data;
    size_t len;
} Array;

typedef struct Block {
    size_t size;
    struct Block* next;
    struct Block* prev;
    int free;
} Block;

static void* heap_mem  = NULL;
static Block* heap_start = NULL;

static void init_heap() {
    heap_mem = mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    heap_start = (Block*)heap_mem;
    heap_start->size = HEAP_SIZE - HEADER_SIZE;
    heap_start->free = 1;
    heap_start->next = NULL;
    heap_start->prev = NULL;
}

Block* get_block(void* ptr) {
    return (Block*)((char*)ptr - HEADER_SIZE);
}

void my_free(void* ptr) {
    if (!ptr) return;
    Block* block = get_block(ptr);
    block->free = 1;

    if (block->next && block->next->free) {
        block->size += HEADER_SIZE + block->next->size;
        if (block->next->next) block->next->next->prev = block;
        block->next = block->next->next;
    }

    if (block->prev && block->prev->free) {
        block->prev->size += HEADER_SIZE + block->size;
        block->prev->next = block->next;
        if (block->next) block->next->prev = block->prev;
    }
}

void* my_malloc(size_t size) {
    if (!heap_mem) init_heap();
    if (size == 0) return NULL;
    size = ALIGN8(size);

    Block* cur = heap_start;
    while (cur) {
        if (cur->free && cur->size >= size) {
            if (cur->size >= size + HEADER_SIZE + 8) {
                Block* newBlock = (Block*)((char*)cur + HEADER_SIZE + size);
                newBlock->size = cur->size - size - HEADER_SIZE;
                newBlock->free = 1;
                newBlock->next = cur->next;
                newBlock->prev = cur;
                if (cur->next) cur->next->prev = newBlock;
                cur->next = newBlock;
                cur->size = size;
            }
            cur->free = 0;
            return (char*)cur + HEADER_SIZE;
        }
        cur = cur->next;
    }
    return NULL;
}

void* my_calloc(size_t count, size_t size) {
    char* ptr = (char*)my_malloc(count * size);
    if (!ptr) return NULL;
    for (size_t i = 0; i < count * size; i++) {
        *(ptr + i) = 0;
    }
    return ptr;
}

void* my_realloc(void* ptr, size_t new_size) {
    if (!ptr) {
        return my_malloc(new_size);
    }
    if (new_size == 0) {
        my_free(ptr);
        return NULL;
    }
    Block* block = get_block(ptr);
    if (block->size >= new_size) {
        if (block->size - new_size > HEADER_SIZE + 8) {
            Block* new_block = (Block*)((char*)ptr + new_size);
            new_block->size = block->size - new_size - HEADER_SIZE;
            new_block->free = 1;
            new_block->next = block->next;
            new_block->prev = block;
            if (block->next) block->next->prev = new_block;
            block->size = new_size;
            block->next = new_block;
        }
        return ptr;
    }
    void* new_ptr = my_malloc(new_size);
    if (!new_ptr) return NULL;
    char* src = (char*)ptr;
    char* trg = (char*)new_ptr;
    for (size_t i = 0; i < block->size; i++) {
        trg[i] = src[i];
    }
    my_free(ptr);
    return (char*)new_ptr;
}

void print_heap() {
    Block* cur = heap_start;
    while (cur) {
        printf("[%zu bytes(%d)] ", cur->size + HEADER_SIZE, cur->free);
        cur = cur->next;
    }
    printf("\n");
}

Array new_array(size_t len, size_t type_size) {
    return (Array){ .data = my_malloc(len * type_size), .len = len };
}

Array new_empty_array(size_t len, size_t type_size) {
    return (Array){ .data = my_calloc(len, type_size), .len = len};
}

void delete_array(Array* arr) {
    my_free(arr->data);
    arr->data = NULL;   
    arr->len = 0;
}

// int main() {
//     Array arr = new_array(10, sizeof(int));
//     for (size_t i = 0; i < arr.len; i++) {
//         printf("%d", get_element(arr, i, int));
//     }
//     printf("\n");
//     print_heap();
//     delete_array(&arr);
//     print_heap();
// }