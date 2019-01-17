#ifndef CLP_EVENTFUNCTIONS_H_
#define CLP_EVENTFUNCTIONS_H_

#include "Event.h"

int CLP_API clpGetXCoord( CLPqword QWORD );
int CLP_API clpGetYCoord( CLPqword QWORD );

CLPevent CLP_API clpGetLastEvent();
void CLP_API clpSetLastEvent( CLPevent event );

#endif