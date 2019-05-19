#include "pch.h"
#include "Console.h"

#ifdef CP_PLATFORM_WINDOWS
#include <Windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>


#ifndef CP_DIST
/*
void cpParseAndPrintTag( CPpconsole console, const char* error, const char* errorType )
{
	CPsize lastTag = 0;
	CPbool TagType = CP_FALSE;
	CPpstring print = cpCreateString( "" );

	// initialize time variables
	time_t time_raw_format;
	struct tm ptime;
	char buffer[50];

	SYSTEMTIME st;
	GetSystemTime( &st );
	

	time( &time_raw_format );
	localtime_s( &ptime, &time_raw_format );

	for( CPsize i = 0; i < console->consoleTag->length; ++i ) {
		if( !TagType && cpStrGetChar( console->consoleTag, i ) == '%' ) {
			TagType = CP_TRUE;

			if( lastTag == 0 ) {
				cpDeleteString( print );
				print = cpStrSubStr( console->consoleTag, 0, i );
			}
			else {
				CPpstring substr = cpStrSubStr( console->consoleTag, lastTag, i - lastTag );
				cpStrAppend( print, substr->str );
				cpDeleteString( substr );
			}
			lastTag = i;
		}
		else if( TagType == CP_TRUE ) {
			switch( cpStrGetChar( console->consoleTag, i ) ) {
			case 'm':
				// month 1-12 ex: 3		
				strftime( buffer, 50, "%m", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'd':
				// day of month 1-31 ex: 27
				strftime( buffer, 50, "%d", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'y':
				// year 2 digits 00-99 ex: 19
				strftime( buffer, 50, "%y", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'Y':
				// year 4 digits 0000-9999 ex: 2019
				strftime( buffer, 50, "%Y", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'D':
				// date MM/DD/YY ex: 03/27/19
				strftime( buffer, 50, "%m/%d/%y", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'H':
				// hour 24 format ex: 14
				strftime( buffer, 50, "%H", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'h':
				// hour 12 format ex: 9
				strftime( buffer, 50, "%I", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'M':
				// Minutes 0-59 ex: 08
				strftime( buffer, 50, "%M", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'S':
				// Seconds 0-59 ex: 32
				strftime( buffer, 50, "%S", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'w':
				// abbreviated weekday name ex: Wed
				strftime( buffer, 50, "%w", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'W':
				// full weekday name ex: Wednesday
				strftime( buffer, 50, "%W", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'i':
				// Millisecond of current second 0-999 ex: 385
			{
				CPpstring str = cpWordToString( st.wMilliseconds );
				cpStrAppend( print, str->str );
				cpDeleteString( str );
				break;
			}
			case 'a':
				// AM/PM of time ex: AM
				strftime( buffer, 50, "%p", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'c':
				// full 12 hour clock HH:MM AM/PM ex: 9:14 PM
				strftime( buffer, 50, "%I:%M %p", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'C':
				// full 24 hour clock HH:MM ex 21:14
				strftime( buffer, 50, "%H:%M", &ptime );
				cpStrAppend( print, buffer );
				break;
			case 'n':
				// logger name
				cpStrAppend( print, console->consoleName->str );
				break;
			case 'Z':
				// default logger given
				strftime( buffer, 50, "[%H:%M:%S]-", &ptime );
				cpStrAppend( print, buffer );
				cpStrAppend( print, errorType );
				cpStrAppend( print, ":" );
				cpStrAppend( print, console->consoleName->str );
				cpStrAppend( print, ": " );
				cpStrAppend( print, error );
				break;
			case 'z':
				// default internal logger
			{
				strftime( buffer, 50, "[%H:%M:%S:", &ptime );
				cpStrAppend( print, buffer );
				CPpstring str = cpWordToString( st.wMilliseconds );
				cpStrAppend( print, str->str );
				cpStrAppend( print, "]-" );
				cpStrAppend( print, errorType );
				cpStrAppend( print, ":" );
				cpStrAppend( print, console->consoleName->str );
				cpStrAppend( print, ": " );
				cpStrAppend( print, error );
				cpDeleteString( str );
				break;
			}
			case 'e':
				// Error type
				cpStrAppend( print, errorType );
				break;
			case 'l':
				// actual log
				cpStrAppend( print, error );
				break;
			case '%':
				// print out % sign
				cpStrAppend( print, "%" );
				break;
			}

			TagType = CP_FALSE;
		}
	}

	puts( print->str );
	cpDeleteString( print );
}
*/
CP_API void cp__InitConsoleAppsWIN32()
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

CP_API void cp__UninitConsoleAppsWIN32()
{
    // Currently no use for UninitConsoleAppsWIN32
}

CP_API void cp__ConsoleLogTraceWIN32( CPpconsole console, const char* error, va_list list )
{
	// Trace uses standard color
	CPpstring serror = cp__ParseError( error, list );
	cp__ParseAndPrintTag( console, serror->str, "Trace" );
	cpDeleteString( serror );
}

CP_API void cp__ConsoleLogInfoWIN32( CPpconsole console, const char* error, va_list list )
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

CP_API void cp__ConsoleLogWarningWIN32( CPpconsole console, const char* error, va_list list )
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

CP_API void cp__ConsoleLogErrorWIN32( CPpconsole console, const char* error, va_list list )
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

CP_API void cp__ConsoleLogFatalWIN32( CPpconsole console, const char* error, va_list list )
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
CP_API void cp__InitConsoleAppsWIN32() {}
CP_API void cp__UninitConsoleAppsWIN32() {}

CP_API void cp__ConsoleLogInfoWIN32( CPpconsole console, const char* error, va_list list ) {}

CP_API void cp__ConsoleLogWarningWIN32( CPpconsole console, const char* error, va_list list ) {}

CP_API void cp__ConsoleLogErrorWIN32( CPpconsole console, const char* error, va_list list ) {}

CP_API void cp__ConsoleLogFatalWIN32( CPpconsole console, const char* error, va_list list ) {}
#endif

#else

CP_API void cp__InitConsoleAppsWIN32()
{
	CP_CORE_LOG_WARNING( "Attept to use ConsoleLogInfo WIN32 on Linux or some other unsupported operating system" );
}

CP_API void cp__UninitConsoleAppsWIN32()
{
	CP_CORE_LOG_WARNING( "Attept to use ConsoleLogInfo WIN32 on Linux or some other unsupported operating system" );
}

CP_API void cp__ConsoleLogInfoWIN32( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attept to use ConsoleLogInfo WIN32 on Linux or some other unsupported operating system" );
}

CP_API void cp__ConsoleLogWarningWIN32( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attept to use ConsoleLogWarning WIN32 on Linux or some other unsupported operating system" );
}

CP_API void cp__ConsoleLogErrorWIN32( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attept to use ConsoleLogError WIN32 on Linux or some other unsupported operating system" );
}

CP_API void cp__ConsoleLogFatalWIN32( CPpconsole console, const char* error, va_list list )
{
	CP_CORE_LOG_WARNING( "Attept to use ConsoleLogFatal WIN32 on Linux or some other unsupported operating system" );
}

#endif
