#include "pch.h"
#include "Console.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#ifdef CP_PLATFORM_LINUX
#define LOCALTIME( a, b ) localtime_r( b, a )
#define CPGETEXTIME() cp__GetExTimeLINUX()
#elif defined( CP_PLATFORM_WINDOWS )
#define LOCALTIME( a, b ) localtime_s( a, b )
#define CPGETEXTIME() cp__GetExTimeWIN32()
#else
#define LOCALTIME( a, b )
#define CPGETEXTIME()
#endif

CPpconsole CP_CORE_CONSOLE = CP_NULL;


// Allocate the console to the heap
CPpconsole cpCreateConsole( const char* name, const char* tag, CPconsoleparsetype parseType )
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
			printf( "--- FATAL --- FAILED TO ALLOCATE CONSOLE : ERROR LOGGING WILL NOT WORK" );
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
			printf( "--- FATAL --- FAILED TO ALLOCATE CONSOLE STRINGS : ERROR LOGGING WILL NOT WORK" );
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
void cpDeleteConsole( CPpconsole console )
{
	cpDeleteString( console->consoleName );
	cpDeleteString( console->consoleTag );
	free( console );
}

// Initialize the console
void cpInitConsoleApps()
{
	CP_CORE_CONSOLE = cpCreateConsole( "ENGINE", "%z", CP_CONSOLE_PARSE_PRINTF_STYLE );
	if( CP_CORE_CONSOLE == CP_NULL ) printf( "CP_CORE_CONSOLE is null" );
#ifdef CP_PLATFORM_WINDOWS
	cp__InitConsoleAppsWIN32();
#elif defined( CP_PLATFORM_LINUX )
	cp__InitConsoleAppsLINUX();
#endif
}

// Uninitialize the console
void cpUninitConsoleApps()
{
	cpDeleteConsole( CP_CORE_CONSOLE );
#ifdef CP_PLATFORM_WINDOWS
	cp__UninitConsoleAppsWIN32();
#elif defined( CP_PLATFORM_LINUX )
	cp__UninitConsoleAppsLINUX();
#endif
}

// Log error to the console
void cpConsoleLogTrace( CPpconsole console, const char* error, ... )
{
    /*
    CPdword va_count = 0;

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
    */
    va_list list;
    va_start( list, error );
    // Call OS specific code needed
#ifdef CP_PLATFORM_WINDOWS
    cp__ConsoleLogTraceWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
    cp__ConsoleLogTraceLINUX( console, error, list );
#endif
    va_end( list );
}

void cpConsoleLogInfo( CPpconsole console, const char* error, ... )
{
    /*
    CPdword va_count = 0;
    va_list list;

    // determine argument count ( will cause errors if the amount of arguments given does not equil the amount of variables listed )
    CPdword errLen = (CPdword)strlen( error );
    for( CPdword i = 0; i < errLen; ++i )
    {
        if( error[i] == '%' ) va_count++;
    }
    */
    va_list list;
    va_start( list, error );
    // Call OS specific code needed
#ifdef CP_PLATFORM_WINDOWS
    cp__ConsoleLogInfoWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
    cp__ConsoleLogInfoLINUX( console, error, list );
#endif
    va_end( list );
}

void cpConsoleLogWarning( CPpconsole console, const char* error, ... )
{
    /*
		CPdword va_count = 0;
		va_list list;

		// determine argument count ( will cause errors if the amount of arguments given does not equil the amount of variables listed )
		CPdword errLen = (CPdword)strlen( error );
		for( CPdword i = 0; i < errLen; ++i )
		{
			if( error[i] == '%' ) va_count++;
		}
    */
    va_list list;
    va_start( list, error );
    // Call OS specific code needed
#ifdef CP_PLATFORM_WINDOWS
    cp__ConsoleLogWarningWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
    cp__ConsoleLogWarningLINUX( console, error, list );
#endif
    va_end( list );
}

