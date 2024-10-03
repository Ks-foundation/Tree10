// dmd.c
#include "stdio.h"
#include "string.h"
#include "fs.h"
#include "kernel.h"
#include "memory.h"

void dmd_main() {
    char command[128];

    while (1) {
        printf("dmd> ");
        gets(command);

        if (strcmp(command, "ls") == 0) {
            fs_list_directory();
        } else if (strncmp(command, "cd ", 3) == 0) {
            fs_change_directory(command + 3);
        } else if (strcmp(command, "cd..") == 0) {
            fs_change_directory("..");
        } else if (strncmp(command, "touch ", 6) == 0) {
            if (fs_create_file(command + 6) == 0) {
                printf("File created: %s\n", command + 6);
            } else {
                printf("Error: Unable to create file\n");
            }
        } else if (strncmp(command, "md ", 3) == 0) {
            if (fs_create_directory(command + 3) == 0) {
                printf("Directory created: %s\n", command + 3);
            } else {
                printf("Error: Unable to create directory\n");
            }
        } else if (strncmp(command, "deletedir ", 10) == 0) {
            if (fs_delete_directory(command + 10) == 0) {
                printf("Directory deleted: %s\n", command + 10);
            } else {
                printf("Error: Unable to delete directory\n");
            }
        } else if (strncmp(command, "deletefile ", 11) == 0) {
            if (fs_delete_file(command + 11) == 0) {
                printf("File deleted: %s\n", command + 11);
            } else {
                printf("Error: Unable to delete file\n");
            }
        } else if (strncmp(command, "nano ", 5) == 0) {
            shell_edit_file(command + 5);
        } else if (strncmp(command, "./", 2) == 0) {
            execute_program(command + 2);
        } else {
            printf("Unknown command: %s\n", command);
        }
    }
}

void shell_edit_file(const char* filename) {
    printf("Editing file: %s\n", filename);
    char content[1024];
    gets(content);

    if (fs_save_file(filename, content, strlen(content)) == 0) {
        printf("File saved.\n");
    } else {
        printf("Error: Unable to save file\n");
    }
}
