#ifndef CP_WINDOW_H_
#define CP_WINDOW_H_

#include "../Core.h"

#if defined( CP_PLATFORM_WINDOWS )

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct CP_API tagCPwindow
{
	HWND  m_hWnd;
	HINSTANCE hInstance;
#ifdef CP_API_OPENGL
	HGLRC m_hGLRC;
#elif defined( CP_API_VULKAN )

#elif defined( CP_API_DIRECTX )

#endif
} CPwindow;

CP_API CPwindow* cpCreateWindow( const wchar_t* title, unsigned int m_width, unsigned int m_height );
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