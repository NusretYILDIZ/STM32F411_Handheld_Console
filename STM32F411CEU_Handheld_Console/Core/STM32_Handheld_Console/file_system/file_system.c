#include "./file_system.h"

#if defined(__arm__)

uint8_t fs_init(void)
{
	
}

void fs_deinit(void)
{
	
}

void fs_use_relpath(uint8_t enable)
{
	
}

uint8_t file_exists(const char *filename)
{
	
}

uint8_t dir_exists(const char *path)
{
	
}

uint8_t file_full_read(const char *filename, void *buffer)
{
	
}

uint8_t file_read(const char *filename, void *buffer, size_t offset, size_t size)
{
	
}

uint8_t file_append(const char *filename, void *data, size_t size)
{
	
}

uint8_t file_write(const char *filename, void *data, size_t offset, size_t size)
{
	
}

uint8_t file_rename(const char *old_name, const char *new_name)
{
	
}

uint32_t file_size(const char *filename)
{
	
}

uint8_t create_dir(const char *path)
{
	
}

uint8_t set_current_dir(const char *path)
{
	
}

uint8_t delete_file(const char *filepath)
{
	
}

uint8_t delete_dir(const char *path)
{
	
}

uint8_t format_disk(void)
{
	
}

uint8_t get_games_list(RAM_PTR index)
{
	
}

uint8_t get_projects_list(RAM_PTR index)
{
	
}


#elif defined(__WIN32__)

#include <stdio.h>
#include <windows.h>

#include "../system/settings.h"

uint8_t fs_init(void)
{
	if(!dir_exists("sdcard")) return create_dir("sdcard");
	
	return 1;  // There is nothing to initialize.
}

void fs_deinit(void)
{
	// There is nothing to deinitialize.
}

void fs_use_relpath(uint8_t enable)
{
	
}

uint8_t file_exists(const char *filename)
{
	if(!filename) return 0;
	
	FILE *file = fopen(filename, "rb");
	
	if(file)
	{
		fclose(file);
		return 1;
	}
	else return 0;
}

uint8_t dir_exists(const char *path)
{
	DWORD attrib = GetFileAttributesA(path);
	
	if(attrib == INVALID_FILE_ATTRIBUTES) return 0;
	if(attrib & FILE_ATTRIBUTE_DIRECTORY) return 1;
	
	return 0;
}

uint8_t file_full_read(const char *filename, void *buffer)
{
	if(/*!filename ||*/ !buffer) return 0;  // Cannot write to null pointer, abort.
	
	size_t file_size, read_size;
	FILE *file;
	
	// For details about file modes: https://stackoverflow.com/a/1466036
	file = fopen(filename, "rb");  // Read in binary mode.
	if(!file) return 0;  // File could not be opened.
	
	fseek(file, 0L, SEEK_END);
	file_size = ftell(file);
	rewind(file);
	
	read_size = fread(buffer, file_size, 1, file);
	if(read_size != file_size) return 0;  // Error during reading file.
	
	fclose(file);
	return 1;
}

uint8_t file_read(const char *filename, void *buffer, size_t offset, size_t size)
{
	if(/*!filename ||*/ !buffer) return 0;  // Cannot write to null pointer, abort.
	//if(size == 0) return 1;
	
	size_t read_size;
	FILE *file;
	
	// For details about file modes: https://stackoverflow.com/a/1466036
	file = fopen(filename, "rb");  // Read in binary mode.
	if(!file) return 0;  // File could not be opened.
	
	fseek(file, offset, SEEK_SET);
	
	read_size = fread(buffer, size, 1, file);
	if(read_size != size) return 0;  // Error during reading file.
	
	fclose(file);
	return 1;  // Success.
}

uint8_t file_append(const char *filename, void *data, size_t size)
{
	//if(!filename || !data) return 0;
	//if(size == 0) return 1;
	
	size_t write_size;
	FILE *file;
	
	// For details about file modes: https://stackoverflow.com/a/1466036
	file = fopen(filename, "ab");  // Append in binary mode.
	if(!file) return 0;  // File could not be opened.
	
	write_size = fwrite(data, size, 1, file);
	if(write_size != size) return 0;  // Error during writing to file.
	
	fclose(file);
	return 1;
}

uint8_t file_write(const char *filename, void *data, size_t offset, size_t size)
{
	//if(!filename || !data) return 0;
	//if(size == 0) return 1;
	
	size_t write_size;
	FILE *file;
	
	// For details about file modes: https://stackoverflow.com/a/1466036
	file = fopen(filename, "r+b");  // Read and write in binary mode.
	if(!file) return 0;  // File could not be opened.
	
	fseek(file, offset, SEEK_SET);
	
	write_size = fwrite(data, size, 1, file);
	if(write_size != size) return 0;  // Error during writing to file.
	
	fclose(file);
	return 1;
}

uint8_t file_rename(const char *old_name, const char *new_name)
{
	//if(!old_name || !new_name) return 0;  // Null check.
	
	return !rename(old_name, new_name);  // Standard rename() function returns 0 on success, but our system should return non-zero value on success.
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

uint8_t create_dir(const char *path)
{
	//if(!path) return 0;
	
	return CreateDirectory(path, NULL);  // Windows-specific function.
}

uint8_t set_current_dir(const char *path)
{
	
}

uint8_t delete_file(const char *filepath)
{
	//if(!filepath) return 0;
	
	return !remove(filepath);  // Standard remove() function returns 0 on success, but our system should return non-zero value on success.
}

uint8_t delete_dir(const char *path)
{
	//if(!path) return 0;
	
	return RemoveDirectory(path);  // Windows-specific function.
}

uint8_t format_disk()
{
	system("rd /q /s sdcard");
	system("md sdcard");
	
	return 1;
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
				if(strcmp(game_files.cFileName, ".") != 0 && strcmp(game_files.cFileName, "..") != 0 && 
					!(game_files.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
					strcmp(game_files.cFileName, FILE_GAME_MANIFEST) == 0)
				{
					GAME_MANIFEST manifest;
					sprintf(path, DIR_ROOT DIR_GAMES "%s/%s", find_data_file.cFileName, game_files.cFileName);
					//if(file_size())
					
					sprintf(get_menu_item(list_addr, item_count)->menu_text.text, "%s", find_data_file.cFileName);
					//get_menu_item(list_addr, item_count)->action = corrupted_game_error;
					item_count++;
					
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