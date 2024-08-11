#ifndef __settings_h
#define __settings_h

#include <stdint.h>
#include "./locals/strings.h"

typedef struct s_SYSTEM_SETTINGS
{
	LANG current_lang;
	uint8_t screen_brightness;
	uint8_t theme_color;
	char username[32];
} SYSTEM_SETTINGS;

typedef struct s_GAME_MANIFEST
{
	char name[64];
	uint8_t version;
} GAME_MANIFEST;

extern SYSTEM_SETTINGS system_settings;

#endif //__settings_h