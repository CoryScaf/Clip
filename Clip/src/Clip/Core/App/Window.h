#ifndef _WINDOW_H_
#define _WINDOW_H_

#if defined( CL_PLATFORM_WINDOWS )

#include <Windows.h>

#include "../Core.h"

typedef struct CL_API _tagCLwindow
{
	HWND  m_hWnd;
	HINSTANCE hInstance;
#ifdef CL_API_OPENGL
	HGLRC m_hGLRC;
#elif defined( CL_API_VULKAN )

#elif defined( CL_API_DIRECTX )

#endif
} _CLwindow;

CL_API _CLwindow* clCreateWindow( const wchar_t* title, unsigned int m_width, unsigned int m_height );
CL_API void clFreeWindow( _CLwindow* window );

CL_API void clPollEvents();

#elif defined( CL_PLATFORM_LINUX )

#include <X11/Xlib>

class _CLwindow
{

};

#endif

#endif