#ifndef CP_CONSOLE_H_
#define CP_CONSOLE_H_

#include <stdio.h>
#include "CPCore/Misc/Color.h"
#include "CPCore/Misc/String.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum tagCPconsoleparsetype
{
	CP_CONSOLE_PARSE_PRINTF_STYLE,
	CP_CONSOLE_PARSE_BRACE_STYLE
} CPconsoleparsetype;

typedef struct CP_API tagCPconsole
{
	CPpstring consoleName;
	CPpstring consoleTag;
	CPconsoleparsetype parseType;
} CPconsole, *CPpconsole;

CPpconsole CP_CORE_CONSOLE;

CP_API void cpInitConsoleApps();
CP_API void cpUninitConsoleApps();

CP_API void cp__InitConsoleAppsWIN32();
CP_API void cp__UninitConsoleAppsWIN32();

CP_API void cp__InitConsoleAppsLINUX();
CP_API void cp__UninitConsoleAppsLINUX();

// Allocate console to the heap UNIVERSAL
CP_API CPpconsole cpCreateConsole( const char* name, const char* tag, CPconsoleparsetype parseType );
// Free console from the heap UNIVERSAL
CP_API void cpDeleteConsole( CPpconsole console );

CP_API void cp__ConsoleLogTraceWIN32( CPpconsole console, const char* error, va_list list );
CP_API void cp__ConsoleLogInfoWIN32( CPpconsole console, const char* error, va_list list );
CP_API void cp__ConsoleLogWarningWIN32( CPpconsole console, const char* error, va_list list );
CP_API void cp__ConsoleLogErrorWIN32( CPpconsole console, const char* error, va_list list );
CP_API void cp__ConsoleLogFatalWIN32( CPpconsole console, const char* error, va_list );

CP_API void cp__ConsoleLogTraceLINUX( CPpconsole console, const char* error, va_list list );	// IMPLIMENT THESE
CP_API void cp__ConsoleLogInfoLINUX( CPpconsole console, const char* error, va_list list );	
CP_API void cp__ConsoleLogWarningLINUX( CPpconsole console, const char* error, va_list list );
CP_API void cp__ConsoleLogErrorLINUX( CPpconsole console, const char* error, va_list list );
CP_API void cp__ConsoleLogFatalLINUX( CPpconsole console, const char* error, va_list list );

CP_API void cpConsoleLogTrace( CPpconsole console, const char* error, ... );
CP_API void cpConsoleLogInfo( CPpconsole console, const char* error, ... );
CP_API void cpConsoleLogWarning( CPpconsole console, const char* error, ... );
CP_API void cpConsoleLogError( CPpconsole console, const char* error, ... );
CP_API void cpConsoleLogFatal( CPpconsole console, const char* error, ... );

CP_API void cp__ConsoleLogTrace(CPpconsole console, const char* error, CPsize tags, ... );
CP_API void cp__ConsoleLogInfo( CPpconsole console, const char* error, CPsize tags, ... );
CP_API void cp__ConsoleLogWarning( CPpconsole console, const char* error, CPsize tags, ... );
CP_API void cp__ConsoleLogError( CPpconsole console, const char* error, CPsize tags, ... );
CP_API void cp__ConsoleLogFatal( CPpconsole console, const char* error, CPsize tags, ... );

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
