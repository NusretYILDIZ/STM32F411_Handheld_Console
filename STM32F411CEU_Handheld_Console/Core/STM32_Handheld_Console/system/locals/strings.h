#ifndef __strings_h
#define __strings_h

#include "../system_settings.h"

typedef enum e_STRINGS
{
	STR_CONSOLE_TITLE,
	STR_BACK,
	STR_INIT_FS_ERROR,
	
	// System Menu
	STR_GAMES,
	STR_EDITOR,
	STR_SETTINGS,
	STR_ABOUT,
	STR_LANGUAGE,
	
	// Games Menu
	STR_START,
	STR_DELETE,
	
	// Editor Menu
	STR_CREATE_NEW_PROJECT,
	STR_OPEN_PROJECT,
} Strings;

//const char **current_lang;

#define get_str(str) (system_settings.current_lang[str])

#endif //__strings_h