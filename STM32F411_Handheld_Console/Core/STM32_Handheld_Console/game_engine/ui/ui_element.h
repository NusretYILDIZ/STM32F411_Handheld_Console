#ifndef __ui_element_h
#define __ui_element_h

typedef enum e_UIElementType
{
	UI_TEXT,
	UI_IMAGE,
	UI_RECT
} UIElementType;

typedef struct s_UIElement
{
	int16_t x, y, w, h;
	UIElementType type;
} UIElement;

#endif //__ui_element_h