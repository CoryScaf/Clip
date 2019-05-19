#include "pch.h"
#include "String.h"
#include <string.h>
#include <stdlib.h>
#include "CPCore/Logging/Console.h"

CPpstring cpCreateString( const char* str )
{
	CPpstring string = malloc( sizeof( CPstring ) );
	if( string == CP_NULL ) {
		CP_CORE_LOG_ERROR( "Failed to allocate CPstring: %s", str );
		return CP_NULL;
	}
	string->length = strlen( str );
	string->str = malloc( string->length+1 );
	if( string->str == CP_NULL ) {
		CP_CORE_LOG_ERROR( "Failed to allocate string in CPstring: %s", str );
		return CP_NULL;
	}
	memcpy( string->str, str, string->length+1 );
	return string;
}

void cpDeleteString( CPpstring str )
{
	free( str->str );
	free( str );
	str = CP_NULL;
}

char cpStrGetChar( CPpstring str, CPsize loc )
{
	if( loc > str->length ) {
		CP_CORE_LOG_WARNING( "cpStrGetChar param 2 ( loc ) can not be longer than the string length." );
		return 0;
	}
	return str->str[loc];
}

CPsize cpStrFind( CPpstring str, const char* find )
{
	CPsize flen = strlen( find );
	for( CPsize i = 0; i < str->length-flen+1; ++i ) {
		char* string = malloc( flen+1 );
		if( string ) {
			memcpy( string, str->str + i, flen );
			string[flen] = 0;
			if( !strcmp( string, find ) ) {
				return i;
			}
			free( string );
		}
		else {
			CP_CORE_LOG_WARNING( "char* 'string' failed malloc in cpStrFind" );
			return 0;
		}
	}
	return 0;
}

void cpStrAppend( CPpstring str, const char* cstr )
{
	char* ostr = str->str;
	CPsize olen = str->length;
	str->length += strlen( cstr );
	str->str = malloc( str->length+1 );
	memcpy( str->str, ostr, olen );
	memcpy( str->str + olen, cstr, str->length - olen + 1 );
	free( ostr );
}

void cpStrReplace( CPpstring str, const char* find, const char* replace )
{
	CPsize flen = strlen( find );
	CPsize rlen = strlen( replace );
	for( CPsize i = 0; i < str->length-flen; ++i ) {
		char* string = malloc( flen+1 );
		if( string ) {
			memcpy( string, str->str + i, flen );
			string[flen] = 0;
			if( !strcmp( string, find ) ) {
				char *nstr = malloc( str->length + ( rlen - flen )+1 );
				if( nstr ) {
					str->length += rlen - flen;
					nstr[str->length] = 0;
					memcpy( nstr, str->str, i );
					memcpy( nstr + i, replace, rlen );
					memcpy( nstr + i + rlen, str->str + i + flen, str->length - i - flen );
					free( str->str );
					str->str = nstr;
				}
				else {
					CP_CORE_LOG_WARNING( "char* 'nstr' failed malloc in cpStrReplace" );
					return;
				}
			}
			free( string );
		}
		else {
			CP_CORE_LOG_WARNING( "char* 'string' failed malloc in cpStrReplace" );
			return;
		}
	}
}

void cpStrInsert( CPpstring str, const char* ins, CPsize loc )
{
	if( loc > str->length ) {
		CP_CORE_LOG_WARNING( "cpStrInsert param 3 ( loc ) can not be larger than the string length." );
		return;
	}
	CPsize ilen = strlen( ins );
	char* nstr = malloc( str->length + ilen + 1 );
	if( nstr ) {
		memcpy( nstr, str->str, loc );
		memcpy( nstr + loc, ins, ilen );
		memcpy( nstr + loc + ilen, str->str + loc, str->length - loc );
		str->length += ilen;
		free( str->str );
		nstr[str->length] = 0;
		str->str = nstr;
	}
	else {
		CP_CORE_LOG_WARNING( "char* 'nstr' failed malloc in cpStrInsert" );
	}
}

CPpstring cpStrSubStr( CPpstring str, CPsize loc, CPsize count )
{
	if( loc > str->length ) {
		CP_CORE_LOG_WARNING( "cpStrSubStr param 2 ( loc ) can not be larger than the string length." );
		return CP_NULL;
	}
	if( loc+count > str->length ) count = str->length - loc;
	CPpstring substr = malloc( sizeof( CPstring ) );
	if( substr ) {
		substr->str = malloc( count+1 );
		if( substr->str ) {
			substr->length = count;
			memcpy( substr->str, str->str + loc, count );
			substr->str[count] = 0;
			return substr;
		}
		else {
			CP_CORE_LOG_WARNING( "CPstring->str 'substr' malloc failed in cpStrSubStr" );
			return CP_NULL;
		}
	}
	else {
		CP_CORE_LOG_WARNING( "CPstring 'substr' malloc failed in cpStrSubStr" );
		return CP_NULL;
	}
}
