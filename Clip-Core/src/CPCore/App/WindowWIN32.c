#include "pch.h"
#include "Window.h"

#include "CPCore/Logging/Console.h"
#include "CPCore/Events/Event.h"
#include "CPCore/Events/EventFunctions.h"

#ifdef CP_API_VULKAN
#include <vulkan/vulkan.h>
#endif

#ifdef CP_PLATFORM_WINDOWS

LRESULT CALLBACK cpWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

CPbyte wcInstances = 0;


CPwindow* cpCreateWindow( const wchar_t* title, unsigned int width, unsigned int height )
{
	// Create new CPwindow* and zero it out
	CPwindow* window = malloc( sizeof( CPwindow ) );
	memset( window, 0, sizeof( CPwindow ) );
	
	// Get hInstance
	window->hInstance = GetModuleHandle( NULL );

	// If CLIPENGINEWINDOW WNDCLASSEX isn't made already then make and register it
	if( wcInstances == 0 )
	{
		WNDCLASSEX wc ={ 0 };
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.style = 0;
		wc.lpfnWndProc = cpWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = window->hInstance;
		wc.hIcon = NULL;
		wc.hCursor = NULL;
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = L"CLIPENGINEWINDOW";
		wc.hIconSm = NULL;

		SetLastError( 0 );
		if( !RegisterClassEx( &wc ) )
		{
			CP_CORE_LOG_FATAL( "Failed Window Class Register : %u", GetLastError() );
			return NULL;
		}
	}
	// Keep track of the CLIPENGINEWINDOW WNDCLASSEX instances needed
	wcInstances++;
	
	// This is to determine the window size including the system menu
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRectEx( &wr, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, FALSE, 0 );
	SetLastError( 0 );
	
	// Create the actual window
	window->hWnd = CreateWindowEx( 0, L"CLIPENGINEWINDOW", title,
									 WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
									 CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL,
									 window->hInstance, NULL );

	if( !window->hWnd )
	{
		CP_CORE_LOG_FATAL( "Failed Window Creation : %u, %p", GetLastError(), window->hWnd );
		return NULL;
	}

	// Show the window
	ShowWindow( window->hWnd, 5 );
	UpdateWindow( window->hWnd );

#if defined( CP_API_OPENGL )
	// create OpenGL context
#elif defined( CP_API_VULKAN )
	// create Vulkan surface
	
#elif defined( CP_API_DIRECTX )

#endif
	return window;
}

void cpFreeWindow( CPwindow* window )
{
	// destroy window and free CPwindow
	DestroyWindow( window->hWnd );
	free( window );
	// remove one CLIPENGINEWINDOW WNDCLASSEX instance
	wcInstances--;
	// if instances equal 0 then unregister the WNDCLASSEX
	if( wcInstances == 0 )
	{
		UnregisterClass( L"CLIPENGINEWINDOW", GetModuleHandle( NULL ) );
	}
}

void cpPollEvents()
{
	// Gather the different events that happen
	MSG msg;
	GetMessage( &msg, NULL, 0, 0 );
	TranslateMessage( &msg );
	DispatchMessage( &msg );
}

