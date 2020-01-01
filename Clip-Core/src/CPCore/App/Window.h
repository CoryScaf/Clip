#ifndef CP_WINDOW_H_
#define CP_WINDOW_H_

#include "CPCore/Core.h"
#if CP_PLATFORM & CP_PLATFORM_WINDOWS
#include <Windows.h>
#elif CP_PLATFORM & CP_PLATFORM_LINUX && CP_PLATFORM & CP_PROTOCOL_X11
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#endif
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCPwindow *CPpwindow;

// Callback functions
typedef void (*CPkeyDownCallback)( CPpwindow, CPqword );
typedef void (*CPkeyUpCallback)( CPpwindow, CPqword );
typedef void (*CPmouseMoveCallback)( CPpwindow, int, int );
typedef void (*CPmouseButtonDownCallback)( CPpwindow, CPdword );
typedef void (*CPmouseButtonUpCallback)( CPpwindow, CPdword );
typedef void (*CPwindowResizeCallback)( CPpwindow, CPdword, CPdword );
typedef void (*CPmouseScrollDownCallback)( CPpwindow );
typedef void (*CPmouseScrollUpCallback)( CPpwindow );
typedef void (*CPmouseCursorEnterCallback)( CPpwindow );
typedef void (*CPmouseCursorLeaveCallback)( CPpwindow );

// Window class on Windows
#if CP_PLATFORM & CP_PLATFORM_WINDOWS
typedef struct  tagCPwindowWINAPI
{
	HWND  hWnd;
	HINSTANCE hInstance;
} CPwindowWINAPI, *CPpwindowWINAPI;
typedef struct tagCP__core_window {
} CP__core_window, *CPp__core_window;
#else
typedef CPerrortype CPwindowWINAPI;
typedef CPerrortype *CPpwindowWINAPI;
#endif

// Window class on Linux
#if CP_PLATFORM & CP_PLATFORM_LINUX
#if CP_PLATFORM & CP_PROTOCOL_X11
// X11 version of window class
typedef struct tagCPwindowX11
{
	Window window;
	XContext context;
} CPwindowX11, *CPpwindowX11;
typedef CPerrortype CPwindowWAYLAND;
typedef CPerrortype *CPpwindowWAYLAND;

typedef struct tagCP__core_window {
	Display *display;
	Screen *screen;
	int screenID;
} CP__core_window, *CPp__core_window;
#elif CP_PLATFORM & CP_PROTOCOL_WAYLAND
// Wayland version of window class
typedef struct tagCPwindowWAYLAND
{

} CPwindowWAYLAND, *CPpwindowWAYLAND;
typedef CPerrortype CPwindowX11;
typedef CPerrortype *CPpwindowX11;
#else
// If it is not on linux set to error types
typedef CPerrortype CPwindowX11;
typedef CPerrortype *CPpwindowX11; 
typedef CPerrortype CPwindowWAYLAND;
typedef CPerrortype *CPpwindowWAYLAND;
#endif
#else
typedef CPerrortype CPwindowX11
typedef CPerrortype *CPpwindowX11
typedef CPerrortype CPwindowWAYLAND
typedef CPerrortype *CPpwindowWAYLAND
#endif

typedef struct tagCPwindow 
{
#if CP_PLATFORM & CP_PLATFORM_WINDOWS
	CPpwindowWINAPI window;
#elif CP_PLATFORM & CP_PLATFORM_LINUX && CP_PLATFORM & CP_PROTOCOL_X11
	CPpwindowX11 window;
#elif CP_PLATFORM & CP_PLATFORM_LINUX && CP_PLATFORM & CP_PROTOCOL_WAYLAND
	CPpwindowWAYLAND window;
#else
	CPerrortype *window;
#endif

	CPkeyDownCallback keyDownCallback;
	CPkeyUpCallback keyUpCallback;
	CPmouseMoveCallback mouseMoveCallback;
	CPmouseButtonDownCallback mouseButtonDownCallback;
	CPmouseButtonUpCallback mouseButtonUpCallback;
	CPmouseScrollDownCallback mouseScrollDownCallback;
	CPmouseScrollUpCallback mouseScrollUpCallback;
	CPmouseCursorEnterCallback mouseCursorEnterCallback;
	CPmouseCursorLeaveCallback mouseCursorLeaveCallback;
	CPwindowResizeCallback windowResizeCallback;

	void *parentClass;

	CPdword width, height;
	CPbool shouldClose;
} CPwindow;

CPp__core_window CP_CORE_WINDOW;

void cpInitWindowApps();
void cpUninitWindowApps();

CPpwindow cpCreateWindow( const char* title, unsigned int m_width, unsigned int m_height );
void cpFreeWindow( CPpwindow window );

void cpPollEvents( void );
void cpSetWindowShouldClose( CPpwindow window, CPbool close );
CPbool cpGetWindowShouldClose( CPpwindow window );

void cpSetKeyDownCallback( CPpwindow window, CPkeyDownCallback callback );
void cpSetKeyUpCallback( CPpwindow window, CPkeyUpCallback callback );
void cpSetMouseButtonDownCallback( CPpwindow window, CPmouseButtonDownCallback callback );
void cpSetMouseButtonUpCallback( CPpwindow window, CPmouseButtonUpCallback callback );
void cpSetMouseMoveCallback( CPpwindow window, CPmouseMoveCallback callback );
void cpSetMouseScrollDownCallback( CPpwindow window, CPmouseScrollDownCallback callback );
void cpSetMouseScrollUpCallback( CPpwindow window, CPmouseScrollUpCallback callback );
void cpSetMouseCursorEnterCallback( CPpwindow window, CPmouseCursorEnterCallback callback );
void cpSetMouseCursorLeaveCallback( CPpwindow window, CPmouseCursorLeaveCallback callback );
void cpSetWindowResizeCallback( CPpwindow window, CPwindowResizeCallback callback );
void cpAttachParentClass( CPpwindow window, void *parentClass );
void* cpGetParentClass( CPpwindow );


#ifdef __cplusplus
}
#endif

#endif