void cpConsoleLogError( CPpconsole console, const char* error, ... )
{
    /*
		CPdword va_count = 0;
		va_list list;

		// determine argument count ( will cause errors if the amount of arguments given does not equil the amount of variables listed )
		CPdword errLen = (CPdword)strlen( error );
		for( CPdword i = 0; i < errLen; ++i )
		{
			if( error[i] == '%' ) va_count++;
		}
    */
    va_list list;
    va_start( list, error );
    // Call OS specific code needed
#ifdef CP_PLATFORM_WINDOWS
    cp__ConsoleLogErrorWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
    cp__ConsoleLogErrorLINUX( console, error, list );
#endif
    va_end( list );
}

void cpConsoleLogFatal( CPpconsole console, const char* error, ... )
{
    /*
		CPdword va_count = 0;
		va_list list;

		// determine argument count ( will cause errors if the amount of arguments given does not equil the amount of variables listed )
		CPdword errLen = (CPdword)strlen( error );
		for( CPdword i = 0; i < errLen; ++i )
		{
			if( error[i] == '%' ) va_count++;
		}
    */
    va_list list;
    va_start( list, error );
    // Call OS specific code needed
#ifdef CP_PLATFORM_WINDOWS
    cp__ConsoleLogFatalWIN32( console, error, list );
#elif defined( CP_PLATFORM_LINUX )
    cp__ConsoleLogFatalLINUX( console, error, list );
#endif
    va_end( list );
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
						CPbyte val = (CPbyte)va_arg( list, int );
						CPpstring str = cpByteToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
					else if( nc == 'i' || nc == 'd' ) {
						lastTag++;
						char val = (char)va_arg( list, int );
						CPpstring str = cpSignedByteToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
				}
				else {
					char val = (char)va_arg( list, int );
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
						CPword val = (CPword)va_arg( list, int );
						CPpstring str = cpWordToString( val );
						cpStrAppend( tmp_string, str->str );
						cpDeleteString( str );
					}
					else if( nc == 'i' || nc == 'd' ) {
						lastTag++;
						short val = (short)va_arg( list, int );
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


void cp__ParseAndPrintTag( CPpconsole console, const char* error, const char* errorType )
{
	CPsize lastTag = 0;
	CPbool TagType = CP_FALSE;
	CPpstring print = cpCreateString( "" );

	// initialize time variables
	time_t time_raw_format;
	struct tm ptime;
	char buffer[50];

	CP__GetExTime spec = CPGETEXTIME();
	
	time( &time_raw_format );
	LOCALTIME( &ptime, &time_raw_format );

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
				CPpstring str = cpDWordToString( spec.millis );
				cpStrAppend( print, str->str );
				cpDeleteString( str );
				break;
			}
			case 'J':
				// Microsections of current second
			{
				CPpstring str = cpQWordToString( spec.micros );
				cpStrAppend( print, str->str );
				cpDeleteString( str );
				break;
			}
            case 'I':
                // Nanosecond of current second 0-999999 ex: 19999
            {
                CPpstring str = cpQWordToString( spec.nanos );
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
				strftime( buffer, 50, "[%H:%M:%S:", &ptime );
				cpStrAppend( print, buffer );
                CPpstring str = cpDWordToString( spec.millis );
                cpStrAppend( print, str->str );
                cpStrAppend( print, "]-" );
				cpStrAppend( print, errorType );
				cpStrAppend( print, ":" );
				cpStrAppend( print, console->consoleName->str );
				cpStrAppend( print, ": " );
				cpStrAppend( print, error );
                cpDeleteString( str );
				break;
			case 'z':
				// default internal logger
			{
				strftime( buffer, 50, "[%H:%M:%S:", &ptime );
				cpStrAppend( print, buffer );
				CPpstring nstr = cpQWordToString( spec.nanos );
				cpStrAppend( print, nstr->str );
                cpStrAppend( print, "]-" );
				cpStrAppend( print, errorType );
				cpStrAppend( print, ":" );
				cpStrAppend( print, console->consoleName->str );
				cpStrAppend( print, ": " );
				cpStrAppend( print, error );
                cpDeleteString( nstr );
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
