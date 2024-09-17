#ifndef __settings_h
#define __settings_h

#include <stdint.h>
#include "./locals/strings.h"

typedef struct
{
	uint8_t current_lang;
	uint8_t screen_brightness;
	uint8_t theme_color_primary;
	uint8_t theme_color_secondary;
	char username[32];
} SYSTEM_SETTINGS;

typedef struct
{
	char name[64];
	uint8_t version;
} GAME_MANIFEST;

extern SYSTEM_SETTINGS system_settings;

#endif //__settings_h