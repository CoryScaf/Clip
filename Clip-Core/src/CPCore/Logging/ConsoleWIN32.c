#include "pch.h"
#include "Console.h"

#if CP_PLATFORM & CP_PLATFORM_WINDOWS
#include <Windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>


#ifndef CP_DIST

void cp__InitConsoleAppsWIN32()
{ 
	if( GetConsoleWindow() == NULL )
	{
		int hConHandle;
		CPqword lStdHandle;
		CONSOLE_SCREEN_BUFFER_INFO conInfo;
		FILE* fp;

		AllocConsole();

		GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &conInfo );
		conInfo.dwSize.Y = 500; // Max console lines
		SetConsoleScreenBufferSize( GetStdHandle( STD_OUTPUT_HANDLE ), conInfo.dwSize );

		lStdHandle = (CPqword)GetStdHandle( STD_OUTPUT_HANDLE );
		hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );

		fp = _fdopen( hConHandle, "w" );
		*stdout = *fp;
		setvbuf( stdout, NULL, _IONBF, 0 );

		lStdHandle = (CPqword)GetStdHandle( STD_INPUT_HANDLE );
		hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );

		fp = _fdopen( hConHandle, "r" );
		*stdin = *fp;
		setvbuf( stdout, NULL, _IONBF, 0 );

		lStdHandle = (CPqword)GetStdHandle( STD_ERROR_HANDLE );
		hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );

		fp = _fdopen( hConHandle, "w" );
		*stderr = *fp;
		setvbuf( stderr, NULL, _IONBF, 0 );
	}
}

void cp__UninitConsoleAppsWIN32()
{
    // Currently no use for UninitConsoleAppsWIN32
}

void cp__ConsoleLogTraceWIN32( CPpconsole console, const char* error, va_list list )
{
	// Trace uses standard color
	CPpstring serror = cp__ParseError( error, list );
	cp__ParseAndPrintTag( console, serror->str, "Trace" );
	cpDeleteString( serror );
}

void cp__ConsoleLogInfoWIN32( CPpconsole console, const char* error, va_list list )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	WORD savedAttribs;

	GetConsoleScreenBufferInfo( hConsole, &conInfo );
	savedAttribs = conInfo.wAttributes;

	SetConsoleTextAttribute( hConsole, 10 ); // green

	CPpstring serror = cp__ParseError( error, list );
	cp__ParseAndPrintTag( console, serror->str, "Info" );
	cpDeleteString( serror );

	SetConsoleTextAttribute( hConsole, savedAttribs );
}

void cp__ConsoleLogWarningWIN32( CPpconsole console, const char* error, va_list list )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	WORD savedAttribs;

	GetConsoleScreenBufferInfo( hConsole, &conInfo );
	savedAttribs = conInfo.wAttributes;

	SetConsoleTextAttribute( hConsole, 14 ); // yellow

	CPpstring serror = cp__ParseError( error, list );
	cp__ParseAndPrintTag( console, serror->str, "Warning" );
	cpDeleteString( serror );

	SetConsoleTextAttribute( hConsole, savedAttribs );
}

void cp__ConsoleLogErrorWIN32( CPpconsole console, const char* error, va_list list )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	WORD savedAttribs;

	GetConsoleScreenBufferInfo( hConsole, &conInfo );
	savedAttribs = conInfo.wAttributes;

	SetConsoleTextAttribute( hConsole, 13 ); // pink

	CPpstring serror = cp__ParseError( error, list );
	cp__ParseAndPrintTag( console, serror->str, "Error" );
	cpDeleteString( serror );

	SetConsoleTextAttribute( hConsole, savedAttribs );
}

