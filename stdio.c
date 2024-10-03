// stdio.c
#include "stdio.h"
#include "io.h"

#define VIDEO_MEMORY 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

int cursor_row = 0;
int cursor_col = 0;

void move_cursor() {
    unsigned short position = cursor_row * MAX_COLS + cursor_col;
    outb(0x3D4, 14);
    outb(0x3D5, position >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, position);
}

void clear_screen() {
    char* video_memory = (char*)VIDEO_MEMORY;
    for (int i = 0; i < MAX_ROWS * MAX_COLS * 2; i += 2) {
        video_memory[i] = ' ';
        video_memory[i + 1] = WHITE_ON_BLACK;
    }
    cursor_row = 0;
    cursor_col = 0;
    move_cursor();
}

void printf(const char* str) {
    char* video_memory = (char*)VIDEO_MEMORY;
    int i = 0;
    while (str[i]) {
        if (str[i] == '\n') {
            cursor_row++;
            cursor_col = 0;
        } else {
            int offset = (cursor_row * MAX_COLS + cursor_col) * 2;
            video_memory[offset] = str[i];
            video_memory[offset + 1] = WHITE_ON_BLACK;
            cursor_col++;
            if (cursor_col >= MAX_COLS) {
                cursor_col = 0;
                cursor_row++;
            }
        }
        if (cursor_row >= MAX_ROWS) {
            // Scroll the screen (not implemented in this example)
            cursor_row = 0;
        }
        i++;
    }
    move_cursor();
}
