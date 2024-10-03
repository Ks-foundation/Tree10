// fs.h
#ifndef FS_H
#define FS_H

void fs_init();
void* fs_load_file(const char* filename);
int fs_save_file(const char* filename, const void* data, int size);
int fs_create_file(const char* filename);
int fs_delete_file(const char* filename);
int fs_create_directory(const char* dirname);
int fs_delete_directory(const char* dirname);
void fs_list_directory();
void fs_change_directory(const char* path);

#endif
