#include "EventFunctions.h"

#include <string.h>
#include <stdlib.h>

_CLevent* lastEvent = CL_NULL;

int CL_API clGetXCoord( CLqword QWORD )
{
	QWORD &= 0xFFFFFFFFu;
	QWORD >>= 4u;
	return (int)QWORD;
}

int CL_API clGetYCoord( CLqword QWORD )
{
	QWORD &= 0xFFFFFFFF00000000u;
	return (int)QWORD;
}

_CLevent clGetLastEvent()
{
	_CLevent event;
	if( lastEvent == CL_NULL )
	{
		event.catigory = CL_EVENT_CAT_NONE;
		event.type = CL_EVENT_NONE;
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

void clSetLastEvent( _CLevent event )
{
	if( lastEvent != CL_NULL )
	{
		free( lastEvent );
		lastEvent = CL_NULL;
	}
	lastEvent = malloc( sizeof( _CLevent ) );
	memset( lastEvent, 0, sizeof( lastEvent ) );
	lastEvent->catigory = event.catigory;
	lastEvent->type = event.type;
	lastEvent->arg0 = event.arg0;
	lastEvent->arg1 = event.arg1;
}