/*
	MIT License

	Copyright (c) 2024 Nusret YILDIZ

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

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