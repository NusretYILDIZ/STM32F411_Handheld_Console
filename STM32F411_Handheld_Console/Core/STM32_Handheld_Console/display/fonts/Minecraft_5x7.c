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

#include "./Minecraft_5x7.h"

#define PROGMEM

const uint8_t Minecraft_5x7_Bitmaps[] PROGMEM = {
  0xFA, 0x00, 0xFA, 0x00, 0xB4, 0x00, 0x52, 0xBE, 0xAF, 0xA9, 0x40, 0x23, 
  0xE0, 0xE0, 0xF8, 0x80, 0x8C, 0x84, 0x44, 0x26, 0x20, 0x22, 0x88, 0xDB, 
  0x49, 0xA0, 0xC0, 0x2A, 0x48, 0x88, 0x00, 0x88, 0x92, 0xA0, 0x00, 0xAA, 
  0x80, 0x21, 0x3E, 0x42, 0x00, 0xC0, 0xF8, 0x00, 0x80, 0x08, 0x84, 0x44, 
  0x22, 0x00, 0x74, 0x67, 0x5C, 0xC5, 0xC0, 0x23, 0x08, 0x42, 0x13, 0xE0, 
  0x74, 0x42, 0x64, 0x47, 0xE0, 0x74, 0x42, 0x60, 0xC5, 0xC0, 0x19, 0x53, 
  0x1F, 0x84, 0x20, 0xFC, 0x3C, 0x10, 0xC5, 0xC0, 0x32, 0x21, 0xE8, 0xC5, 
  0xC0, 0xFC, 0x42, 0x22, 0x10, 0x80, 0x74, 0x62, 0xE8, 0xC5, 0xC0, 0x74, 
  0x62, 0xF0, 0x89, 0x80, 0x88, 0x00, 0x8C, 0x00, 0x12, 0x48, 0x42, 0x10, 
  0xF8, 0x01, 0xF0, 0x84, 0x21, 0x24, 0x80, 0x74, 0x42, 0x22, 0x00, 0x80, 
  0x7A, 0x1B, 0x69, 0xBE, 0x07, 0x80, 0x74, 0x7F, 0x18, 0xC6, 0x20, 0xF4, 
  0x7D, 0x18, 0xC7, 0xC0, 0x74, 0x61, 0x08, 0x45, 0xC0, 0xF4, 0x63, 0x18, 
  0xC7, 0xC0, 0xFC, 0x39, 0x08, 0x43, 0xE0, 0xFC, 0x39, 0x08, 0x42, 0x00, 
  0x7C, 0x27, 0x18, 0xC5, 0xC0, 0x8C, 0x7F, 0x18, 0xC6, 0x20, 0xE9, 0x24, 
  0xB8, 0x00, 0x08, 0x42, 0x10, 0xC5, 0xC0, 0x8C, 0xB9, 0x28, 0xC6, 0x20, 
  0x84, 0x21, 0x08, 0x43, 0xE0, 0x8E, 0xEB, 0x58, 0xC6, 0x20, 0x8E, 0x6B, 
  0x38, 0xC6, 0x20, 0x74, 0x63, 0x18, 0xC5, 0xC0, 0xF4, 0x7D, 0x08, 0x42, 
  0x00, 0x74, 0x63, 0x18, 0xC9, 0xA0, 0xF4, 0x7D, 0x18, 0xC6, 0x20, 0x7C, 
  0x1C, 0x10, 0xC5, 0xC0, 0xF9, 0x08, 0x42, 0x10, 0x80, 0x8C, 0x63, 0x18, 
  0xC5, 0xC0, 0x8C, 0x63, 0x15, 0x28, 0x80, 0x8C, 0x63, 0x1A, 0xEE, 0x20, 
  0x8A, 0x88, 0xA8, 0xC6, 0x20, 0x8A, 0x88, 0x42, 0x10, 0x80, 0xF8, 0x44, 
  0x44, 0x43, 0xE0, 0xF2, 0x49, 0x38, 0x00, 0x82, 0x10, 0x41, 0x08, 0x20, 
  0xE4, 0x92, 0x78, 0x00, 0x22, 0xA2, 0x00, 0xF8, 0x00, 0x90, 0x70, 0x5F, 
  0x17, 0x80, 0x84, 0x2D, 0x98, 0xC7, 0xC0, 0x74, 0x61, 0x17, 0x00, 0x08, 
  0x5B, 0x38, 0xC5, 0xE0, 0x74, 0x7F, 0x07, 0x80, 0x34, 0xF4, 0x44, 0x40, 
  0x7C, 0x62, 0xF0, 0xF8, 0x00, 0x84, 0x2D, 0x98, 0xC6, 0x20, 0xBE, 0x00, 
  0x08, 0x02, 0x10, 0x86, 0x2E, 0x88, 0x9A, 0xCA, 0x90, 0xAA, 0xA4, 0x00, 
  0xD5, 0x6B, 0x18, 0x80, 0xF4, 0x63, 0x18, 0x80, 0x74, 0x63, 0x17, 0x00, 
  0xB6, 0x63, 0xE8, 0x40, 0x00, 0x6C, 0xE2, 0xF0, 0x84, 0x00, 0xB6, 0x61, 
  0x08, 0x00, 0x7C, 0x1C, 0x1F, 0x00, 0x4B, 0xA4, 0x88, 0x00, 0x8C, 0x63, 
  0x17, 0x80, 0x8C, 0x62, 0xA2, 0x00, 0x8C, 0x6B, 0x57, 0x80, 0x8A, 0x88, 
  0xA8, 0x80, 0x8C, 0x62, 0xF0, 0xF8, 0x00, 0xF8, 0x88, 0x8F, 0x80, 0x29, 
  0x44, 0x88, 0x00, 0xFE, 0x00, 0x89, 0x14, 0xA0, 0x00, 0x66, 0x60, 0x74, 
  0x61, 0x08, 0x45, 0xC2, 0x20, 0x00, 0x50, 0x1D, 0x18, 0xC6, 0x31, 0x70, 
  0x00, 0x43, 0xA4, 0x92, 0xE0, 0x7C, 0x1C, 0x10, 0xC5, 0xC2, 0x20, 0x00, 
  0x50, 0x23, 0x18, 0xC6, 0x31, 0x70, 0x00, 0x70, 0x1F, 0x09, 0xC6, 0x31, 
  0x70, 0x00, 0x74, 0x61, 0x17, 0x08, 0x80, 0x50, 0x1D, 0x18, 0xC5, 0xC0, 
  0xF8, 0x00, 0x7C, 0x1C, 0x1F, 0x08, 0x80, 0x50, 0x23, 0x18, 0xC5, 0xE0, 
  0x49, 0x80, 0xF8, 0xC5, 0xE1, 0xF0, 0x00, 0x3E, 0x3F, 0xBD, 0xFC, 0x7C, 
  0x1F, 0xFF, 0xFE, 0xFE, 0x3E, 0x00, 0x3E, 0x3F, 0xBD, 0xFE, 0x7F, 0x1F, 
  0x9F, 0xDE, 0xFE, 0x3E, 0x00, 0x3E, 0x3F, 0xBF, 0xFF, 0xFC, 0x1F, 0x1F, 
  0xDE, 0xFE, 0x3E, 0x00, 0x3E, 0x3F, 0xBD, 0xFC, 0xFC, 0x7F, 0x3F, 0xDE, 
  0xFE, 0x3E, 0x00, 0x3E, 0x3F, 0xBA, 0xFD, 0x7F, 0x7F, 0x5F, 0xAE, 0xFE, 
  0x3E, 0x00, 0x3E, 0x3F, 0xBA, 0xFD, 0x7F, 0x7F, 0xBF, 0xDE, 0xFE, 0x3E, 
  0x00, 0x3E, 0x3F, 0xBD, 0xFD, 0x7E, 0x3F, 0x5F, 0xAE, 0xFE, 0x3E, 0x00, 
  0x3E, 0x3F, 0xB9, 0xFD, 0x7E, 0x7F, 0x5F, 0x9E, 0xFE, 0x3E, 0x00, 0x3F, 
  0xFF, 0xE3, 0xFF, 0xFF, 0xB5, 0xB7, 0x47, 0xAA, 0x92, 0xFC, 0x55, 0x53, 
  0xEA, 0xAE, 0xBF, 0x5B, 0x74, 0x6F, 0xFF, 0xFE, 0x3F, 0xFF, 0xE0, 0x00, 
  0x3F, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xFB, 0x91, 0x71, 0x91, 0xEE, 0xEE, 
  0xEF, 0x7E, 0xCD, 0xCD, 0xEF, 0xEB, 0xBB, 0xBD, 0xF3, 0x11, 0x19, 0xBB, 
  0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0x80, 0x3F, 0xFF, 0xF8, 0xFF, 0xFF, 
  0xFB, 0x91, 0xB3, 0x1E, 0xF6, 0xAB, 0x7E, 0xEC, 0x4E, 0xFE, 0xDA, 0xAD, 
  0xF3, 0xB5, 0x5B, 0xBF, 0xFF, 0xFE, 0x3F, 0xFF, 0xF8, 0x00, 0x3F, 0x8F, 
  0xFB, 0x7B, 0xEE, 0x7D, 0xEF, 0xBD, 0xF1, 0x1B, 0xFE, 0x3F, 0x80, 0x3F, 
  0x8F, 0xFB, 0x71, 0xEF, 0xBD, 0xC7, 0xBB, 0xF1, 0x1B, 0xFE, 0x3F, 0x80, 
  0x3F, 0x8F, 0xFB, 0x3B, 0xEA, 0x7C, 0xEF, 0xAD, 0xF5, 0x1B, 0xFE, 0x3F, 
  0x80, 0x3F, 0x8F, 0xFB, 0x31, 0xEB, 0xBC, 0xC7, 0xAB, 0xF5, 0x1B, 0xFE, 
  0x3F, 0x80
};

