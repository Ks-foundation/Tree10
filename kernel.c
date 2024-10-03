// kernel.c
#include "kernel.h"
#include "fs.h"
#include "string.h"
#include "stdio.h"
#include "memory.h"

void kernel_main() {
    clear_screen();
    printf("Welcome to Tree10 OS!\n");

    fs_init(); // Initialize the file system

    // Load and execute the shell
    execute_program("dmd.air");

    // Halt the system if shell exits
    while (1) {
        // Idle loop
    }
}

void execute_program(const char* filename) {
    void* program_data = fs_load_file(filename);
    if (program_data != NULL) {
        // Assuming the binary is a flat binary with an entry point at the start
        void (*program_entry)() = (void (*)())program_data;
        program_entry();
    } else {
        printf("Error: Cannot find or load %s\n", filename);
    }
}
