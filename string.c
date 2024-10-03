// string.c
#include "string.h"

int strlen(const char* str) {
    int len = 0;
    while (str[len]) len++;
    return len;
}

void strcpy(char* dest, const char* src) {
    int i = 0;
    while ((dest[i] = src[i]) != '\0') i++;
}

int strcmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] && str2[i]) {
        if (str1[i] != str2[i]) return str1[i] - str2[i];
        i++;
    }
    return str1[i] - str2[i];
}

void strcat(char* dest, const char* src) {
    int dest_len = strlen(dest);
    int i = 0;
    while ((dest[dest_len + i] = src[i]) != '\0') i++;
}

void memcpy(void* dest, const void* src, int n) {
    char* d = dest;
    const char* s = src;
    for (int i = 0; i < n; i++) d[i] = s[i];
}

void memset(void* dest, int val, int n) {
    char* d = dest;
    for (int i = 0; i < n; i++) d[i] = (char)val;
}
