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

#ifndef __keyboard_images_h
#define __keyboard_images_h

const unsigned char symbols_icon[] = {
	0x51, 0xC2, 0x00, 0x52, 0x25, 0x00, 0xF8, 0x22, 0x00, 0x50, 0x46, 0x80, 0xF8, 0x8B, 0x00, 0x50,
	0x09, 0x00, 0x50, 0x86, 0x80
};

const unsigned char letters_icon[] = {
	0x72, 0x00, 0x00, 0x8A, 0x00, 0x00, 0x8A, 0xC7, 0x00, 0xFB, 0x28, 0x80, 0x8A, 0x28, 0x00, 0x8A,
	0x28, 0x80, 0x8B, 0xC7, 0x00
};

const unsigned char backspace_icon[] = {
	0x1F, 0xF8, 0x20, 0x08, 0x42, 0x88, 0x81, 0x08, 0x42, 0x88, 0x20, 0x08, 0x1F, 0xF8
};

const unsigned char uppercase_disabled_icon[] = {
	0x08, 0x00, 0x14, 0x00, 0x22, 0x00, 0x41, 0x00, 0xE3, 0x80, 0x3E, 0x00, 0x00, 0x00, 0x3E, 0x00
};

const unsigned char uppercase_enabled_icon[] = {
	0x08, 0x00, 0x1C, 0x00, 0x3E, 0x00, 0x7F, 0x00, 0xFF, 0x80, 0x3E, 0x00, 0x00, 0x00, 0x3E, 0x00
};

const unsigned char enter_icon[] = {
	0x21, 0x61, 0xFF, 0x60, 0x20
};

#endif //__keyboard_images_h