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

#ifndef __coordinate_h
#define __coordinate_h

typedef struct s_Vector2
{
	float x, y;
} Vector2;

typedef struct s_Vector3
{
	float x, y, z;
} Vector3;

typedef struct s_Vector4
{
	float x, y, z, w;
} Vector4;


typedef struct s_Vector2Int8
{
	int8_t x, y;
} Vector2Int8;

typedef struct s_Vector3Int8
{
	int8_t x, y, z;
} Vector3Int8;

typedef struct s_Vector4Int8
{
	int8_t x, y, z, w;
} Vector4Int8;


typedef struct s_Vector2Int16
{
	int16_t x, y;
} Vector2Int16;

typedef struct s_Vector3Int16
{
	int16_t x, y, z;
} Vector3Int16;

typedef struct s_Vector4Int16
{
	int16_t x, y, z, w;
} Vector4Int16;


typedef struct s_Vector2Int32
{
	int32_t x, y;
} Vector2Int32;

typedef struct s_Vector3Int32
{
	int32_t x, y, z;
} Vector3Int32;

typedef struct s_Vector4Int32
{
	int32_t x, y, z, w;
} Vector4Int32;

#endif //__coordinate_h