#ifndef _EVENTFUNCTIONS_H_
#define _EVENTFUNCTIONS_H_

#include "Event.h"

int CL_API clGetXCoord( CLqword QWORD );
int CL_API clGetYCoord( CLqword QWORD );

_CLevent CL_API clGetLastEvent();
void CL_API clSetLastEvent( _CLevent event );

#endif