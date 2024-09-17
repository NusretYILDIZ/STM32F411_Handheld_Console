#include "./file_system.h"

#if defined(__arm__)

#include "fatfs.h"

FATFS fs;

FRES fs_init(void)
{
	return f_mount(&fs, "", 1);
}

void fs_deinit(void)
{
	f_mount(0, "", 0);
}

FRES file_exists(const char *filename)
{
	return f_stat(filename, 0);
}

FRES dir_exists(const char *path)
{
	return f_stat(path, 0);
}

FRES file_full_read(const char *filename, void *buffer)
{
	FIL file;
	FRESULT res;
	FSIZE_t file_size, read_size;
	
	res = f_open(&file, filename, FA_READ);
	if(res) return res;
	
	file_size = f_size(&file);
	res = f_read(&file, buffer, file_size, &read_size);
	if(res) return res;
	
	res = f_close(&file);
	if(res) return res;
	
	if(read_size != file_size) return FRES_READ_ERR;
	else return FRES_OK;
}

FRES file_read(const char *filename, void *buffer, size_t offset, size_t size)
{
	FIL file;
	FRESULT res;
	FSIZE_t read_size;
	
	res = f_open(&file, filename, FA_READ);
	if(res) return res;
	
	res = f_lseek(&file, offset);
	if(res) return res;
	
	res = f_read(&file, buffer, size, &read_size);
	if(res) return res;
	
	res = f_close(&file);
	if(res) return res;
	
	if(read_size != size) return FRES_READ_ERR;
	else return FRES_OK;
}

FRES file_append(const char *filename, void *data, size_t size)
{
	FIL file;
	FRESULT res;
	FSIZE_t write_size;
	
	res = f_open(&file, filename, FA_OPEN_APPEND | FA_WRITE);
	if(res) return res;
	
	res = f_write(&file, buffer, size, &write_size);
	if(res)
	{
		f_close(&file);
		return res;
	}
	
	res = f_close(&file);
	if(res) return res;
	
	if(write_size != size) return FRES_WRITE_ERR;
	else return FRES_OK;
}

FRES file_write(const char *filename, void *data, size_t offset, size_t size)
{
	FIL file;
	FRESULT res;
	FSIZE_t write_size;
	
	res = f_open(&file, filename, FA_READ | FA_WRITE);
	if(res) return res;
	
	res = f_lseek(&file, offset);
	if(res) return res;
	
	res = f_write(&file, buffer, size, &write_size);
	if(res)
	{
		f_close(&file);
		return res;
	}
	
	res = f_close(&file);
	if(res) return res;
	
	if(write_size != size) return FRES_WRITE_ERR;
	else return FRES_OK;
}

FRES file_rename(const char *old_name, const char *new_name)
{
	return f_rename(old_name, new_name);
}

uint32_t file_size(const char *filename)
{
	FILINFO file_info;
	FRES res;
	
	res = f_stat(filename, &file_info);
	
	return (res) ? 0 : file_info.fsize;
}

FRES create_dir(const char *path)
{
	return f_mkdir(path);
}

FRES set_current_dir(const char *path)
{
	return f_chdir(path);
}

FRES delete_file(const char *filepath)
{
	return f_unlink(filepath);
}

FRES delete_dir(const char *path)
{
	return f_unlink(path);
}

FRES format_disk(void)
{
	BYTE work[_MAX_SS];
	
	return f_mkfs("", FM_FAT32, 0, work, sizeof(work));
}

uint8_t get_games_list(RAM_PTR index)
{
	return 0;
}

uint8_t get_projects_list(RAM_PTR index)
{
	
}


#elif defined(__WIN32__)

#include <stdio.h>
#include <windows.h>

char current_dir[256] = { '\0' };

#include "../system/settings.h"

FRES fs_init(void)
{
	if(dir_exists("sdcard") != FRES_OK) return create_dir("sdcard");
	
	return FRES_OK;
}

void fs_deinit(void)
{
	// There is nothing to deinitialize.
}

FRES file_exists(const char *filename)
{
	if(!filename) return FRES_INVALID_PARAMETER;
	
	FILE *file = fopen(filename, "rb");
	
	if(file)
	{
		fclose(file);
		return FRES_OK;
	}
	else return FRES_NO_FILE;
}

FRES dir_exists(const char *path)
{
	DWORD attrib = GetFileAttributesA(path);
	
	if(attrib == INVALID_FILE_ATTRIBUTES) return FRES_NO_PATH;
	if(attrib & FILE_ATTRIBUTE_DIRECTORY) return FRES_OK;
	
	return FRES_NO_PATH;
}

FRES file_full_read(const char *filename, void *buffer)
{
	if(!buffer) return FRES_INVALID_PARAMETER;  // Cannot write to null pointer, abort.
	
	size_t file_size, read_size;
	FILE *file;
	
	// For details about file modes: https://stackoverflow.com/a/1466036
	file = fopen(filename, "rb");  // Read in binary mode.
	if(!file) return FRES_NO_FILE;  // File could not be opened.
	
	fseek(file, 0L, SEEK_END);
	file_size = ftell(file);
	rewind(file);
	
	read_size = fread(buffer, file_size, 1, file);
	if(read_size != file_size) return FRES_READ_ERR;  // Error during reading file.
	
	fclose(file);
	return FRES_OK;
}

FRES file_read(const char *filename, void *buffer, size_t offset, size_t size)
{
	if(!buffer) return FRES_INVALID_PARAMETER;  // Cannot write to null pointer, abort.
	
	size_t read_size;
	FILE *file;
	
	// For details about file modes: https://stackoverflow.com/a/1466036
	file = fopen(filename, "rb");  // Read in binary mode.
	if(!file) return FRES_NO_FILE;  // File could not be opened.
	
	fseek(file, offset, SEEK_SET);
	
	read_size = fread(buffer, size, 1, file);
	if(read_size != size) return FRES_READ_ERR;  // Error during reading file.
	
	fclose(file);
	return FRES_OK;  // Success.
}

