#ifndef _EVENT_H_
#define _EVENT_H_

#include "Clip/Core/Core.h"

typedef unsigned long long CLqword;

typedef enum tagCLeventtype
{
	// no event
	CL_EVENT_NONE = 0,
	// window/application events
	CL_EVENT_WINDOW_CLOSE = 1,
	CL_EVENT_WINDOW_RESIZE = 2,
	CL_EVENT_WINDOW_FOCUS = 3,
	CL_EVENT_WINDOW_LOST_FOCUS = 4,
	CL_EVENT_WINDOW_MOVED = 5,
	// keyboard events
	CL_EVENT_KEY_PRESSED = 6,
	CL_EVENT_KEY_RELEASED = 7,
	// mouse events
	CL_EVENT_MOUSE_MOVED = 8,
	CL_EVENT_MOUSE_BUTTON_PRESSED = 9,
	CL_EVENT_MOUSE_BUTTON_RELEASED = 10,
	CL_EVENT_MOUSE_SCROLLED = 11,
	// completer application events
	CL_EVENT_APP_TICK = 12,
	CL_EVENT_APP_UPDATE = 13,
	CL_EVENT_APP_RENDER = 14
} CLeventtype;

typedef enum tagCLeventcategory
{
	CL_EVENT_CAT_NONE			= 0,
	CL_EVENT_CAT_KEYBOARD		= CL_BIT( 0 ),
	CL_EVENT_CAT_MOUSE			= CL_BIT( 1 ),
	CL_EVENT_CAT_APPLICATION	= CL_BIT( 2 ),
	CL_EVENT_CAT_INPUT			= CL_BIT( 3 )
} CLeventcategory;

typedef struct CL_API _tagCLevent
{
	CLeventtype type;
	CLbyte catigory;

	CLdword arg0;
	CLqword arg1;
} _CLevent;

#endif