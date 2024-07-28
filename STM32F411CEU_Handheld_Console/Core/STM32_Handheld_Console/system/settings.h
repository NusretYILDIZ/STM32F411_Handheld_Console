#ifndef __settings_h
#define __settings_h

#include <stdint.h>

typedef struct s_SYSTEM_SETTINGS
{
	const char **current_lang;  // TODO: Don't make this an absolute pointer.
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