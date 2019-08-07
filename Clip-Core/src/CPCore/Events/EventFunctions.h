#ifndef CP_EVENTFUNCTIONS_H_
#define CP_EVENTFUNCTIONS_H_

#include "Event.h"

#ifdef __cplusplus
extern "C" {
#endif

int cpGetXCoord( CPqword QWORD );
int cpGetYCoord( CPqword QWORD );

int cpGetScrollDelta( CPdword DWORD );

CPevent cpGetLastEvent();
void cpSetLastEvent( CPevent event );

#ifdef __cplusplus
}
#endif

#endif