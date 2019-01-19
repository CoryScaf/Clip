#ifndef CP_EVENTFUNCTIONS_H_
#define CP_EVENTFUNCTIONS_H_

#include "Event.h"

#ifdef __cplusplus
extern "C" {
#endif
// GetXCoord will retrieve the X position of events like MOVE, MOUSE_MOVE, etc
int CP_API cpGetXCoord( CPqword QWORD );
// GetYCoord will retrieve the Y position of events like MOVE, MOUSE_MOVE, etc
int CP_API cpGetYCoord( CPqword QWORD );

CPevent CP_API cpGetLastEvent();
void CP_API cpSetLastEvent( CPevent event );

#ifdef __cplusplus
}
#endif

#endif