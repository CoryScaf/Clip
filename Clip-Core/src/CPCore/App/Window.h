#ifndef CP_WINDOW_H_
#define CP_WINDOW_H_

#if CP_PLATFORM & CP_PLATFORM_WINDOWS
//#include <Windows.h>
#endif

#include <string.h>
#include "CPCore/Core.h"

#ifdef __cplusplus
extern "C" {
#endif

#if CP_PLATFORM & CP_PLATFORM_WINDOWS
typedef struct  tagCPwindowWINAPI
{
	//HWND  hWnd;
	//HINSTANCE hInstance;
} CPwindowWINAPI, *CPpwindowWINAPI;
#else
typedef CPerrortype CPwindowWINAPI;
typedef CPerrortype *CPpwindowWINAPI;
#endif

#if defined( CP_PLATFORM_LINUX )

#if defined( CP_PROTOCOL_X11 )

#else

#endif

#else

#endif

 //CPwindow* cpCreateWindow( const wchar_t* title, unsigned int m_width, unsigned int m_height );
 //void cpFreeWindow( CPwindow* window );

 //void cpPollEvents();

#ifdef __cplusplus
}
#endif

#endif
