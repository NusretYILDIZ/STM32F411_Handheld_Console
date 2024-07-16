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