#ifndef CLP_WINDOW_H_
#define CLP_WINDOW_H_

#if defined( CLP_PLATFORM_WINDOWS )

#include <Windows.h>

#include "../Core.h"

typedef struct CLP_API tagCLPwindow
{
	HWND  m_hWnd;
	HINSTANCE hInstance;
#ifdef CLP_API_OPENGL
	HGLRC m_hGLRC;
#elif defined( CLP_API_VULKAN )

#elif defined( CLP_API_DIRECTX )

#endif
} CLPwindow;

CLP_API CLPwindow* clpCreateWindow( const wchar_t* title, unsigned int m_width, unsigned int m_height );
CLP_API void clpFreeWindow( CLPwindow* window );

CLP_API void clpPollEvents();

#elif defined( CLP_PLATFORM_LINUX )

#include <X11/Xlib>

typedef class tagCLPwindow
{

} CLPwindow;

#endif

#endif