#ifndef __game_engine_h
#define __game_engine_h

#include "./script/mem_access_def.h"
#include "./script/script_engine.h"
#include "./script/instructions.h"

#include "./objects/game_object.h"
#include "./objects/terrain.h"

#include "./ui/ui_element.h"

#include "./units/coordinate.h"

#define NAMEOF(X) #X
#define DATA_TYPE_INIT(X) { #X, sizeof(X) }

#endif //__game_engine_h