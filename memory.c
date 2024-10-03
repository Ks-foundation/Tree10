// memory.c
#include "memory.h"
#include "string.h"

#define HEAP_SIZE 1024 * 1024  // 1 MB heap
char heap[HEAP_SIZE];
int heap_index = 0;

typedef struct mem_block {
    int size;
    int is_free;
    struct mem_block* next;
} mem_block_t;

mem_block_t* free_list = (void*)heap;

void memory_init() {
    free_list->size = HEAP_SIZE - sizeof(mem_block_t);
    free_list->is_free = 1;
    free_list->next = NULL;
}

void* malloc(int size) {
    mem_block_t* current = free_list;
    while (current != NULL) {
        if (current->is_free && current->size >= size) {
            // Split the block if there's excess space
            if (current->size > size + sizeof(mem_block_t)) {
                mem_block_t* new_block = (void*)((char*)current + sizeof(mem_block_t) + size);
                new_block->size = current->size - size - sizeof(mem_block_t);
                new_block->is_free = 1;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }
            current->is_free = 0;
            return (void*)((char*)current + sizeof(mem_block_t));
        }
        current = current->next;
    }
    return NULL; // No suitable block found
}

void free(void* ptr) {
    if (ptr == NULL) return;

    mem_block_t* block = (mem_block_t*)((char*)ptr - sizeof(mem_block_t));
    block->is_free = 1;

    // Coalesce adjacent free blocks
    mem_block_t* current = free_list;
    while (current != NULL) {
        if (current->is_free && current->next && current->next->is_free) {
            current->size += sizeof(mem_block_t) + current->next->size;
            current->next = current->next->next;
        }
        current = current->next;
    }
}

void* realloc(void* ptr, int size) {
    if (ptr == NULL) {
        return malloc(size);
    }
    mem_block_t* block = (mem_block_t*)((char*)ptr - sizeof(mem_block_t));
    if (block->size >= size) {
        // Current block is big enough
        return ptr;
    } else {
        // Allocate new block and copy data
        void* new_ptr = malloc(size);
        if (new_ptr) {
            memcpy(new_ptr, ptr, block->size);
            free(ptr);
        }
        return new_ptr;
    }
}
