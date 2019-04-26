#include "pch.h"
#include "Console.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Allocate the console to the heap
CP_API CPpconsole cpCreateConsole( const char* name, const char* tag, CPconsoleparsetype parseType )
{
	// get lengths of strings ( add one for null character at the end )
	CPsize tagSize = strlen( tag )+1;
	CPsize nameSize = strlen( name )+1;
	// allocate console to the heap with space for name and tag
	CPpconsole console = (CPconsole*)malloc( sizeof( CPconsole ) );
	if( console == CP_NULL )
	{
		if( CP_CORE_CONSOLE == CP_NULL )
		{
			printf_s( "--- FATAL --- FAILED TO ALLOCATE CONSOLE : ERROR LOGGING WILL NOT WORK" );
		}
		else
		{
			CP_CORE_LOG_ERROR( "Failed to allocate console: %s", name );
		}
		return CP_NULL;
	}
	
	// allocate strings in console
	console->consoleTag = cpCreateString( tag );
	console->consoleName = cpCreateString( name );
	if( console->consoleTag == CP_NULL || console->consoleName == CP_NULL )
	{
		if( CP_CORE_CONSOLE == CP_NULL )
		{
			printf_s( "--- FATAL --- FAILED TO ALLOCATE CONSOLE STRINGS : ERROR LOGGING WILL NOT WORK" );
		}
		else
		{
			CP_CORE_LOG_ERROR( "Failed to allocate console strings: %s", name );
		}
		return CP_NULL;
	}

	console->parseType = parseType;
	return console;
}

// Free the console from the heap
CP_API void cpDeleteConsole( CPpconsole console )
{
	cpDeleteString( console->consoleName );
	cpDeleteString( console->consoleTag );
	free( console );
}

// Initialize the console
CP_API void cpInitConsoleApps()
{
	CP_CORE_CONSOLE = cpCreateConsole( "ENGINE", "[%t:%e] %n: %l", CP_CONSOLE_PARSE_PRINTF_STYLE );
	if( CP_CORE_CONSOLE == CP_NULL ) printf_s( "CP_CORE_CONSOLE is null" );
#ifdef CP_PLATFORM_WINDOWS
	cp__InitConsoleAppsWIN32();
#elif defined( CP_PLATFORM_LINUX )
	cp__InitConsoleAppsLINUX();
#endif
}

// Uninitialize the console
CP_API void cpUninitConsoleApps()
{
	cpDeleteConsole( CP_CORE_CONSOLE );
#ifdef CP_PLATFORM_WINDOWS
	cp__UninitConsoleAppsWIN32();
#elif defined( CP_PLATFORM_LINUX )
	cp__UninitConsoleAppsLINUX();
#endif
}

// Log error to the console
CP_API void cpConsoleLogTrace( CPpconsole console, const char* error, ... )
{
	if( console->parseType == CP_CONSOLE_PARSE_BRACE_STYLE )
	{
		CPdword va_count = 0;
		va_list list;

		// determine argument count ( will cause errors if the amount of arguments given does not equil the amount of variables listed )
		CPdword errLen = (CPdword)strlen( error );
		for( CPdword i = 0; i < errLen; ++i )
		{
			if( error[i] == '%' ) {
				if( i+1 < errLen ) {
					char ip1 = error[i+1];
					if( ip1 == 'c' || ip1 == 'i' || ip1 == 'd' || ip1 == 'f' || ip1 == 's' || ip1 == 'l' || ip1 == 'u' || ip1 == 'b'
						|| ip1 == '-' || ip1 == '+' || ip1 == '.' || ( ip1 >= '0' && ip1 <= '9' ) ) {
						va_count++;
					}
				}
			}
		}

		va_start( list, va_count );
		// Call OS specific code needed
#ifdef CP_PLATFORM_WINDOWS
		cp__ConsoleLogTraceWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
		cp__ConsoleLogTraceLINUX( console, error, list );
#endif
		va_end( list );
	}
	else
	{
		va_list list;
		va_start( list, error );
#ifdef CP_PLATFORM_WINDOWS
		cp__ConsoleLogTraceWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
		cp__ConsoleLogTraceLINUX( console, error, list );
#endif
		va_end( list );
	}
}

