#include "./strings.h"
#include "./special_chars.h"

const char *strings_en[] = {
	"STM32 Handheld Gaming Console",
	"OK",
	"Back",
	"Cancel",
	"An error occurred while initialiazing SD card.\nMake sure the SD card is formatted with FAT32.",
	"<empty>",
	"-- Corrupted Data --",
	"Corrupted Game",
	"The game you want to play cannot be started.\n\nMake sure that the game is installed properly.",
	"Software has been closed because an\nerror occured.\n\nError code: ",
	
	// Keyboard
	"Enter character",
	"Space",
	"Done",
	
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
};

const char *strings_tr[] = {
	"STM32 Ta"STR_TR_s STR_TR_i"nabilir Oyun Konsolu",
	"Tamam",
	"Geri",
	STR_TR_I"ptal",
	"SD kart ba"STR_TR_s"lat"STR_TR_i"l"STR_TR_i"rken bir hata olu"STR_TR_s"tu.\nSD kart"STR_TR_i"n FAT32 ile bi"STR_TR_c"imlendirildi"STR_TR_g"inden emin olun.",
	"<bo"STR_TR_s">",
	"-- Bozulmu"STR_TR_s" Veri --",
	"Bozuk Oyun",
	"Oynamak istedi"STR_TR_g"iniz oyun ba"STR_TR_s"lat"STR_TR_i"lam"STR_TR_i"yor.\n\nOyunu do"STR_TR_g"ru bi"STR_TR_c"imde kurdu"STR_TR_g"unuzdan emin olun.",
	"Yaz"STR_TR_i"l"STR_TR_i"m kapat"STR_TR_i"ld"STR_TR_i" "STR_TR_c STR_TR_u"nk"STR_TR_u" bir hata meydana\ngeldi.\n\nHata kodu: ",
	
	// Keyboard
	"Karakter gir",
	"Bo"STR_TR_s"luk",
	"Tamamla",
	
	// System Menu
	"Oyunlar",
	"Edit"STR_TR_o"r",
	"Ayarlar",
	"Hakk"STR_TR_i"nda",
	"Dil: T"STR_TR_u"rk"STR_TR_c"e",
	
	// Games Menu
	"Oyunlar",
	"Oyunlar aran"STR_TR_i"yor...",
	"Ba"STR_TR_s"lat",
	"Sil",
	
	// Editor Menu
	"Yeni Proje Olu"STR_TR_s"tur",
	"Proje A"STR_TR_c,
};

const char *langs[] = {
	strings_en,
	strings_tr,
};

char **current_lang = strings_en;