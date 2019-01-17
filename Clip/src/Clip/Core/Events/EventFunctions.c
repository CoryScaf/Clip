#include "EventFunctions.h"

#include <string.h>
#include <stdlib.h>

CLPevent* lastEvent = CLP_NULL;

int CLP_API clpGetXCoord( CLPqword QWORD )
{
	QWORD &= 0xFFFFFFFFu;
	QWORD >>= 4u;
	return (int)QWORD;
}

int CLP_API clpGetYCoord( CLPqword QWORD )
{
	QWORD &= 0xFFFFFFFF00000000u;
	return (int)QWORD;
}

CLPevent clpGetLastEvent()
{
	CLPevent event;
	if( lastEvent == CLP_NULL )
	{
		event.catigory = CLP_EVENT_CAT_NONE;
		event.type = CLP_EVENT_NONE;
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

void clpSetLastEvent( CLPevent event )
{
	if( lastEvent != CLP_NULL )
	{
		free( lastEvent );
		lastEvent = CLP_NULL;
	}
	lastEvent = malloc( sizeof( CLPevent ) );
	memset( lastEvent, 0, sizeof( lastEvent ) );
	lastEvent->catigory = event.catigory;
	lastEvent->type = event.type;
	lastEvent->arg0 = event.arg0;
	lastEvent->arg1 = event.arg1;
}