CP_API void cpConsoleLogInfo( CPpconsole console, const char* error, ... )
{
	if( console->parseType == CP_CONSOLE_PARSE_BRACE_STYLE )
	{
		CPdword va_count = 0;
		va_list list;

		// determine argument count ( will cause errors if the amount of arguments given does not equil the amount of variables listed )
		CPdword errLen = (CPdword)strlen( error );
		for( CPdword i = 0; i < errLen; ++i )
		{
			if( error[i] == '%' ) va_count++;
		}

		va_start( list, va_count );
		// Call OS specific code needed
#ifdef CP_PLATFORM_WINDOWS
		cp__ConsoleLogInfoWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
		cp__ConsoleLogInfoLINUX( console, error, list );
#endif
		va_end( list );
	}
	else
	{
		va_list list;
		va_start( list, error );
#ifdef CP_PLATFORM_WINDOWS
		cp__ConsoleLogInfoWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
		cp__ConsoleLogInfoLINUX( console, error, list );
#endif
		va_end( list );
	}
}

CP_API void cpConsoleLogWarning( CPpconsole console, const char* error, ... )
{
	if( console->parseType == CP_CONSOLE_PARSE_BRACE_STYLE )
	{
		CPdword va_count = 0;
		va_list list;

		// determine argument count ( will cause errors if the amount of arguments given does not equil the amount of variables listed )
		CPdword errLen = (CPdword)strlen( error );
		for( CPdword i = 0; i < errLen; ++i )
		{
			if( error[i] == '%' ) va_count++;
		}

		va_start( list, va_count );
		// Call OS specific code needed
#ifdef CP_PLATFORM_WINDOWS
		cp__ConsoleLogWarningWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
		cp__ConsoleLogWarningLINUX( console, error, list );
#endif
		va_end( list );
	}
	else
	{
		va_list list;
		va_start( list, error );
#ifdef CP_PLATFORM_WINDOWS
		cp__ConsoleLogWarningWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
		cp__ConsoleLogWarningLINUX( console, error, list );
#endif
		va_end( list );
	}
}

CP_API void cpConsoleLogError( CPpconsole console, const char* error, ... )
{
	if( console->parseType == CP_CONSOLE_PARSE_BRACE_STYLE )
	{
		CPdword va_count = 0;
		va_list list;

		// determine argument count ( will cause errors if the amount of arguments given does not equil the amount of variables listed )
		CPdword errLen = (CPdword)strlen( error );
		for( CPdword i = 0; i < errLen; ++i )
		{
			if( error[i] == '%' ) va_count++;
		}

		va_start( list, va_count );
		// Call OS specific code needed
#ifdef CP_PLATFORM_WINDOWS
		cp__ConsoleLogErrorWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
		cp__ConsoleLogErrorLINUX( console, error, list );
#endif
		va_end( list );
	}
	else
	{
		va_list list;
		va_start( list, error );
#ifdef CP_PLATFORM_WINDOWS
		cp__ConsoleLogErrorWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
		cp__ConsoleLogErrorLINUX( console, error, list );
#endif
		va_end( list );
	}
}

CP_API void cpConsoleLogFatal( CPpconsole console, const char* error, ... )
{
	if( console->parseType == CP_CONSOLE_PARSE_BRACE_STYLE )
	{
		CPdword va_count = 0;
		va_list list;

		// determine argument count ( will cause errors if the amount of arguments given does not equil the amount of variables listed )
		CPdword errLen = (CPdword)strlen( error );
		for( CPdword i = 0; i < errLen; ++i )
		{
			if( error[i] == '%' ) va_count++;
		}

		va_start( list, va_count );
		// Call OS specific code needed
#ifdef CP_PLATFORM_WINDOWS
		cp__ConsoleLogFatalWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
		cp__ConsoleLogFatalLINUX( console, error, list );
#endif
		va_end( list );
	}
	else
	{
		va_list list;
		va_start( list, error );
#ifdef CP_PLATFORM_WINDOWS
		cp__ConsoleLogFatalWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
		cp__ConsoleLogFatalLINUX( console, error, list );
#endif
		va_end( list );
	}
}

