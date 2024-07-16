#ifndef __game_object_h
#define __game_object_h

#include "../units/coordinate.h"
#include "../script/script_engine.h"

typedef struct s_GameObject
{
	uint16_t id;
	Vector3 pos;
	Vector3 rot;
	RAM_PTR data_ptr;
} GameObject;

#endif //__game_object_h