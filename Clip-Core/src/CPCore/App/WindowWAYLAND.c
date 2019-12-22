#include "pch.h"
#include "Window.h"

#include "CPCore/Logging/Console.h"
#include "CPCore/Events/Event.h"
#include "CPCore/Events/EventFunctions.h"

#if defined( CP_PLATFORM_LINUX ) && defined( CP_PROTOCOL_WAYLAND )
/*
CPwindow* cpCreateWindow( const wchar_t* title, unsigned int width, unsigned int height ) 
{
   CP_CORE_LOG_INFO( "THIS IS A WAYLAND SESSION." );
}
*/
#endif
