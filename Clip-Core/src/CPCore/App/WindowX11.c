#include "pch.h"
#include "Window.h"

#include "CPCore/Logging/Console.h"

#if CP_PLATFORM & CP_PLATFORM_LINUX && CP_PLATFORM & CP_PROTOCOL_X11

void cpInitWindowApps() {
    CP_CORE_WINDOW = malloc( sizeof( CP__core_window ) );
    CP_CORE_WINDOW->display = XOpenDisplay( CP_NULL );
    if( !CP_CORE_WINDOW->display ) {
        CP_CORE_LOG_FATAL( "Failed to initialize X11 display" );
        free( CP_CORE_WINDOW );
        return;
    }
    CP_CORE_WINDOW->screen = DefaultScreenOfDisplay( CP_CORE_WINDOW->display );
    if( !CP_CORE_WINDOW->screen ) {
        CP_CORE_LOG_FATAL( "Failed to initialize X11 screen" );
        XCloseDisplay( CP_CORE_WINDOW->display );
        free( CP_CORE_WINDOW );
        return;
    }
    CP_CORE_WINDOW->screenID = DefaultScreen( CP_CORE_WINDOW->display );
}

void cpUninitWindowApps() {
    XFree( CP_CORE_WINDOW->screen );
    XCloseDisplay( CP_CORE_WINDOW->display );
    free( CP_CORE_WINDOW );
}

CPpwindow cpCreateWindow( const char* title, unsigned int width, unsigned int height ) 
{
    CPpwindow window = malloc( sizeof( CPwindow ) );
    CPpwindowX11 windowx = malloc( sizeof( CPwindowX11 ) );
    window->shouldClose = CP_FALSE;
    window->width = width;
    window->height = height;
    windowx->window = XCreateSimpleWindow( CP_CORE_WINDOW->display, RootWindowOfScreen( CP_CORE_WINDOW->screen ), 10, 10, height, width, 0,
                                          BlackPixel( CP_CORE_WINDOW->display, CP_CORE_WINDOW->screenID ), WhitePixel( CP_CORE_WINDOW->display, CP_CORE_WINDOW->screenID ) );
    XSelectInput( CP_CORE_WINDOW->display, windowx->window, KeyPressMask | KeyReleaseMask | KeymapStateMask |
                    PointerMotionMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask 
                    | ExposureMask );
    XStoreName( CP_CORE_WINDOW->display, windowx->window, title );
    XClearWindow( CP_CORE_WINDOW->display, windowx->window );
    XMapRaised( CP_CORE_WINDOW->display, windowx->window );
    windowx->context = 0; 
    window->window = windowx;
    if( XSaveContext( CP_CORE_WINDOW->display, windowx->window, windowx->context, (const char*)window ) ) {
        CP_CORE_LOG_ERROR( "Could not save context of window. ( Events will not work for this window )" );
    }
    window->keyDownCallback = CP_NULL;
    window->keyUpCallback = CP_NULL;
    window->mouseButtonDownCallback = CP_NULL;
    window->mouseButtonUpCallback = CP_NULL;
    window->mouseCursorEnterCallback = CP_NULL;
    window->mouseCursorLeaveCallback = CP_NULL;
    window->mouseMoveCallback = CP_NULL;
    window->mouseScrollDownCallback = CP_NULL;
    window->mouseScrollUpCallback = CP_NULL;
    window->windowResizeCallback = CP_NULL;
    return window;
}

void cpFreeWindow( CPpwindow window ) {
    XDeleteContext( CP_CORE_WINDOW->display, window->window->window, window->window->context );
    XDestroyWindow( CP_CORE_WINDOW->display, window->window->window ); 
    free( window->window );
    free( window );
}

CPpwindow cp__GetFocusedWindow( void ) {
    Window win;
    int tmp;
    XGetInputFocus( CP_CORE_WINDOW->display, &win, &tmp );
    XPointer window;
    if( XFindContext( CP_CORE_WINDOW->display, win, 0, &window ) ) {
        return CP_NULL;
    }
    CPpwindow ret = (CPpwindow)window;
    return ret;
}

void cpPollEvents( void ) {
    XEvent ev;
    XNextEvent( CP_CORE_WINDOW->display, &ev );
    CPpwindow window = cp__GetFocusedWindow();
    if( !window ) {
        return;
    }
    if( ev.type == KeymapNotify ) {
        XRefreshKeyboardMapping( &ev.xmapping );
    }
    else if( ev.type == KeyPress ) {
        KeySym keysym = 0;
        XLookupString( &ev.xkey, CP_NULL, 0, &keysym, CP_NULL );
        if( window->keyDownCallback ) {
            window->keyDownCallback( window, (CPqword)keysym );
        }
    }
    else if( ev.type == KeyRelease ) {
        KeySym keysym = 0;
        XLookupString( &ev.xkey, CP_NULL, 0, &keysym, CP_NULL );
        if( window->keyUpCallback ) {
            window->keyUpCallback( window, (CPqword)keysym );
        }
    }
    else if( ev.type == ButtonPress ) {
        if( ev.xbutton.button == 4 ) {
            if( window->mouseScrollUpCallback ) {
                window->mouseScrollUpCallback( window );
            }
        }
        else if( ev.xbutton.button == 5 ) {
            if( window->mouseScrollDownCallback ) {
                window->mouseScrollDownCallback( window );
            }
        }
        else {
            if( window->mouseButtonDownCallback ) {
                window->mouseButtonDownCallback( window, (CPdword)ev.xbutton.button );
            }
        }
    }
    else if( ev.type == ButtonRelease ) {
        if( window->mouseButtonUpCallback ) {
            window->mouseButtonUpCallback( window, (CPdword)ev.xbutton.button );
        }
    }
    else if( ev.type == MotionNotify ) {
        if( window->mouseMoveCallback ) {
            window->mouseMoveCallback( window, (CPdword)ev.xmotion.x, (CPdword)ev.xmotion.y );
        }
    }
    else if( ev.type == EnterNotify ) {
        if( window->mouseCursorEnterCallback ) {
            window->mouseCursorEnterCallback( window );
        }
    }
    else if( ev.type == LeaveNotify ) {
        if( window->mouseCursorLeaveCallback ) {
            window->mouseCursorLeaveCallback( window );
        }
    }
    else if( ev.type == Expose ) {
        XWindowAttributes attribs;
        XGetWindowAttributes( CP_CORE_WINDOW->display, window->window->window, &attribs );
        window->width = attribs.width;
        window->height = attribs.height;
        if( window->windowResizeCallback ) {
            window->windowResizeCallback( window, attribs.width, attribs.height );
        }
    }
}

#endif