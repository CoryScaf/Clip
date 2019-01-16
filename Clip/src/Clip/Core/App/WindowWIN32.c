#include "Window.h"

#include "Clip/Core/Logging/Console.h"
#include "Clip/Core/Events/Event.h"
#include "Clip/Core/Events/EventFunctions.h"

#ifdef CL_PLATFORM_WINDOWS

LRESULT CALLBACK clWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

CLbyte wcInstances = 0;


CL_API _CLwindow* clCreateWindow( const wchar_t* title, unsigned int width, unsigned int height )
{
	_CLwindow* window = malloc( sizeof( _CLwindow ) );
	memset( window, 0, sizeof( _CLwindow ) );
	
	window->hInstance = GetModuleHandle( NULL );

	if( wcInstances == 0 )
	{
		WNDCLASSEX wc ={ 0 };
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.style = 0;
		wc.lpfnWndProc = clWndProc;
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
			CL_CORE_LOG_FATAL( "Failed Window Class Register : %u", GetLastError() );
			return NULL;
		}
	}
	wcInstances++;
	
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRectEx( &wr, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, FALSE, 0 );
	SetLastError( 0 );
	
	window->m_hWnd = CreateWindowEx( 0, L"CLIPENGINEWINDOW", title,
									 WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
									 CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL,
									 window->hInstance, NULL );

	if( !window->m_hWnd )
	{
		CL_CORE_LOG_FATAL( "Failed Window Creation : %u, %p", GetLastError(), window->m_hWnd );
		return NULL;
	}

	ShowWindow( window->m_hWnd, 5 );
	UpdateWindow( window->m_hWnd );

#if defined( CL_API_OPENGL )
	//create context
#elif defined( CL_API_VULKAN )

#elif defined( CL_API_DIRECTX )

#endif
	return window;
}

void CL_API clFreeWindow( _CLwindow* window )
{
	DestroyWindow( window->m_hWnd );
	free( window );
	wcInstances--;
	if( wcInstances == 0 )
	{
		UnregisterClass( L"CLIPENGINEWINDOW", GetModuleHandle( NULL ) );
	}
}

void CL_API clPollEvents()
{
	MSG msg;
	GetMessage( &msg, NULL, 0, 0 );
	TranslateMessage( &msg );
	DispatchMessage( &msg );
}

LRESULT CALLBACK clWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( uMsg == WM_CLOSE || uMsg == WM_QUIT )
	{
		_CLevent event;
		event.catigory = CL_EVENT_CAT_APPLICATION;
		event.type = CL_EVENT_WINDOW_CLOSE;
		event.arg0 = 0;
		event.arg1 = 0;
		clSetLastEvent( event );
	}
	else if( uMsg == WM_SIZE )
	{
		_CLevent event;
		event.catigory = CL_EVENT_CAT_APPLICATION;
		event.type = CL_EVENT_WINDOW_RESIZE;
		if( wParam == SIZE_MAXIMIZED )
			event.arg0 = 1;
		else if( wParam == SIZE_MINIMIZED )
			event.arg0 = 2;
		else if( wParam == SIZE_RESTORED )
			event.arg0 = 3;
		else event.arg0 = 0;
		event.arg1 = LOWORD( lParam );
		CLqword qword = HIWORD( lParam );
		event.arg1 |= qword << 4;
		clSetLastEvent( event );
	}
	else if( uMsg == WM_ACTIVATE )
	{
		_CLevent event;
		event.catigory = CL_EVENT_CAT_APPLICATION;
		
		if( LOWORD( wParam ) == WA_ACTIVE || LOWORD( wParam ) == WA_CLICKACTIVE )
		{
			event.type = CL_EVENT_WINDOW_FOCUS;
		}
		else
		{
			event.type = CL_EVENT_WINDOW_LOST_FOCUS;
		}
	}
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

#endif