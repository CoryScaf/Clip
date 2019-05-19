#ifndef CP_EVENTFUNCTIONS_H_
#define CP_EVENTFUNCTIONS_H_

#include "Event.h"

#ifdef __cplusplus
extern "C" {
#endif

int CP_API cpGetXCoord( CPqword QWORD );
int CP_API cpGetYCoord( CPqword QWORD );

int CP_API cpGetScrollDelta( CPdword DWORD );

CPevent CP_API cpGetLastEvent();
void CP_API cpSetLastEvent( CPevent event );

#ifdef __cplusplus
}
#endif

#endif