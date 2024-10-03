// edit.c
#include "stdio.h"
#include "string.h"
#include "fs.h"

void edit_main(const char* filename) {
    char buffer[1024];
    printf("Editing file: %s\n", filename);

    // Load the file if it exists
    void* data = fs_load_file(filename);
    if (data) {
        strcpy(buffer, data);
        printf("Current content:\n%s\n", buffer);
    } else {
        printf("Creating new file...\n");
        buffer[0] = '\0';
    }

    // Allow user to edit the content
    printf("Enter new content (end with empty line):\n");
    gets(buffer);

    // Save the file
    fs_save_file(filename, buffer, strlen(buffer));
    printf("File saved.\n");
}
