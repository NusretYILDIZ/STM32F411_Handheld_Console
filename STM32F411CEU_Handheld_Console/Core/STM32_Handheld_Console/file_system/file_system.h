#ifndef __file_system_h
#define __file_system_h

#include <stdint.h>
#include <stddef.h>

#include "../game_engine/script/script_engine.h"
#include "../system/system_main.h"

#define DIR_GAMES             "GAMES/"
#define DIR_PROJECTS          "PROJECTS/"
#define FILE_SYSTEM_SETTINGS  "SYSSTTNG.BIN"
#define FILE_ENGINE_SETTINGS  "ENGSTTNG.BIN"
#define FILE_GAME_MANIFEST    "MANIFEST.BIN"

#if defined(__arm__)
	#define DIR_ROOT  "/"
#elif defined(__WIN32__)
	#define DIR_ROOT  "./sdcard/"
#elif defined(__ANDROID__)
	#error "Android version for file system is not implemented yet."
#else
	#error "Unsupported platform"
#endif

extern char current_dir[256];

uint8_t fs_init(void);
void fs_deinit(void);
//void fs_init_error(void);
void fs_use_relpath(uint8_t enable);

uint8_t file_exists(const char *filename);
uint8_t dir_exists(const char *path);

uint8_t file_full_read(const char *filename, void *buffer);
uint8_t file_read(const char *filename, void *buffer, size_t offset, size_t size);
uint8_t file_append(const char *filename, void *data, size_t size);
uint8_t file_write(const char *filename, void *data, size_t offset, size_t size);
uint8_t file_rename(const char *old_name, const char *new_name);

uint8_t create_dir(const char *path);
uint8_t set_current_dir(const char *path);

uint8_t delete_file(const char *filepath);
uint8_t delete_dir(const char *path);

uint8_t format_disk(void);


uint8_t get_games_list(RAM_PTR index);
uint8_t get_projects_list(RAM_PTR index);

#endif //__file_system_h