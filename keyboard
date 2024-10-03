// keyboard.c
#include "keyboard.h"
#include "io.h"
#include "stdio.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

char key_buffer[256];
int key_buffer_index = 0;

char getch() {
    char c = 0;
    while (c == 0) {
        if (inb(KEYBOARD_STATUS_PORT) & 0x01) {
            c = inb(KEYBOARD_DATA_PORT);
        }
    }
    return c;
}

void gets(char* buffer) {
    int index = 0;
    char c;
    while ((c = getch()) != '\n') {
        if (c == '\b' && index > 0) {
            index--;
            printf("\b \b");
        } else {
            buffer[index++] = c;
            char str[2] = {c, '\0'};
            printf(str);
        }
    }
    buffer[index] = '\0';
    printf("\n");
}
