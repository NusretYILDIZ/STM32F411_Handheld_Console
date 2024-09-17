#ifndef __strings_h
#define __strings_h

typedef enum
{
	STR_CONSOLE_TITLE,
	STR_OK,
	STR_BACK,
	STR_CANCEL,
	STR_INIT_FS_ERROR,
	STR_EMPTY,
	STR_CORRUPTED_DATA,
	STR_GAME_CORRUPTED_TITLE,
	STR_GAME_CORRUPTED_MSG,
	STR_KERNEL_PANIC_MSG,
	
	// Keyboard
	STR_ENTER_LETTER,
	STR_SPACE,
	STR_DONE,
	
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

typedef enum
{
	LANG_EN,
	LANG_TR,
} LANG;

extern const char *strings_en[];
extern const char *strings_tr[];

extern const char *langs[];

extern char **current_lang;
#define get_str(str) (current_lang[str])

#endif //__strings_h