void cp__ConsoleLogFatalWIN32( CPpconsole console, const char* error, va_list list )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	WORD savedAttribs;

	GetConsoleScreenBufferInfo( hConsole, &conInfo );
	savedAttribs = conInfo.wAttributes;

	SetConsoleTextAttribute( hConsole, 12 ); // red

	CPpstring serror = cp__ParseError( error, list );
	cp__ParseAndPrintTag( console, serror->str, "Fatal" );
	cpDeleteString( serror );

	SetConsoleTextAttribute( hConsole, savedAttribs );
}
#else
void cp__InitConsoleAppsWIN32() {}
void cp__UninitConsoleAppsWIN32() {}

void cp__ConsoleLogInfoWIN32( CPpconsole console, const char* error, va_list list ) {}

void cp__ConsoleLogWarningWIN32( CPpconsole console, const char* error, va_list list ) {}

void cp__ConsoleLogErrorWIN32( CPpconsole console, const char* error, va_list list ) {}

void cp__ConsoleLogFatalWIN32( CPpconsole console, const char* error, va_list list ) {}
#endif

LARGE_INTEGER getFILETIMEoffset()
{
	SYSTEMTIME s;
	FILETIME f;
	LARGE_INTEGER t;

	s.wYear = 1970;
	s.wMonth = 1;
	s.wDay = 1;
	s.wHour = 0;
	s.wMinute = 0;
	s.wSecond = 0;
	s.wMilliseconds = 0;
	SystemTimeToFileTime( &s, &f );
	t.QuadPart = f.dwHighDateTime;
	t.QuadPart <<= 32;
	t.QuadPart |= f.dwLowDateTime;
	return t;
}

CP__GetExTime cp__GetExTimeWIN32() 
{
	LARGE_INTEGER t;
	FILETIME f;
	double microseconds;
	static LARGE_INTEGER offset;
	static double frequencyToMicroseconds;
	static int initialized = 0;
	static BOOL usePerformanceCounter = 0;

	if( !initialized ) {
		LARGE_INTEGER performanceFrequency;
		initialized = 1;
		usePerformanceCounter = QueryPerformanceFrequency( &performanceFrequency );
		if( usePerformanceCounter ) {
			QueryPerformanceCounter( &offset );
			frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.0;
		}
		else {
			offset = getFILETIMEoffset();
			frequencyToMicroseconds = 10.0;
		}
	}
	if( usePerformanceCounter ) QueryPerformanceCounter( &t );
	else {
		GetSystemTimeAsFileTime( &f );
		t.QuadPart = f.dwHighDateTime;
		t.QuadPart <<= 32;
		t.QuadPart |= f.dwLowDateTime;
	}

	t.QuadPart -= offset.QuadPart;
	microseconds = (double)t.QuadPart / frequencyToMicroseconds;
	CP__GetExTime get;
	get.millis = (CPdword)( microseconds/100.0 );
	get.nanos = (CPqword)( microseconds*1000.0 );
	get.micros = (CPqword)microseconds;
	return get;
}

#else

void cp__InitConsoleAppsWIN32()
{
	CP_CORE_LOG_WARNING( "Attempt to use ConsoleLogInfo WIN32 on Linux or some other unsupported operating system" );
}

void cp__UninitConsoleAppsWIN32()
{
	CP_CORE_LOG_WARNING( "Attempt to use ConsoleLogInfo WIN32 on Linux or some other unsupported operating system" );
}

void cp__ConsoleLogTraceWIN32( CPpconsole console, const char* error, va_list list ) {
	CP_CORE_LOG_WARNING( "Attempt to use ConsoleLogTrace WIN32 on Linux or some other unsupported operating system" );
}

void cp__ConsoleLogInfoWIN32( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attepmt to use ConsoleLogInfo WIN32 on Linux or some other unsupported operating system" );
}

void cp__ConsoleLogWarningWIN32( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attempt to use ConsoleLogWarning WIN32 on Linux or some other unsupported operating system" );
}

void cp__ConsoleLogErrorWIN32( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attempt to use ConsoleLogError WIN32 on Linux or some other unsupported operating system" );
}

void cp__ConsoleLogFatalWIN32( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attempt to use ConsoleLogFatal WIN32 on Linux or some other unsupported operating system" );
}

#endif
