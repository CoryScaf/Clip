#ifndef CP_WINDOW_H_
#define CP_WINDOW_H_

#if defined( CP_PLATFORM_WINDOWS )

#include <Windows.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct  tagCPwindowWINAPI
{
	HWND  hWnd;
	HINSTANCE hInstance;
} CPwindow, CPwindowWINAPI;

 CPwindow* cpCreateWindow( const wchar_t* title, unsigned int m_width, unsigned int m_height );
 void cpFreeWindow( CPwindow* window );

 void cpPollEvents();

#ifdef __cplusplus
}
#endif

#elif defined( CP_PLATFORM_LINUX )


typedef struct tagCPwindow
{

} CPwindow;

#endif

#endif