CPpstring cp__ParseError( const char *error, va_list list )
{
	CPpstring string = cpCreateString( "" );
	CPpstring tmp_string = cpCreateString( "" );
	CPsize size = strlen( error );
	CPpstring serror = cpCreateString( error );
	CPsize lastTag = 0;
	CPbool tagType = CP_FALSE;
	CPbool continueTag = CP_FALSE;
	CPsize i;
	CPpstring end_tag_string = CP_NULL;
	CPbool num_space_end_string = CP_FALSE;
	CPbool check_for_sign = CP_FALSE;
	CPsize float_precision = 6;
	
	for( i = 0; i < size; ++i ) {
		if( !tagType && cpStrGetChar( serror, i ) == '%' ) {
			tagType = CP_TRUE;

			if( lastTag == 0 ) {
				cpDeleteString( string );
				string = cpStrSubStr( serror, 0, i );
			}
			else {
				CPpstring substr = cpStrSubStr( serror, lastTag, i - lastTag );
				cpStrAppend( string, substr->str );
				cpDeleteString( substr );
			}
		}
		else if( tagType == CP_TRUE ) {
			if( !continueTag )
				lastTag = i;
			else continueTag = CP_FALSE;
			char c = cpStrGetChar( serror, i );
			if( c == 'c' ) {
				lastTag++;
				if( i + 1 < size ) {
					char nc = cpStrGetChar( serror, i+1 );
					if( nc == 's' ) {
						lastTag++;
						char *val = va_arg( list, char * );
						cpStrAppend( tmp_string, val );
					}
					else if( nc == 'u' ) {
						lastTag++;
						CPbyte val = va_arg( list, CPbyte );
						CPpstring str = cpByteToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
					else if( nc == 'i' || nc == 'd' ) {
						lastTag++;
						char val = va_arg( list, char );
						CPpstring str = cpSignedByteToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
				}
				else {
					char val = va_arg( list, char );
					char str[2]={ val, '\0' };
					cpStrAppend( tmp_string, str );
				}
			}
			else if( c == 'i' || c == 'd' ) {
				lastTag++;
				int val = va_arg( list, int );
				CPpstring str = cpIntToString( val );
				cpStrAppend( tmp_string, str->str );
				cpDeleteString( str );
			}
			else if( c == 'f' ) {
				lastTag++;
				double val = va_arg( list, double );
				CPpstring str = cpFloatToString( (float)val, float_precision );
				cpStrAppend( tmp_string, str->str );
				cpDeleteString( str );
			}
			else if( c == 's' ) {
				lastTag++;
				if( i + 1 < size ) {
					char nc = cpStrGetChar( serror, i+1 );
					if( nc == 'u' ) {
						lastTag++;
						CPword val = va_arg( list, CPword );
						CPpstring str = cpWordToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
					else if( nc == 'i' || nc == 'd' ) {
						lastTag++;
						short val = va_arg( list, short );
						CPpstring str = cpShortToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
					else if( nc == 'c' ) {
						lastTag++;
						char *str = va_arg( list, char * );
						cpStrAppend( tmp_string, str );
					}
				}
				else {
					CPpstring str = va_arg( list, CPpstring );
					cpStrAppend( tmp_string, str->str );
				}
			}
			else if( c == 'l' ) {
				lastTag++;
				if( i + 1 < size ) {
					char nc = cpStrGetChar( serror, i+1 );
					if( nc == 'l' ) {
						lastTag++;
						if( i + 2 < size ) {
							char nnc = cpStrGetChar( serror, i+1 );
							if( nnc == 'u' ) {
								lastTag++;
								CPqword val = va_arg( list, CPqword );
								CPpstring str = cpQWordToString( val );
								cpStrAppend( tmp_string, str->str );
								cpDeleteString( str );
							}
							else if( nnc == 'f' ) {
								lastTag++;
								long double val = va_arg( list, long double );
								CPpstring str = cpLongDoubleToString( val, float_precision );
								cpStrAppend( tmp_string, str->str );
								cpDeleteString( str );
							}
							else if( nnc == 'i' || nnc == 'd' ) {
								lastTag++;
								long long val = va_arg( list, long long );
								CPpstring str = cpLongLongToString( val );
								cpStrAppend( tmp_string, str->str );
								cpDeleteString( str );
							}
						}
						else {
							lastTag++;
							long long val = va_arg( list, long long );
							CPpstring str = cpLongLongToString( val );
							cpStrAppend( tmp_string, str->str );
							cpDeleteString( str );
						}
					}
					else if( nc == 'f' ) {
						lastTag++;
						double val = va_arg( list, double );
						CPpstring str = cpDoubleToString( val, float_precision );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
					else if( nc == 'u' ) {
						lastTag++;
						CPqword val = va_arg( list, CPqword );
						CPpstring str = cpQWordToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
					else if( nc == 'i' || nc == 'd' ) {
						lastTag++;
						long long val = va_arg( list, long long );
						CPpstring str = cpLongLongToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
				}
				else {
					lastTag++;
					long long val = va_arg( list, long long );
					CPpstring str = cpLongLongToString( val );
					cpStrAppend( string, str->str );
					cpDeleteString( str );
				}
			}
			else if( c == 'u' ) {
				lastTag++;
				if( i + 1 < size ) {
					char nc = cpStrGetChar( serror, i+1 );
					if( nc == 'c' || nc == 'b' ) {
						lastTag++;
						CPbyte val = (CPbyte)va_arg( list, CPdword );
						CPpstring str = cpByteToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
					else if( nc == 's' ) {
						lastTag++;
						CPword val = (CPword)va_arg( list, CPdword );
						CPpstring str = cpWordToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
					else if( nc == 'i' || nc == 'd' ) {
						lastTag++;
						CPdword val = va_arg( list, CPdword );
						CPpstring str = cpDWordToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
					else if( nc == 'l' ) {
						lastTag++;
						if( i+2 < size ) {
							char nnc = cpStrGetChar( serror, i+2 );
							if( nnc == 'l' ) {
								lastTag++;
							}
						}
						CPqword val = va_arg( list, CPqword );
						CPpstring str = cpQWordToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
				}
			}
			else if( c == 'b' ) {
				lastTag++;
				CPbool val = (CPbool)va_arg( list, CPdword );
				if( val ) cpStrAppend( tmp_string, "true" );
				else cpStrAppend( tmp_string, "false" );
			}
			else if( c == '%' ) {
				lastTag++;
				cpStrAppend( tmp_string, "%" );
			}
			else if( c >= '0' && c <= '9' ) {
				lastTag++;
				if( c != '0' ) {
					CPsize val = (CPsize)c - ( CPsize )'0';
					for( CPsize j = 1; i+j < size; ++j ) {
						char nc = cpStrGetChar( serror, i+j );
						if( nc >= '0' && nc <= '9' ) {
							lastTag++;
							val *= 10;
							val += (CPsize)c - ( CPsize )'0';
						}
						else j = size-i+1;
					}
					continueTag = CP_TRUE;
					char *spc = malloc( val+1 );
					if( spc ) {
						memset( spc, ' ', val );
						if( !num_space_end_string )
							cpStrAppend( tmp_string, spc );
						else {
							end_tag_string = cpCreateString( spc );
							num_space_end_string = CP_FALSE;
						}
						free( spc );
					}
					else {
						CP_CORE_LOG_WARNING( "cp__ParseError char* failed malloc ( %%[NUMBER] in cpConsoleLog[ERROR_LEVEL] )." );
						return CP_NULL;
					}
				}
			}
			else if( c == '-' ) {
				lastTag++;
				num_space_end_string = CP_TRUE;
				continueTag = CP_TRUE;
			}
			else if( c == '+' ) {
				lastTag++;
				check_for_sign = CP_TRUE;
				continueTag = CP_TRUE;
			}
			else if( c == '.' ) {
				lastTag++;
				if( i+1 < size ) {
					lastTag++;
					char nnc = cpStrGetChar( serror, i+1 );
					if( nnc > '0' && nnc <= '9' ) {
						CPsize val = (CPsize)nnc - ( CPsize )'0';
						for( CPsize j = 2; i+j < size; ++j ) {
							char nc = cpStrGetChar( serror, i+j );
							if( nc >= '0' && nc <= '9' ) {
								lastTag++;
								val *= 10;
								val += (CPsize)c - ( CPsize )'0';
							}
							else j = size-i+1;
						}
						continueTag = CP_TRUE;
						float_precision = val;
					}
				}
				else {
					CP_CORE_LOG_WARNING( "cpConsoleLog[ERROR_LEVEL] %%. must be fallowed by number ( number can't start with 0 ) - %%.[NUMBER]" );
				}
			}
			else if( c == 'n' ) {
				lastTag++;
			}
			else {
				CP_CORE_LOG_WARNING( "cpConsoleLog[ERROR_LEVEL] no tag after %%." );
				return CP_NULL;
			}
			if( !continueTag ) {
				tagType = CP_FALSE;
				if( end_tag_string != CP_NULL ) {
					cpStrAppend( tmp_string, end_tag_string->str );
					cpDeleteString( end_tag_string );
					end_tag_string = CP_NULL;
				}
				if( check_for_sign ) {
					for( CPsize ss = 0; ss < tmp_string->length; ++ss ) {
						char ssc = cpStrGetChar( tmp_string, ss );
						if( ssc == '-' ) ss = tmp_string->length;
						else if( ssc >= '0' && ssc <= '9' ) {
							cpStrInsert( tmp_string, "+", ss );
							ss = tmp_string->length;
						}
					}
					check_for_sign = CP_FALSE;
				}
				cpStrAppend( string, tmp_string->str );
				cpDeleteString( tmp_string );
				tmp_string = cpCreateString( "" );
				float_precision = 6;
			}
			i = lastTag-1;
		}
	}
	if( lastTag < i ) {
		CPpstring substr = cpStrSubStr( serror, lastTag, i - lastTag );
		cpStrAppend( string, substr->str );
		cpDeleteString( substr );
	}
	cpDeleteString( serror );
	return string;
}