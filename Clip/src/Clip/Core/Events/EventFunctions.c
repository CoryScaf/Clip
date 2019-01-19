#include "EventFunctions.h"

#include <string.h>
#include <stdlib.h>

CPevent* lastEvent = CP_NULL;

int CP_API cpGetXCoord( CPqword QWORD )
{
	QWORD &= 0xFFFFFFFFu;
	QWORD >>= 4u;
	return (int)QWORD;
}

int CP_API cpGetYCoord( CPqword QWORD )
{
	QWORD &= 0xFFFFFFFF00000000u;
	return (int)QWORD;
}

int CP_API cpGetScrollDelta( CPdword DWORD )
{
	return (int)DWORD;
}

CPevent cpGetLastEvent()
{
	CPevent event;
	if( lastEvent == CP_NULL )
	{
		event.catigory = CP_EVENT_CAT_NONE;
		event.type = CP_EVENT_NONE;
		event.arg0 = 0;
		event.arg1 = 0;
	}
	else
	{
		event.catigory = lastEvent->catigory;
		event.type = lastEvent->type;
		event.arg0 = lastEvent->arg0;
		event.arg1 = lastEvent->arg1;
	}
	return event;
}

void cpSetLastEvent( CPevent event )
{
	if( lastEvent != CP_NULL )
	{
		free( lastEvent );
		lastEvent = CP_NULL;
	}
	lastEvent = malloc( sizeof( CPevent ) );
	memset( lastEvent, 0, sizeof( lastEvent ) );
	lastEvent->catigory = event.catigory;
	lastEvent->type = event.type;
	lastEvent->arg0 = event.arg0;
	lastEvent->arg1 = event.arg1;
}