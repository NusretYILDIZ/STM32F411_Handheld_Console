#ifndef __game_engine_h
#define __game_engine_h

#include "./script/script_engine.h"
#include "./script/instructions.h"

#include "./objects/game_object.h"
#include "./objects/terrain.h"

#include "./ui/ui_element.h"

#include "./units/coordinate.h"

#include "./utils/keyboard.h"

#include "./graphics/graphics_2d.h"

#define NAMEOF(X) #X
#define DATA_TYPE_INIT(X) { #X, sizeof(X) }

#if defined(__arm__)
	#define GAME_PATH_LENGTH  17  // /GAMES/gamepath/  (max dirname length = 8)(plus null-terminator)
#elif defined(__WIN32__)
	#define GAME_PATH_LENGTH  25  // ./sdcard/GAMES/gamepath/
#else
	#error "Unsupported platform."
#endif

#define MAX_QUAD_COUNT  256

#if MAX_QUAD_COUNT > 256
	typedef uint16_t QUAD_INDEX;
#else
	typedef uint8_t QUAD_INDEX;
#endif

#define ATTR_USE_ENGINE  0x01
#define ATTR_3D_GAME     0x02

typedef struct s_GAME_2D_SETTINGS
{
	RAM_PTR sprites_addr;
} GAME_2D_SETTINGS;

typedef struct s_GAME_3D_SETTINGS
{
	RAM_PTR quad_buffer_addr;
	QUAD_INDEX quad_count;
	
	RAM_PTR lights_addr;
	uint8_t lights_count;
} GAME_3D_SETTINGS;

typedef union u_GAME_TYPE_SETTINGS
{
	GAME_2D_SETTINGS game_2d;
	GAME_3D_SETTINGS game_3d;
} GAME_TYPE_SETTINGS;

typedef struct s_ENGINE_SETTINGS
{
	char game_path[GAME_PATH_LENGTH];
	RAM_PTR free_memory_addr;
	RAM_PTR game_code_addr;
	RAM_PTR game_objects_addr;
	uint8_t attr;
	
	GAME_TYPE_SETTINGS game_type_settings;
} ENGINE_SETTINGS;

extern ENGINE_SETTINGS engine_settings;

extern uint32_t elapsed_time;
extern uint32_t delta_time;

void wait_frame_time(void);
void load_game(void *game);
uint8_t game_engine_loop(void);

#endif //__game_engine_h