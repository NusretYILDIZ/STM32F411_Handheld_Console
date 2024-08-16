#include "./strings.h"

const char *strings_en[] = {
	"STM32 Handheld Gaming Console",
	"OK",
	"Back",
	"An error occurred while initialiazing SD card.\nMake sure the SD card is formatted with FAT32.",
	"<empty>",
	"-- Corrupted Data --",
	"Corrupted Game",
	"The game you want to play cannot be started.\n\nMake sure that the game is installed properly.",
	"Software has been closed because an\nerror occured.\n\nError code: ",
	
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
	"STM32 Ta"TR_s TR_i"nabilir Oyun Konsolu",
	"Tamam",
	"Geri",
	"SD kart ba"TR_s"lat"TR_i"l"TR_i"rken bir hata olu"TR_s"tu.\nSD kart"TR_i"n FAT32 ile bi"TR_c"imlendirildi"TR_g"inden emin olun.",
	"<bo"TR_s">",
	"-- Bozulmu"TR_s" Veri --",
	"Bozuk Oyun",
	"Oynamak istedi"TR_g"iniz oyun ba"TR_s"lat"TR_i"lam"TR_i"yor.\n\nOyunu do"TR_g"ru bi"TR_c"imde kurdu"TR_g"unuzdan emin olun.",
	"Yaz"TR_i"l"TR_i"m kapat"TR_i"ld"TR_i" "TR_c TR_u"nk"TR_u" bir hata meydana\ngeldi.\n\nHata kodu: ",
	
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
};

const char *langs[] = {
	strings_en,
	strings_tr,
};

char **current_lang = strings_en;