#ifndef __strings_h
#define __strings_h

#include "../settings.h"

typedef enum e_STRINGS
{
	STR_CONSOLE_TITLE,
	STR_OK,
	STR_BACK,
	STR_INIT_FS_ERROR,
	STR_EMPTY,
	STR_CORRUPTED,
	STR_GAME_CORRUPTED_TITLE,
	STR_GAME_CORRUPTED_MSG,
	
	// System Menu
	STR_GAMES,
	STR_EDITOR,
	STR_SETTINGS,
	STR_ABOUT,
	STR_LANGUAGE,
	
	// Games Menu
	STR_GAME_LIST_TITLE,
	STR_SEARCHING_FOR_GAMES,
	STR_START,
	STR_DELETE,
	
	// Editor Menu
	STR_CREATE_NEW_PROJECT,
	STR_OPEN_PROJECT,
} String;

//const char **current_lang;

#define get_str(str) (system_settings.current_lang[str])

#endif //__strings_h