const GFXglyph Minecraft_5x7_Glyphs[] PROGMEM = {
  {     0,   0,   0,   5,    0,  -11 },   // 0x20 ' '
  {     2,   1,   7,   2,    0,   -9 },   // 0x21 '!'
  {     4,   3,   2,   4,    0,   -9 },   // 0x22 '"'
  {     6,   5,   7,   6,    0,   -9 },   // 0x23 '#'
  {    11,   5,   7,   6,    0,   -9 },   // 0x24 '$'
  {    16,   5,   7,   6,    0,   -9 },   // 0x25 '%'
  {    21,   5,   7,   6,    0,   -9 },   // 0x26 '&'
  {    26,   1,   2,   2,    0,   -9 },   // 0x27 '''
  {    27,   3,   7,   4,    0,   -9 },   // 0x28 '('
  {    31,   3,   7,   4,    0,   -9 },   // 0x29 ')'
  {    35,   3,   3,   4,    0,   -9 },   // 0x2A '*'
  {    37,   5,   5,   6,    0,   -8 },   // 0x2B '+'
  {    41,   1,   2,   2,    0,   -3 },   // 0x2C ','
  {    42,   5,   1,   6,    0,   -6 },   // 0x2D '-'
  {    44,   1,   1,   2,    0,   -3 },   // 0x2E '.'
  {    45,   5,   7,   6,    0,   -9 },   // 0x2F '/'
  {    50,   5,   7,   6,    0,   -9 },   // 0x30 '0'
  {    55,   5,   7,   6,    0,   -9 },   // 0x31 '1'
  {    60,   5,   7,   6,    0,   -9 },   // 0x32 '2'
  {    65,   5,   7,   6,    0,   -9 },   // 0x33 '3'
  {    70,   5,   7,   6,    0,   -9 },   // 0x34 '4'
  {    75,   5,   7,   6,    0,   -9 },   // 0x35 '5'
  {    80,   5,   7,   6,    0,   -9 },   // 0x36 '6'
  {    85,   5,   7,   6,    0,   -9 },   // 0x37 '7'
  {    90,   5,   7,   6,    0,   -9 },   // 0x38 '8'
  {    95,   5,   7,   6,    0,   -9 },   // 0x39 '9'
  {   100,   1,   5,   2,    0,   -7 },   // 0x3A ':'
  {   102,   1,   6,   2,    0,   -7 },   // 0x3B ';'
  {   104,   4,   7,   5,    0,   -9 },   // 0x3C '<'
  {   108,   5,   4,   6,    0,   -7 },   // 0x3D '='
  {   111,   4,   7,   5,    0,   -9 },   // 0x3E '>'
  {   115,   5,   7,   6,    0,   -9 },   // 0x3F '?'
  {   120,   6,   7,   7,    0,   -8 },   // 0x40 '@'
  {   126,   5,   7,   6,    0,   -9 },   // 0x41 'A'
  {   131,   5,   7,   6,    0,   -9 },   // 0x42 'B'
  {   136,   5,   7,   6,    0,   -9 },   // 0x43 'C'
  {   141,   5,   7,   6,    0,   -9 },   // 0x44 'D'
  {   146,   5,   7,   6,    0,   -9 },   // 0x45 'E'
  {   151,   5,   7,   6,    0,   -9 },   // 0x46 'F'
  {   156,   5,   7,   6,    0,   -9 },   // 0x47 'G'
  {   161,   5,   7,   6,    0,   -9 },   // 0x48 'H'
  {   166,   3,   7,   4,    0,   -9 },   // 0x49 'I'
  {   170,   5,   7,   6,    0,   -9 },   // 0x4A 'J'
  {   175,   5,   7,   6,    0,   -9 },   // 0x4B 'K'
  {   180,   5,   7,   6,    0,   -9 },   // 0x4C 'L'
  {   185,   5,   7,   6,    0,   -9 },   // 0x4D 'M'
  {   190,   5,   7,   6,    0,   -9 },   // 0x4E 'N'
  {   195,   5,   7,   6,    0,   -9 },   // 0x4F 'O'
  {   200,   5,   7,   6,    0,   -9 },   // 0x50 'P'
  {   205,   5,   7,   6,    0,   -9 },   // 0x51 'Q'
  {   210,   5,   7,   6,    0,   -9 },   // 0x52 'R'
  {   215,   5,   7,   6,    0,   -9 },   // 0x53 'S'
  {   220,   5,   7,   6,    0,   -9 },   // 0x54 'T'
  {   225,   5,   7,   6,    0,   -9 },   // 0x55 'U'
  {   230,   5,   7,   6,    0,   -9 },   // 0x56 'V'
  {   235,   5,   7,   6,    0,   -9 },   // 0x57 'W'
  {   240,   5,   7,   6,    0,   -9 },   // 0x58 'X'
  {   245,   5,   7,   6,    0,   -9 },   // 0x59 'Y'
  {   250,   5,   7,   6,    0,   -9 },   // 0x5A 'Z'
  {   255,   3,   7,   4,    0,   -9 },   // 0x5B '['
  {   259,   5,   7,   6,    0,   -9 },   // 0x5C '\'
  {   264,   3,   7,   4,    0,   -9 },   // 0x5D ']'
  {   268,   5,   3,   6,    0,   -9 },   // 0x5E '^'
  {   271,   5,   1,   6,    0,   -2 },   // 0x5F '_'
  {   273,   2,   2,   3,    0,   -9 },   // 0x60 '`'
  {   274,   5,   5,   6,    0,   -7 },   // 0x61 'a'
  {   278,   5,   7,   6,    0,   -9 },   // 0x62 'b'
  {   283,   5,   5,   6,    0,   -7 },   // 0x63 'c'
  {   287,   5,   7,   6,    0,   -9 },   // 0x64 'd'
  {   292,   5,   5,   6,    0,   -7 },   // 0x65 'e'
  {   296,   4,   7,   5,    0,   -9 },   // 0x66 'f'
  {   300,   5,   6,   6,    0,   -7 },   // 0x67 'g'
  {   305,   5,   7,   6,    0,   -9 },   // 0x68 'h'
  {   310,   1,   7,   2,    0,   -9 },   // 0x69 'i'
  {   312,   5,   8,   6,    0,   -9 },   // 0x6A 'j'
  {   317,   4,   7,   5,    0,   -9 },   // 0x6B 'k'
  {   321,   2,   7,   3,    0,   -9 },   // 0x6C 'l'
  {   324,   5,   5,   6,    0,   -7 },   // 0x6D 'm'
  {   328,   5,   5,   6,    0,   -7 },   // 0x6E 'n'
  {   332,   5,   5,   6,    0,   -7 },   // 0x6F 'o'
  {   336,   5,   6,   6,    0,   -7 },   // 0x70 'p'
  {   341,   5,   6,   6,    0,   -7 },   // 0x71 'q'
  {   346,   5,   5,   6,    0,   -7 },   // 0x72 'r'
  {   350,   5,   5,   6,    0,   -7 },   // 0x73 's'
  {   354,   3,   7,   4,    0,   -9 },   // 0x74 't'
  {   358,   5,   5,   6,    0,   -7 },   // 0x75 'u'
  {   362,   5,   5,   6,    0,   -7 },   // 0x76 'v'
  {   366,   5,   5,   6,    0,   -7 },   // 0x77 'w'
  {   370,   5,   5,   6,    0,   -7 },   // 0x78 'x'
  {   374,   5,   6,   6,    0,   -7 },   // 0x79 'y'
  {   379,   5,   5,   6,    0,   -7 },   // 0x7A 'z'
  {   383,   3,   7,   4,    0,   -9 },   // 0x7B '{'
  {   387,   1,   7,   2,    0,   -9 },   // 0x7C '|'
  {   389,   3,   7,   4,    0,   -9 },   // 0x7D '}'
  {   393,   6,   2,   7,    0,   -9 },   // 0x7E '~'
  {     0,   0,   0,   0,    0,    0 },   // 0x7F 'non-printable'
  {   395,   5,   9,   6,    0,   -9 },   // 0x80 'non-printable'
  {   402,   5,   9,   6,    0,  -11 },   // 0x81 'non-printable'
  {   409,   3,   9,   4,    0,  -11 },   // 0x82 'non-printable'
  {   413,   5,   9,   6,    0,   -9 },   // 0x83 'non-printable'
  {   420,   5,   9,   6,    0,  -11 },   // 0x84 'non-printable'
  {   427,   5,   9,   6,    0,  -11 },   // 0x85 'non-printable'
  {   434,   5,   7,   6,    0,   -7 },   // 0x86 'non-printable'
  {   439,   5,   7,   6,    0,   -9 },   // 0x87 'non-printable'
  {   444,   1,   5,   2,    0,   -7 },   // 0x88 'non-printable'
  {   446,   5,   7,   6,    0,   -7 },   // 0x89 'non-printable'
  {   451,   5,   7,   6,    0,   -9 },   // 0x8A 'non-printable'
  {   456,   5,   9,   6,    0,  -10 },   // 0x8B 'non-printable'
  {   463,   9,   9,  11,    0,  -10 },   // 0x8C 'non-printable'
  {   474,   9,   9,  11,    0,  -10 },   // 0x8D 'non-printable'
  {   485,   9,   9,  11,    0,  -10 },   // 0x8E 'non-printable'
  {   496,   9,   9,  11,    0,  -10 },   // 0x8F 'non-printable'
  {   507,   9,   9,  11,    0,  -10 },   // 0x90 'non-printable'
  {   518,   9,   9,  11,    0,  -10 },   // 0x91 'non-printable'
  {   529,   9,   9,  11,    0,  -10 },   // 0x92 'non-printable'
  {   540,   9,   9,  11,    0,  -10 },   // 0x93 'non-printable'
  {   551,  21,   9,  23,    0,  -10 },   // 0x94 'non-printable'
  {   576,  27,   9,  29,    0,  -10 },   // 0x95 'non-printable'
  {   607,  23,   9,  25,    0,  -10 },   // 0x96 'non-printable'
  {   634,  11,   9,  13,    0,  -10 },   // 0x97 'non-printable'
  {   647,  11,   9,  13,    0,  -10 },   // 0x98 'non-printable'
  {   660,  11,   9,  13,    0,  -10 },   // 0x99 'non-printable'
  {   673,  11,   9,  13,    0,  -10 }    // 0x9A 'non-printable'
};

const GFXfont Minecraft_5x7 PROGMEM = {(uint8_t *) Minecraft_5x7_Bitmaps, (GFXglyph *)Minecraft_5x7_Glyphs, 0x20, 0x9A, 11};