#ifndef CP_WINDOW_H_
#define CP_WINDOW_H_

#include "../Core.h"
#include "GraphicsContext.h"

#if defined( CP_PLATFORM_WINDOWS )

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct CP_API tagCPwindowWINAPI
{
	HWND  hWnd;
	HINSTANCE hInstance;
} CPwindow, CPwindowWINAPI;

CP_API CPwindow* cpCreateWindow( const wchar_t* title, unsigned int m_width, unsigned int m_height, CPgraphicsContext* context );
CP_API void cpFreeWindow( CPwindow* window );

CP_API void cpPollEvents();

#ifdef __cplusplus
}
#endif

#elif defined( CP_PLATFORM_LINUX )

#include <X11/Xlib>

typedef class tagCPwindow
{

} CPwindow;

#endif

#endif