// memory.h
#ifndef MEMORY_H
#define MEMORY_H

void* malloc(int size);
void free(void* ptr);
void* realloc(void* ptr, int size);

#endif
