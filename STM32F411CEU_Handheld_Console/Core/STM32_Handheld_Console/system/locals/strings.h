#ifndef __strings_h
#define __strings_h

//#include "./strings_en.h"
//#include "./strings_tr.h"

#include "./special_chars.h"

typedef enum e_STRINGS
{
	STR_CONSOLE_TITLE,
	STR_OK,
	STR_BACK,
	STR_INIT_FS_ERROR,
	STR_EMPTY,
	STR_CORRUPTED_DATA,
	STR_GAME_CORRUPTED_TITLE,
	STR_GAME_CORRUPTED_MSG,
	STR_KERNEL_PANIC_MSG,
	
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

extern const char *strings_en[]; /* = {
	"STM32 Handheld Gaming Console",
	"OK",
	"Back",
	"An error occurred while initialiazing SD card.\nMake sure the SD card is formatted with FAT32.",
	"<empty>",
	"-- Corrupted Data --",
	"Corrupted Game",
	"The game you want to play cannot be started.\n\nMake sure that the game is installed properly.",
	
	// System Menu
	"Games",
	"Editor",
	"Settings",
	"About",
	"Language: English",
	
	// Games Menu
	"Games",
	"Searching for games...",
	"Start",
	"Delete",
	
	// Editor Menu
	"Create New Project",
	"Open Project",
};*/

extern const char *strings_tr[]; /* = {
	"STM32 Ta"TR_s TR_i"nabilir Oyun Konsolu",
	"Tamam",
	"Geri",
	"SD kart ba"TR_s"lat"TR_i"l"TR_i"rken bir hata olu"TR_s"tu.\nSD kart"TR_i"n FAT32 ile bi"TR_c"imlendirildi"TR_g"inden emin olun.",
	"<bo"TR_s">",
	"-- Bozulmu"TR_s" Veri --",
	"Bozuk Oyun",
	"Oynamak istedi"TR_g"iniz oyun ba"TR_s"lat"TR_i"lam"TR_i"yor.\n\nOyunu do"TR_g"ru bi"TR_c"imde kurdu"TR_g"unuzdan emin olun.",
	
	// System Menu
	"Oyunlar",
	"Edit"TR_o"r",
	"Ayarlar",
	"Hakk"TR_i"nda",
	"Dil: T"TR_u"rk"TR_c"e",
	
	// Games Menu
	"Oyunlar",
	"Oyunlar aran"TR_i"yor...",
	"Ba"TR_s"lat",
	"Sil",
	
	// Editor Menu
	"Yeni Proje Olu"TR_s"tur",
	"Proje A"TR_c,
};*/

extern const char *langs[]; /* = {
	strings_en,
	strings_tr,
};*/

extern char **current_lang;
#define get_str(str) (current_lang[str])

//const char **current_lang;

//#define get_str(str) (system_settings.current_lang[str])

#endif //__strings_h