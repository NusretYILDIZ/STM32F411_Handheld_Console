#include "./file_system.h"

#if defined(__arm__)
	#error "STM32 version of file system is not implemented yet."
#elif defined(__WIN32__)

#define DIR_ROOT  "./sdcard"

#include <stdio.h>
#include <windows.h>

uint8_t fs_init(void)
{
	//if(!dir_exists("sdcard")) return create_dir("sdcard");
	
	return 0;  // There is nothing to initialize.
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


uint8_t get_games_list(RAM_PTR index)
{
	WIN32_FIND_DATA find_data_file;
	HANDLE handle_file = 0;
	uint16_t game_count = 0;
	
	char path[256] = { '\0' };
	strcat(path, DIR_ROOT DIR_GAMES);
	
	handle_file = FindFirstFileA(path, &find_data_file);
	
	if(handle_file == INVALID_HANDLE_VALUE) return 0;
	else
	{
		do
		{
			if(!strcmp(find_data_file.cAlternateFileName, FILE_GAME_MANIFEST))
		} while();
	}
}

uint8_t get_projects_list(RAM_PTR index)
{
	
}


#elif defined(__ANDROID__)
	#error "Android version for file system is not implemented yet."
#else
	#error "Unsupported platform"
#endif