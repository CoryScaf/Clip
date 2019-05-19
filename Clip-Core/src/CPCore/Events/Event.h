#ifndef CP_EVENT_H_
#define CP_EVENT_H_

#include "CPCore/Core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum tagCPeventtype
{
	// no event
	CP_EVENT_NONE = 0,
	// window/application events
	CP_EVENT_WINDOW_CLOSE = 1,
	CP_EVENT_WINDOW_RESIZE = 2,
	CP_EVENT_WINDOW_FOCUS = 3,
	CP_EVENT_WINDOW_LOST_FOCUS = 4,
	CP_EVENT_WINDOW_MOVED = 5,
	// keyboard events
	CP_EVENT_KEY_PRESSED = 6,
	CP_EVENT_KEY_RELEASED = 7,
	// mouse events
	CP_EVENT_MOUSE_MOVED = 8,
	CP_EVENT_MOUSE_BUTTON_PRESSED = 9,
	CP_EVENT_MOUSE_BUTTON_RELEASED = 10,
	CP_EVENT_MOUSE_SCROLLED = 11,
	// completer application events
	CP_EVENT_APP_TICK = 12,
	CP_EVENT_APP_UPDATE = 13,
	CP_EVENT_APP_RENDER = 14
} CPeventtype;

typedef enum tagCPeventcategory
{
	CP_EVENT_CAT_NONE			= 0,
	CP_EVENT_CAT_KEYBOARD		= CP_BIT( 0 ),
	CP_EVENT_CAT_MOUSE			= CP_BIT( 1 ),
	CP_EVENT_CAT_APPLICATION	= CP_BIT( 2 ),
	CP_EVENT_CAT_INPUT			= CP_BIT( 3 )
} CPeventcategory;

typedef struct CP_API tagCPevent
{
	CPeventtype type;
	CPbyte catigory;

	CPdword arg0;
	CPqword arg1;
} CPevent;

#ifdef __cplusplus
}
#endif

#endif
