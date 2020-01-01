#include "pch.h"
#include "Window.h"

#include "CPCore/Logging/Console.h"

#if CP_PLATFORM & CP_PLATFORM_LINUX && CP_PLATFORM & CP_PROTOCOL_WAYLAND
CPpwindow cpCreateWindow( const wchar_t* title, unsigned int width, unsigned int height ) 
{
   CP_CORE_LOG_ERROR( "Wayland is currently not supported" );
   return CP_NULL;
}

void cpFreeWindow( CPpwindow window ) {
}

void cpPollEvents() {
}

#endif
