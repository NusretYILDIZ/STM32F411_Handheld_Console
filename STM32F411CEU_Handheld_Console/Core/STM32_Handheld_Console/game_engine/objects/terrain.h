#ifndef __terrain_h
#define __terrain_h

#include "../units/coordinate.h"
#include "../script/script_engine.h"

/*typedef struct s_TerrainData
{
	
} TerrainData;*/

typedef enum e_TerrainSize
{
	TerrainSize_8x8,
	TerrainSize_16x16,
	TerrainSize_24x24,
	//TerrainSize_32x32,
} TerrainSize;

typedef struct s_Terrain
{
	Vector3 pos;
	TerrainSize size;
	float dst;  // Distance between two perpendicular point (in meters).
	RAM_PTR data_addr;
} Terrain;

#endif //__terrain_h