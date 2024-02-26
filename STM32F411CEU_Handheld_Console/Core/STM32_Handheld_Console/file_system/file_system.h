#ifndef __file_system_h
#define __file_system_h

void init_fs(void);
void open_file(const char *file_path, unsigned char mode);
void close_file(void);
void read_file(void *buffer, unsigned int count);
void write_file(const void *buffer, unsigned int count);
void lseek_file(unsigned long offset);
void truncate_file(void);
void sync_file(void);
void open_dir(const char *path);
void close_dir(void);
void read_dir(void *file_info);
void find_first(void *file_info, const char *path, const char *pattern);


void* fi_get_file_name(void *file_info);
unsigned long fi_get_file_size(void *file_info);

#endif //__file_system_h