LRESULT CALLBACK cpWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( uMsg == WM_CLOSE || uMsg == WM_QUIT )
	{
		CP_CORE_LOG_ERROR( "The thing shoulda worked\n" );
		// Window Close Event
		CPevent event;
		event.catigory = CP_EVENT_CAT_APPLICATION;
		event.type = CP_EVENT_WINDOW_CLOSE;
		event.arg0 = 0;
		event.arg1 = 0;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_SIZE )
	{
		// Window Resize Event
		CPevent event;
		event.catigory = CP_EVENT_CAT_APPLICATION;
		event.type = CP_EVENT_WINDOW_RESIZE;
		if( wParam == SIZE_MAXIMIZED )
			event.arg0 = 1;
		else if( wParam == SIZE_MINIMIZED )
			event.arg0 = 2;
		else if( wParam == SIZE_RESTORED )
			event.arg0 = 3;
		else event.arg0 = 0;
		event.arg1 = LOWORD( lParam );
		CPqword qword = HIWORD( lParam );
		event.arg1 |= qword << 4;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_ACTIVATE )
	{
		// Window Focus / Lose Focus Event
		CPevent event;
		event.catigory = CP_EVENT_CAT_APPLICATION;

		if( LOWORD( wParam ) == WA_ACTIVE || LOWORD( wParam ) == WA_CLICKACTIVE )
		{
			event.type = CP_EVENT_WINDOW_FOCUS;
		}
		else
		{
			event.type = CP_EVENT_WINDOW_LOST_FOCUS;
		}
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_KEYDOWN )
	{
		// Input Key Pressed Event
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_KEYBOARD;
		event.type = CP_EVENT_KEY_PRESSED;
		event.arg0 = (CPdword)wParam;
		event.arg1 = 0;
		event.arg1 &= 0xFFFF & lParam;	// repeat bits
		CPqword high = lParam & 0x40000000;	// previous state bit
		high <<= 2;	// make it the highDWord;
		event.arg1 &= high;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_KEYUP )
	{
		// Input Key Released Event
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_KEYBOARD;
		event.type = CP_EVENT_KEY_RELEASED;
		event.arg0 = (CPdword)wParam;		// repeat bits
		event.arg1 = (CPqword)( lParam & 0x40000000 );		// previous state bit
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_MOVE )
	{
		// Window Moved Event
		CPevent event;
		event.catigory = CP_EVENT_CAT_APPLICATION;
		event.type = CP_EVENT_WINDOW_MOVED;
		event.arg0 = 0;
		event.arg1 = (CPqword)lParam;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_MOUSEMOVE )
	{
		// Input Mouse Moved Event
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_MOUSE;
		event.type = CP_EVENT_MOUSE_MOVED;
		event.arg0 = 0;
		event.arg1 = (CPqword)lParam;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_LBUTTONDOWN )
	{
		// Input Mouse Button Pressed Event ( Left Mouse )
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_MOUSE;
		event.type = CP_EVENT_MOUSE_BUTTON_PRESSED;
		event.arg0 = 0x02;
		event.arg1 = (CPqword)lParam;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_MBUTTONDOWN )
	{
		// Input Mouse Button Pressed Event ( Middle Mouse )
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_MOUSE;
		event.type = CP_EVENT_MOUSE_BUTTON_PRESSED;
		event.arg0 = 0x04;
		event.arg1 = (CPqword)lParam;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_RBUTTONDOWN )
	{
		// Input Mouse Button Pressed Event ( Right Mouse )
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_MOUSE;
		event.type = CP_EVENT_MOUSE_BUTTON_PRESSED;
		event.arg0 = 0x08;
		event.arg1 = (CPqword)lParam;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_XBUTTONDOWN )
	{
		// Input Mouse Button Pressed Event ( X Mouse )
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_MOUSE;
		event.type = CP_EVENT_MOUSE_BUTTON_PRESSED;
		if( HIWORD( wParam ) & 0x01 )
			event.arg0 = 0x10;
		else if( HIWORD( wParam ) & 0x02 )
			event.arg0 = 0x20;
		event.arg1 = (CPqword)lParam;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_LBUTTONUP )
	{
		// Input Mouse Button Released Event ( Left Mouse )
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_MOUSE;
		event.type = CP_EVENT_MOUSE_BUTTON_RELEASED;
		event.arg0 = 0x02;
		event.arg1 = (CPqword)lParam;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_MBUTTONUP )
	{
		// Input Mouse Button Released Event ( Middle Mouse )
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_MOUSE;
		event.type = CP_EVENT_MOUSE_BUTTON_RELEASED;
		event.arg0 = 0x04;
		event.arg1 = (CPqword)lParam;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_RBUTTONUP )
	{
		// Input Mouse Button Released Event ( Right Mouse )
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_MOUSE;
		event.type = CP_EVENT_MOUSE_BUTTON_RELEASED;
		event.arg0 = 0x08;
		event.arg1 = (CPqword)lParam;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_XBUTTONUP )
	{
		// Input Mouse Button Released Event ( X Mouse )
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_MOUSE;
		event.type = CP_EVENT_MOUSE_BUTTON_RELEASED;
		if( HIWORD( lParam ) & 0x01 )
			event.arg0 = 0x10;
		else if( HIWORD( lParam ) & 0x02 )
			event.arg0 = 0x20;
		event.arg1 = (CPqword)lParam;
		cpSetLastEvent( event );
	}
	else if( uMsg == WM_MOUSEWHEEL )
	{
		// Input Mouse Scrool Event
		CPevent event;
		event.catigory = CP_EVENT_CAT_INPUT | CP_EVENT_CAT_MOUSE;
		event.type = CP_EVENT_MOUSE_SCROLLED;
		event.arg0 = HIWORD( wParam );
		event.arg1 = (CPqword)lParam;
		cpSetLastEvent( event );
	}
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

#endif