FRES file_append(const char *filename, void *data, size_t size)
{
	size_t write_size;
	FILE *file;
	
	// For details about file modes: https://stackoverflow.com/a/1466036
	file = fopen(filename, "ab");  // Append in binary mode.
	if(!file) return FRES_NO_FILE;  // File could not be opened.
	
	write_size = fwrite(data, size, 1, file);
	if(write_size != size) return FRES_WRITE_ERR;  // Error during writing to file.
	
	fclose(file);
	return FRES_OK;
}

FRES file_write(const char *filename, void *data, size_t offset, size_t size)
{
	size_t write_size;
	FILE *file;
	
	// For details about file modes: https://stackoverflow.com/a/1466036
	file = fopen(filename, "r+b");  // Read and write in binary mode.
	if(!file) return FRES_NO_FILE;  // File could not be opened.
	
	fseek(file, offset, SEEK_SET);
	
	write_size = fwrite(data, size, 1, file);
	if(write_size != size) return FRES_WRITE_ERR;  // Error during writing to file.
	
	fclose(file);
	return FRES_OK;
}

FRES file_rename(const char *old_name, const char *new_name)
{
	if(!rename(old_name, new_name)) return FRES_OK;
	else return FRES_INT_ERR;
}

uint32_t file_size(const char *filename)
{
	size_t file_size;
	FILE *file;
	
	file = fopen(filename, "rb");
	if(!file) return 0;
	
	fseek(file, 0L, SEEK_END);
	file_size = ftell(file);
	rewind(file);
	fclose(file);
	
	return file_size;
}

FRES create_dir(const char *path)
{
	if(CreateDirectory(path, NULL)) return FRES_OK;
	else return FRES_INT_ERR;
}

FRES set_current_dir(const char *path)
{
	if(strlen(path) > 255) return FRES_NOT_ENOUGH_CORE;
	
	memset(current_dir, '\0', sizeof(current_dir));
	strcpy(current_dir, path);
	
	return FRES_OK;
}

FRES delete_file(const char *filepath)
{
	if(!remove(filepath)) return FRES_OK;
	else return FRES_INT_ERR;
}

FRES delete_dir(const char *path)
{
	if(RemoveDirectory(path)) return FRES_OK;
	else return FRES_INT_ERR;
}

FRES format_disk()
{
	system("rd /q /s sdcard");
	system("md sdcard");
	
	return FRES_OK;
}

#define get_menu_item(addr, index)  ((MENU_ITEM *)(&ram[addr + sizeof(MENU_ITEM) * index]))

uint8_t get_games_list(RAM_PTR list_addr)
{
	WIN32_FIND_DATA find_data_file;
	HANDLE file_handler = 0;
	uint16_t item_count = 0;
	
	char path[256] = { '\0' };
	sprintf(path, DIR_ROOT DIR_GAMES);
	//strcpy(path, DIR_ROOT DIR_GAMES);
	//strcat(path, "*");
	
	file_handler = FindFirstFileA(DIR_ROOT DIR_GAMES "*", &find_data_file);
	
	if(file_handler == INVALID_HANDLE_VALUE) return 0;
	
	do
	{
		if(strcmp(find_data_file.cFileName, ".") != 0 && strcmp(find_data_file.cFileName, "..") != 0 && find_data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			WIN32_FIND_DATA game_files;
			HANDLE game_files_handler = 0;
			
			sprintf(path, DIR_ROOT DIR_GAMES "%s/*.bin", find_data_file.cFileName);
			game_files_handler = FindFirstFileA(path, &game_files);
			
			if(game_files_handler == INVALID_HANDLE_VALUE)
			{
				sprintf(get_menu_item(list_addr, item_count)->menu_text.text, get_str(STR_CORRUPTED_DATA));
				get_menu_item(list_addr, item_count)->action = corrupted_game_error;
				item_count++;
				
				continue;
			}
			
			do
			{
				// If current file is MANIFEST.BIN
				if(strcmp(game_files.cFileName, ".") != 0 && strcmp(game_files.cFileName, "..") != 0 && 
					!(game_files.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
					strcmp(game_files.cFileName, FILE_GAME_MANIFEST) == 0)
				{
					GAME_MANIFEST manifest;
					sprintf(path, DIR_ROOT DIR_GAMES "%s/%s", find_data_file.cFileName, game_files.cFileName);
					
					if(file_size(path) != sizeof(GAME_MANIFEST))
					{
						sprintf(get_menu_item(list_addr, item_count)->menu_text.text, get_str(STR_CORRUPTED_DATA));
						get_menu_item(list_addr, item_count)->action = corrupted_game_error;
						item_count++;
					}
					else
					{
						sprintf(get_menu_item(list_addr, item_count)->menu_text.text, "%s", find_data_file.cFileName);
						//get_menu_item(list_addr, item_count)->action = corrupted_game_error;
						item_count++;
					}
					break;
				}
			}
			while(FindNextFileA(game_files_handler, &game_files) != 0);
			
			FindClose(game_files_handler);
		}
	}
	while(FindNextFileA(file_handler, &find_data_file) != 0);
	
	FindClose(file_handler);
	
	return item_count;
}

uint8_t get_projects_list(RAM_PTR list_addr)
{
	
}


#elif defined(__ANDROID__)
	#error "Android version for file system is not implemented yet."
#else
	#error "Unsupported platform"
#endif