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

#define path(p)  DIR_ROOT p

// Taken from FatFs
typedef enum {
	FRES_OK = 0,				/* (0) Succeeded */
	FRES_DISK_ERR,				/* (1) A hard error occurred in the low level disk I/O layer */
	FRES_INT_ERR,				/* (2) Assertion failed */
	FRES_NOT_READY,				/* (3) The physical drive cannot work */
	FRES_NO_FILE,				/* (4) Could not find the file */
	FRES_NO_PATH,				/* (5) Could not find the path */
	FRES_INVALID_NAME,			/* (6) The path name format is invalid */
	FRES_DENIED,				/* (7) Access denied due to prohibited access or directory full */
	FRES_EXIST,					/* (8) Access denied due to prohibited access */
	FRES_INVALID_OBJECT,		/* (9) The file/directory object is invalid */
	FRES_WRITE_PROTECTED,		/* (10) The physical drive is write protected */
	FRES_INVALID_DRIVE,			/* (11) The logical drive number is invalid */
	FRES_NOT_ENABLED,			/* (12) The volume has no work area */
	FRES_NO_FILESYSTEM,			/* (13) There is no valid FAT volume */
	FRES_MKFS_ABORTED,			/* (14) The f_mkfs() aborted due to any problem */
	FRES_TIMEOUT,				/* (15) Could not get a grant to access the volume within defined period */
	FRES_LOCKED,				/* (16) The operation is rejected according to the file sharing policy */
	FRES_NOT_ENOUGH_CORE,		/* (17) LFN working buffer could not be allocated */
	FRES_TOO_MANY_OPEN_FILES,	/* (18) Number of open files > _FS_LOCK */
	FRES_INVALID_PARAMETER,		/* (19) Given parameter is invalid */
	FRES_READ_ERR,				/* (20) Read bytes count is not equal to wanted bytes count */
	FRES_WRITE_ERR,				/* (20) Written bytes count is not equal to wanted bytes count */
} FRES;

extern char current_dir[256];

FRES fs_init(void);
void fs_deinit(void);

FRES file_exists(const char *filename);
FRES dir_exists(const char *path);

FRES file_full_read(const char *filename, void *buffer);
FRES file_read(const char *filename, void *buffer, size_t offset, size_t size);
FRES file_append(const char *filename, void *data, size_t size);
FRES file_write(const char *filename, void *data, size_t offset, size_t size);
FRES file_rename(const char *old_name, const char *new_name);
uint32_t file_size(const char *filename);

FRES create_dir(const char *path);
FRES set_current_dir(const char *path);

FRES delete_file(const char *filepath);
FRES delete_dir(const char *path);

FRES format_disk(void);


uint8_t get_games_list(RAM_PTR index);
uint8_t get_projects_list(RAM_PTR index);

#endif //__file_system_h