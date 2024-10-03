// fs.c
#include "fs.h"
#include "string.h"
#include "stdio.h"
#include "memory.h"

#define MAX_FILES 64
#define MAX_FILENAME_LENGTH 32

typedef struct {
    char name[MAX_FILENAME_LENGTH];
    int is_directory;
    int parent_index;
    void* data;
    int size;
} fs_node_t;

fs_node_t fs_nodes[MAX_FILES];
int fs_node_count = 0;
int current_directory = 0; // Index of the current directory in fs_nodes

void fs_init() {
    memory_init(); // Initialize memory management
    // Initialize root directory
    memset(fs_nodes, 0, sizeof(fs_nodes));
    strcpy(fs_nodes[0].name, "/");
    fs_nodes[0].is_directory = 1;
    fs_nodes[0].parent_index = -1;
    fs_node_count = 1;

    // For demonstration, create a shell executable
    fs_create_file("dmd.air");
    // Load the shell code into the file (omitted for brevity)
}

void* fs_load_file(const char* filename) {
    for (int i = 0; i < fs_node_count; i++) {
        if (!fs_nodes[i].is_directory &&
            fs_nodes[i].parent_index == current_directory &&
            strcmp(fs_nodes[i].name, filename) == 0) {
            return fs_nodes[i].data;
        }
    }
    return NULL; // File not found
}

int fs_save_file(const char* filename, const void* data, int size) {
    for (int i = 0; i < fs_node_count; i++) {
        if (!fs_nodes[i].is_directory &&
            fs_nodes[i].parent_index == current_directory &&
            strcmp(fs_nodes[i].name, filename) == 0) {
            fs_nodes[i].data = realloc(fs_nodes[i].data, size);
            memcpy(fs_nodes[i].data, data, size);
            fs_nodes[i].size = size;
            return 0; // Success
        }
    }
    return -1; // File not found
}

int fs_create_file(const char* filename) {
    if (fs_node_count >= MAX_FILES) {
        return -1; // No space
    }
    strcpy(fs_nodes[fs_node_count].name, filename);
    fs_nodes[fs_node_count].is_directory = 0;
    fs_nodes[fs_node_count].parent_index = current_directory;
    fs_nodes[fs_node_count].data = malloc(0);
    fs_nodes[fs_node_count].size = 0;
    fs_node_count++;
    return 0; // Success
}

int fs_delete_file(const char* filename) {
    for (int i = 0; i < fs_node_count; i++) {
        if (!fs_nodes[i].is_directory &&
            fs_nodes[i].parent_index == current_directory &&
            strcmp(fs_nodes[i].name, filename) == 0) {
            free(fs_nodes[i].data);
            // Shift remaining nodes
            for (int j = i; j < fs_node_count - 1; j++) {
                fs_nodes[j] = fs_nodes[j + 1];
            }
            fs_node_count--;
            return 0; // Success
        }
    }
    return -1; // File not found
}

int fs_create_directory(const char* dirname) {
    if (fs_node_count >= MAX_FILES) {
        return -1; // No space
    }
    strcpy(fs_nodes[fs_node_count].name, dirname);
    fs_nodes[fs_node_count].is_directory = 1;
    fs_nodes[fs_node_count].parent_index = current_directory;
    fs_node_count++;
    return 0; // Success
}

int fs_delete_directory(const char* dirname) {
    // For simplicity, only delete empty directories
    for (int i = 0; i < fs_node_count; i++) {
        if (fs_nodes[i].is_directory &&
            fs_nodes[i].parent_index == current_directory &&
            strcmp(fs_nodes[i].name, dirname) == 0) {
            // Check if directory is empty
            for (int j = 0; j < fs_node_count; j++) {
                if (fs_nodes[j].parent_index == i) {
                    printf("Error: Directory not empty\n");
                    return -1;
                }
            }
            // Shift remaining nodes
            for (int j = i; j < fs_node_count - 1; j++) {
                fs_nodes[j] = fs_nodes[j + 1];
            }
            fs_node_count--;
            return 0; // Success
        }
    }
    return -1; // Directory not found
}

void fs_list_directory() {
    printf("Contents of directory:\n");
    for (int i = 0; i < fs_node_count; i++) {
        if (fs_nodes[i].parent_index == current_directory) {
            if (fs_nodes[i].is_directory) {
                printf("[DIR]  %s\n", fs_nodes[i].name);
            } else {
                printf("[FILE] %s\n", fs_nodes[i].name);
            }
        }
    }
}

void fs_change_directory(const char* path) {
    if (strcmp(path, "..") == 0) {
        if (fs_nodes[current_directory].parent_index != -1) {
            current_directory = fs_nodes[current_directory].parent_index;
        }
    } else {
        for (int i = 0; i < fs_node_count; i++) {
            if (fs_nodes[i].is_directory &&
                fs_nodes[i].parent_index == current_directory &&
                strcmp(fs_nodes[i].name, path) == 0) {
                current_directory = i;
                return;
            }
        }
        printf("Error: Directory not found\n");
    }
}
