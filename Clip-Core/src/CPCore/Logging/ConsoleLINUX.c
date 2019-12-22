#include "pch.h"
#include "Console.h"

#if CP_PLATFORM & CP_PLATFORM_LINUX
#include <stdio.h>
#include <time.h>

// Fixes bug where IDE thinks its not defined but it is
#ifndef CLOCK_REALTIME
#   define CLOCK_REALTIME 0
#endif

#ifndef CP_DIST

void cp__ConsoleLogTraceLINUX( CPpconsole console, const char* error, va_list list )
{
    CPpstring serror = cp__ParseError( error, list );
    cp__ParseAndPrintTag( console, serror->str, "Trace" );
    cpDeleteString( serror );
}

void cp__ConsoleLogInfoLINUX( CPpconsole console, const char* error, va_list list )
{
    printf( "\033[32m" );
    CPpstring serror = cp__ParseError( error, list );
    cp__ParseAndPrintTag( console, serror->str, "Info" );
    cpDeleteString( serror );
    printf( "\033[0m" );
}

void cp__ConsoleLogWarningLINUX( CPpconsole console, const char* error, va_list list )
{
    printf( "\033[33m" );
    CPpstring serror = cp__ParseError( error, list );
    cp__ParseAndPrintTag( console, serror->str, "Warning" );
    cpDeleteString( serror );
    printf( "\033[0m" );
}

void cp__ConsoleLogErrorLINUX( CPpconsole console, const char* error, va_list list )
{
    printf( "\033[35m" );
    CPpstring serror = cp__ParseError( error, list );
    cp__ParseAndPrintTag( console, serror->str, "Warning" );
    cpDeleteString( serror );
    printf( "\033[0m" );
}

void cp__ConsoleLogFatalLINUX( CPpconsole console, const char* error, va_list list )
{
    printf( "\033[31m" );
    CPpstring serror = cp__ParseError( error, list );
    cp__ParseAndPrintTag( console, serror->str, "Fatal" );
    cpDeleteString( serror );
    printf( "\033[0m" );
}

void cp__InitConsoleAppsLINUX()
{
    // Currently no use for InitConsoleAppsLINUX
}

void cp__UninitConsoleAppsLINUX()
{
    // Currently no use for UninitConsoleAppsLINUX
}

#else

void cp__ConsoleLogTraceLINUX( CPpconsole console, const char* error, va_list list ) {}
void cp__ConsoleLogInfoLINUX( CPpconsole console, const char* error, va_list list ) {}
void cp__ConsoleLogWarningLINUX( CPpconsole console, const char* error, va_list list ) {}
void cp__ConsoleLogErrorLINUX( CPpconsole console, const char* error, va_list list ) {}
void cp__ConsoleLogFatalLINUX( CPpconsole console, const char* error, va_list list ) {}
void cp__InitConsoleAppsLINUX() {}
void cp__UninitConsoleAppsLINUX() {}
#endif

CP__GetExTime cp__GetExTimeLINUX()
{
	struct timespec ts;
	clock_gettime( CLOCK_REALTIME, &ts );
	CP__GetExTime get;
	get.nanos = ts.tv_nsec;
	get.millis = ts.tv_nsec / 1000000;
	get.micros = ts.tv_nsec / 1000;
	return get;
}

#else

void cp__ConsoleLogTraceLINUX( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attempt to use ConsoleLogInfo LINUX on Windows or some other unsupported operating system" );
}

void cp__ConsoleLogInfoLINUX( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attempt to use ConsoleLogInfo LINUX on Windows or some other unsupported operating system" );
}

void cp__ConsoleLogWarningLINUX( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attempt to use ConsoleLogWarning LINUX on Windows or some other unsupported operating system" );
}

void cp__ConsoleLogErrorLINUX( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attempt to use ConsoleLogError LINUX on Windows or some other unsupported operating system" );
}

void cp__ConsoleLogFatalLINUX( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attempt to use ConsoleLogFatal LINUX on Windows or some other unsupported operating system" );
}

void cp__InitConsoleAppsLINUX()
{
	CP_CORE_LOG_WARNING( "Attempt to use InitConsoleApps LINUX on Windows or some other unsupported operating system" );
}

void cp__UninitConsoleAppsLINUX()
{
	CP_CORE_LOG_WARNING( "Attempt to use UninitConsoleApps LINUX on Windows or some other unsupported operating system" );
}

#endif
