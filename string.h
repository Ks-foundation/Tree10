// string.h
#ifndef STRING_H
#define STRING_H

int strlen(const char* str);
void strcpy(char* dest, const char* src);
int strcmp(const char* str1, const char* str2);
void strcat(char* dest, const char* src);
void memcpy(void* dest, const void* src, int n);
void memset(void* dest, int val, int n);

#endif
