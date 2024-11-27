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

#ifndef __strings_h
#define __strings_h

typedef enum
{
	STR_CONSOLE_TITLE,
	STR_OK,
	STR_BACK,
	STR_CANCEL,
	STR_INIT_FS_ERROR,
	STR_EMPTY,
	STR_CORRUPTED_DATA,
	STR_GAME_CORRUPTED_TITLE,
	STR_GAME_CORRUPTED_MSG,
	STR_KERNEL_PANIC_MSG,
	
	// Keyboard
	STR_ENTER_LETTER,
	STR_SPACE,
	STR_DONE,
	
	// System Menu
	STR_GAMES,
	STR_EDITOR,
	STR_SETTINGS,
	STR_ABOUT,
	STR_LANGUAGE,
	
	// Games Menu
	STR_GAME_LIST_TITLE,
	STR_SEARCHING_FOR_GAMES,
	STR_START,
	STR_DELETE,
	
	// Editor Menu
	STR_CREATE_NEW_PROJECT,
	STR_OPEN_PROJECT,
} String;

typedef enum
{
	LANG_EN,
	LANG_TR,
} LANG;

extern const char *strings_en[];
extern const char *strings_tr[];

extern const char *langs[];

extern char **current_lang;
#define get_str(str) (current_lang[str])

#endif //__strings_h