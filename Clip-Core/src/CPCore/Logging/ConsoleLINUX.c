#include "pch.h"
#include "Console.h"

#ifdef CP_PLATFORM_LINUX
#include <stdio.h>

#ifndef CP_DIST

CP_API void cp__ConsoleLogTraceLINUX( CPpconsole console, const char* error, va_list list )
{
    CPpstring serror = cp__ParseError( error, list );
    cp__ParseAndPrintTag( console, serror->str, "Trace" );
    cpDeleteString( serror );
}

CP_API void cp__ConsoleLogInfoLINUX( CPpconsole console, const char* error, va_list list )
{
    printf( "\033[0;32m" );
    CPpstring serror = cp__ParseError( error, list );
    cp__ParseAndPrintTag( console, serror->str, "Info" );
    cpDeleteString( serror );
    printf( "\033[0m" );
}

CP_API void cp__ConsoleLogWarningLINUX( CPpconsole console, const char* error, va_list list )
{
    printf( "\033[0;33m" );
    CPpstring serror = cp__ParseError( error, list );
    cp__ParseAndPrintTag( console, serror->str, "Warning" );
    cpDeleteString( serror );
    printf( "\033[0m" );
}

CP_API void cp__ConsoleLogErrorLINUX( CPpconsole console, const char* error, va_list list )
{
    printf( "\033[0;35m" );
    CPpstring serror = cp__ParseError( error, list );
    cp__ParseAndPrintTag( console, serror->str, "Warning" );
    cpDeleteString( serror );
    printf( "\033[0m" );
}

CP_API void cp__ConsoleLogFatalLINUX( CPpconsole console, const char* error, va_list list )
{
    printf( "\044[0;31m" );
    CPpstring serror = cp__ParseError( error, list );
    cp__ParseAndPrintTag( console, serror->str, "Fatal" );
    cpDeleteString( serror );
    printf( "\033[0m" );
}

CP_API void cp__InitConsoleAppsLINUX()
{
    // Currently no use for InitConsoleAppsLINUX
}

CP_API void cp__UninitConsoleAppsLINUX()
{
    // Currently no use for UninitConsoleAppsLINUX
}

#else

CP_API void cp__ConsoleLogTraceLINUX( CPpconsole console, const char* error, va_list list ) {}
CP_API void cp__ConsoleLogInfoLINUX( CPpconsole console, const char* error, va_list list ) {}
CP_API void cp__ConsoleLogWarningLINUX( CPpconsole console, const char* error, va_list list ) {}
CP_API void cp__ConsoleLogErrorLINUX( CPpconsole console, const char* error, va_list list ) {}
CP_API void cp__ConsoleLogFatalLINUX( CPpconsole console, const char* error, va_list list ) {}
CP_API void cp__InitConsoleAppsLINUX() {}
CP_API void cp__UninitConsoleAppsLINUX() {}
#endif

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
