#ifndef CLP_EVENT_H_
#define CLP_EVENT_H_

#include "Clip/Core/Core.h"

typedef enum tagCLPeventtype
{
	// no event
	CLP_EVENT_NONE = 0,
	// window/application events
	CLP_EVENT_WINDOW_CLOSE = 1,
	CLP_EVENT_WINDOW_RESIZE = 2,
	CLP_EVENT_WINDOW_FOCUS = 3,
	CLP_EVENT_WINDOW_LOST_FOCUS = 4,
	CLP_EVENT_WINDOW_MOVED = 5,
	// keyboard events
	CLP_EVENT_KEY_PRESSED = 6,
	CLP_EVENT_KEY_RELEASED = 7,
	// mouse events
	CLP_EVENT_MOUSE_MOVED = 8,
	CLP_EVENT_MOUSE_BUTTON_PRESSED = 9,
	CLP_EVENT_MOUSE_BUTTON_RELEASED = 10,
	CLP_EVENT_MOUSE_SCROLLED = 11,
	// completer application events
	CLP_EVENT_APP_TICK = 12,
	CLP_EVENT_APP_UPDATE = 13,
	CLP_EVENT_APP_RENDER = 14
} CLPeventtype;

typedef enum tagCLPeventcategory
{
	CLP_EVENT_CAT_NONE			= 0,
	CLP_EVENT_CAT_KEYBOARD		= CLP_BIT( 0 ),
	CLP_EVENT_CAT_MOUSE			= CLP_BIT( 1 ),
	CLP_EVENT_CAT_APPLICATION	= CLP_BIT( 2 ),
	CLP_EVENT_CAT_INPUT			= CLP_BIT( 3 )
} CLPeventcategory;

typedef struct CLP_API tagCLPevent
{
	CLPeventtype type;
	CLPbyte catigory;

	CLPdword arg0;
	CLPqword arg1;
} CLPevent;

#endif