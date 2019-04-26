#include "pch.h"
#include "Console.h"

#ifdef CP_PLATFORM_LINUX
// THESE NEED IMPLIMENTATION
CP_API void cp__ConsoleLogTraceLINUX( CPpconsole console, const char* error, va_list list )
{

}

CP_API void cp__ConsoleLogInfoLINUX( CPpconsole console, const char* error, va_list list )
{

}

CP_API void cp__ConsoleLogWarningLINUX( CPpconsole console, const char* error, va_list list )
{

}

CP_API void cp__ConsoleLogErrorLINUX( CPpconsole console, const char* error, va_list list )
{

}

CP_API void cp__ConsoleLogFatalLINUX( CPpconsole console, const char* error, va_list )
{

}

CP_API void cp__InitConsoleAppsLINUX()
{

}

CP_API void cp__UninitConsoleAppsLINUX()
{

}

#else

CP_API void cp__ConsoleLogTraceLINUX( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attept to use ConsoleLogInfo LINUX on Windows or some other unsupported operating system" );
}

CP_API void cp__ConsoleLogInfoLINUX( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attept to use ConsoleLogInfo LINUX on Windows or some other unsupported operating system" );
}

CP_API void cp__ConsoleLogWarningLINUX( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attept to use ConsoleLogWarning LINUX on Windows or some other unsupported operating system" );
}

CP_API void cp__ConsoleLogErrorLINUX( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attept to use ConsoleLogError LINUX on Windows or some other unsupported operating system" );
}

CP_API void cp__ConsoleLogFatalLINUX( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attept to use ConsoleLogFatal LINUX on Windows or some other unsupported operating system" );
}

CP_API void cp__InitConsoleAppsLINUX()
{
	CP_CORE_LOG_WARNING( "Attept to use InitConsoleApps LINUX on Windows or some other unsupported operating system" );
}

CP_API void cp__UninitConsoleAppsLINUX()
{
	CP_CORE_LOG_WARNING( "Attept to use UninitConsoleApps LINUX on Windows or some other unsupported operating system" );
}

#endif