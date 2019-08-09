#ifndef CP_CONSOLE_H_
#define CP_CONSOLE_H_

#include <stdio.h>
#include "CPCore/Misc/Color.h"
#include "CPCore/Misc/String.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCPconsole
{
	CPpstring consoleName;
	CPpstring consoleTag;
} CPconsole, *CPpconsole;

typedef struct tagCP__GetExTime
{
	CPdword millis;
	CPqword micros;
	CPqword nanos;
} CP__GetExTime;

extern CPpconsole CP_CORE_CONSOLE;

void cpInitConsoleApps();
void cpUninitConsoleApps();

void cp__InitConsoleAppsWIN32();
void cp__UninitConsoleAppsWIN32();

void cp__InitConsoleAppsLINUX();
void cp__UninitConsoleAppsLINUX();

CP__GetExTime cp__GetExTimeWIN32();
CP__GetExTime cp__GetExTimeLINUX();

// Allocate console to the heap UNIVERSAL
CPpconsole cpCreateConsole( const char* name, const char* tag );
// Free console from the heap UNIVERSAL
void cpDeleteConsole( CPpconsole console );

void cp__ConsoleLogTraceWIN32( CPpconsole console, const char* error, va_list list );
void cp__ConsoleLogInfoWIN32( CPpconsole console, const char* error, va_list list );
void cp__ConsoleLogWarningWIN32( CPpconsole console, const char* error, va_list list );
void cp__ConsoleLogErrorWIN32( CPpconsole console, const char* error, va_list list );
void cp__ConsoleLogFatalWIN32( CPpconsole console, const char* error, va_list );

void cp__ConsoleLogTraceLINUX( CPpconsole console, const char* error, va_list list );	// IMPLIMENT THESE
void cp__ConsoleLogInfoLINUX( CPpconsole console, const char* error, va_list list );	
void cp__ConsoleLogWarningLINUX( CPpconsole console, const char* error, va_list list );
void cp__ConsoleLogErrorLINUX( CPpconsole console, const char* error, va_list list );
void cp__ConsoleLogFatalLINUX( CPpconsole console, const char* error, va_list list );

void cpConsoleLogTrace( CPpconsole console, const char* error, ... );
void cpConsoleLogInfo( CPpconsole console, const char* error, ... );
void cpConsoleLogWarning( CPpconsole console, const char* error, ... );
void cpConsoleLogError( CPpconsole console, const char* error, ... );
void cpConsoleLogFatal( CPpconsole console, const char* error, ... );

CPpstring cp__ParseError( const char* error, va_list list );
void cp__ParseAndPrintTag( CPpconsole console, const char* error, const char* errorType );

#ifdef CP_DIST
#	define CP_CORE_LOG_FATAL( ... )
#	define CP_CORE_LOG_ERROR( ... )
#	define CP_CORE_LOG_WARNING( ... )
#	define CP_CORE_LOG_INFO( ... )


#else
#	define CP_CORE_LOG_FATAL( ... ) cpConsoleLogFatal( CP_CORE_CONSOLE, __VA_ARGS__ )
#	define CP_CORE_LOG_ERROR( ... ) cpConsoleLogError( CP_CORE_CONSOLE, __VA_ARGS__ ) 
#	define CP_CORE_LOG_WARNING( ... ) cpConsoleLogWarning( CP_CORE_CONSOLE, __VA_ARGS__ )
#	define CP_CORE_LOG_INFO( ... ) cpConsoleLogInfo( CP_CORE_CONSOLE, __VA_ARGS__ )
#endif

#ifdef __cplusplus
}
#endif

#endif
