#include "pch.h"
#include "MiscFunctions.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Clip/Core/Logging/Console.h"
#include <time.h>

CPpstring    cpIntToString( int x )
{
	CPpstring str = malloc( sizeof( CPstring ) );
	if( str ) {
		str->length = 0;
		int y = abs( x );
		for( int i = 1; y / i > 0; i *= 10 ) str->length++;
		if( x != y ) {
			str->length++;
			str->str = malloc( str->length+1 );
			if( str->str )
				str->str[0] = '-';
		}
		else
			str->str = malloc( str->length+1 );
		if( str->str ) {
			str->str[str->length] = 0;
			CPsize index = 0;
			while( y > 0 ) {
				str->str[str->length - index - 1] = ( y % 10 ) + '0';
				index++;
				y /= 10;
			}
			return str;
		}
		CP_CORE_LOG_WARNING( "CPstring->str malloc failed in IntToString." );
		free( str );
		return CP_NULL;
	}
	CP_CORE_LOG_WARNING( "CPstring malloc failed in IntToString." );
	return CP_NULL;
}

CPpstring    cpDWordToString( CPdword x )
{
	CPpstring str = malloc( sizeof( CPstring ) );
	if( str ) {
		str->length = 0;
		for( CPdword i = 1; x / i > 0; i *= 10 ) str->length++;
		str->str = malloc( str->length + 1 );
		if( str->str ) {
			str->str[str->length] = 0;
			for( CPsize index = 0; x > 0; x /= 10, index++ ) str->str[str->length - index - 1] = ( x % 10 ) + '0';
			return str;
		}
		CP_CORE_LOG_WARNING( "CPstring->str malloc failed in DWordToString." );
		free( str );
		return CP_NULL;
	}
	CP_CORE_LOG_WARNING( "CPstring malloc failed in DWordToString." );
	return CP_NULL;
} 

CPpstring    cpWordToString( CPword x )
{
	CPpstring str = malloc( sizeof( CPstring ) );
	if( str ) {
		str->length = 0;
		for( CPword i = 1; x / i > 0; i *= 10 ) str->length++;
		str->str = malloc( str->length + 1 );
		if( str->str ) {
			str->str[str->length] = 0;
			for( CPsize index = 0; x > 0; x /= 10, index++ ) str->str[str->length - index - 1] = ( x % 10 ) + '0';
			return str;
		}
		CP_CORE_LOG_WARNING( "CPstring->str malloc failed in WordToString." );
		free( str );
		return CP_NULL;
	}
	CP_CORE_LOG_WARNING( "CPstring malloc failed in WordToString." );
	return CP_NULL;
}

CPpstring    cpByteToString( CPbyte x )
{
	CPpstring str = malloc( sizeof( CPstring ) );
	if( str ) {
		str->length = 0;
		for( CPbyte i = 1; x / i > 0; i *= 10 ) str->length++;
		str->str = malloc( str->length + 1 );
		if( str->str ) {
			str->str[str->length] = 0;
			for( CPsize index = 0; x > 0; x /= 10, index++ ) str->str[str->length - index - 1] = ( x % 10 ) + '0';
			return str;
		}
		CP_CORE_LOG_WARNING( "CPstring->str malloc failed in ByteToString." );
		free( str );
		return CP_NULL;
	}
	CP_CORE_LOG_WARNING( "CPstirng malloc failed in ByteToString." );
	return CP_NULL;
}

CPpstring    cpQWordToString( CPqword x )
{
	CPpstring str = malloc( sizeof( CPstring ) );
	if( str ) {
		str->length = 0;
		for( CPqword i = 1; x / i > 0; i *= 10 ) str->length++;
		str->str = malloc( str->length + 1 );
		if( str->str ) {
			str->str[str->length] = 0;
			for( CPsize index = 0; x > 0; x /= 10, index++ ) str->str[str->length - index - 1] = ( x % 10 ) + '0';
			return str;
		}
		CP_CORE_LOG_WARNING( "CPstring->str malloc failed in QWordToString." );
		free( str );
		return CP_NULL;
	}
	CP_CORE_LOG_WARNING( "CPstring malloc failed in QWordToString." );
	return CP_NULL;
}

CPpstring    cpDoubleToString( double x, CPsize precision )
{
	int front = (int)x;
	int back = (int)( ( x - (double)front ) * pow( 10.0, (double)precision )  + 0.5 );
	while( back > 0 && back % 10 == 0 ) back /= 10;
	CPpstring str = malloc( sizeof( CPstring ) );
	if( str ) {
		str->length = 0;
		int af = abs( front );
		for( int i = 1; af / i > 0; i *= 10 ) str->length++;
		if( front != af ) {
			str->length++;
			str->str = malloc( str->length+1 );
			if( str->str )
				str->str[0] = '-';
		}
		else
			str->str = malloc( str->length+1 );
		if( str->str ) {
			str->str[str->length] = 0;
			CPsize index = 0;
			while( af > 0 ) {
				str->str[str->length - index - 1] = ( af % 10 ) + '0';
				index++;
				af /= 10;
			}

			CPpstring dec = malloc( sizeof( CPstring ) );
			if( dec ) {
				dec->length = 0;
				int ab = abs( back );
				for( int i = 1; ab / i > 0; i *= 10 ) dec->length++;
				dec->str = malloc( dec->length+1 );
				if( dec->str ) {
					dec->str[dec->length] = 0;
					index = 0;
					while( ab > 0 ) {
						dec->str[dec->length-index-1] = ( ab % 10 ) + '0';
						index++;
						ab /= 10;
					}
					cpStrAppend( str, "." );
					cpStrAppend( str, dec->str );
					free( dec->str );
					free( dec );
					return str;
				}
				CP_CORE_LOG_WARNING( "CPstring->str 'decimal' malloc fialed in DoubleToString." );
				free( dec );
				free( str->str );
				free( str );
				return CP_NULL;
			}
			CP_CORE_LOG_WARNING( "CPstring 'decimal' malloc failed in DoubleToString." );
			free( str->str );
			free( str );
			return CP_NULL;
		}
		CP_CORE_LOG_WARNING( "CPstring->str malloc failed in DoubleToString." );
		free( str );
		return CP_NULL;
	}
	CP_CORE_LOG_WARNING( "CPstring malloc failed in DoubleToString." );
	return CP_NULL;
}

CPpstring    cpFloatToString( float x, CPsize precision )
{
	int front = (int)x;
	int back = (int)( ( x - (float)front ) * pow( 10.0f, (float)precision )  + 0.5f );
	while( back > 0 && back % 10 == 0 ) back /= 10;
	CPpstring str = malloc( sizeof( CPstring ) );
	if( str ) {
		str->length = 0;
		int af = abs( front );
		for( int i = 1; af / i > 0; i *= 10 ) str->length++;
		if( front != af ) {
			str->length++;
			str->str = malloc( str->length+1 );
			if( str->str )
				str->str[0] = '-';
		}
		else
			str->str = malloc( str->length+1 );
		if( str->str ) {
			str->str[str->length] = 0;
			CPsize index = 0;
			while( af > 0 ) {
				str->str[str->length - index - 1] = ( af % 10 ) + '0';
				index++;
				af /= 10;
			}

			CPpstring dec = malloc( sizeof( CPstring ) );
			if( dec ) {
				dec->length = 0;
				int ab = abs( back );
				for( int i = 1; ab / i > 0; i *= 10 ) dec->length++;
				dec->str = malloc( dec->length+1 );
				if( dec->str ) {
					dec->str[dec->length] = 0;
					index = 0;
					while( ab > 0 ) {
						dec->str[dec->length-index-1] = ( ab % 10 ) + '0';
						index++;
						ab /= 10;
					}
					cpStrAppend( str, "." );
					cpStrAppend( str, dec->str );
					free( dec->str );
					free( dec );
					return str;
				}
				CP_CORE_LOG_WARNING( "CPstring->str 'decimal' malloc fialed in DoubleToString." );
				free( dec );
				free( str->str );
				free( str );
				return CP_NULL;
			}
			CP_CORE_LOG_WARNING( "CPstring 'decimal' malloc failed in DoubleToString." );
			free( str->str );
			free( str );
			return CP_NULL;
		}
		CP_CORE_LOG_WARNING( "CPstring->str malloc failed in DoubleToString." );
		free( str );
		return CP_NULL;
	}
	CP_CORE_LOG_WARNING( "CPstring malloc failed in DoubleToString." );
	return CP_NULL;
}

CPpstring    cpLongDoubleToString( long double x, CPsize precision )
{
	int front = (int)x;
	int back = (int)( ( x - (long double)front ) * pow( 10.0f, (long double)precision )  + 0.5f );
	while( back > 0 && back % 10 == 0 ) back /= 10;
	CPpstring str = malloc( sizeof( CPstring ) );
	if( str ) {
		str->length = 0;
		int af = abs( front );
		for( int i = 1; af / i > 0; i *= 10 ) str->length++;
		if( front != af ) {
			str->length++;
			str->str = malloc( str->length+1 );
			if( str->str )
				str->str[0] = '-';
		}
		else
			str->str = malloc( str->length+1 );
		if( str->str ) {
			str->str[str->length] = 0;
			CPsize index = 0;
			while( af > 0 ) {
				str->str[str->length - index - 1] = ( af % 10 ) + '0';
				index++;
				af /= 10;
			}

			CPpstring dec = malloc( sizeof( CPstring ) );
			if( dec ) {
				dec->length = 0;
				int ab = abs( back );
				for( int i = 1; ab / i > 0; i *= 10 ) dec->length++;
				dec->str = malloc( dec->length+1 );
				if( dec->str ) {
					dec->str[dec->length] = 0;
					index = 0;
					while( ab > 0 ) {
						dec->str[dec->length-index-1] = ( ab % 10 ) + '0';
						index++;
						ab /= 10;
					}
					cpStrAppend( str, "." );
					cpStrAppend( str, dec->str );
					free( dec->str );
					free( dec );
					return str;
				}
				CP_CORE_LOG_WARNING( "CPstring->str 'decimal' malloc fialed in DoubleToString." );
				free( dec );
				free( str->str );
				free( str );
				return CP_NULL;
			}
			CP_CORE_LOG_WARNING( "CPstring 'decimal' malloc failed in DoubleToString." );
			free( str->str );
			free( str );
			return CP_NULL;
		}
		CP_CORE_LOG_WARNING( "CPstring->str malloc failed in DoubleToString." );
		free( str );
		return CP_NULL;
	}
	CP_CORE_LOG_WARNING( "CPstring malloc failed in DoubleToString." );
	return CP_NULL;
}

CPpstring    cpSignedByteToString( char x )
{
	CPpstring str = malloc( sizeof( CPstring ) );
	if( str ) {
		str->length = 0;
		char y = (char)abs( (int)x );
		for( char i = 1; y / i > 0; i *= 10 ) str->length++;
		if( x != y ) {
			str->length++;
			str->str = malloc( str->length+1 );
			if( str->str )
				str->str[0] = '-';
		}
		else
			str->str = malloc( str->length+1 );
		if( str->str ) {
			str->str[str->length] = 0;
			CPsize index = 0;
			while( y > 0 ) {
				str->str[str->length - index - 1] = ( y % 10 ) + '0';
				index++;
				y /= 10;
			}
			return str;
		}
		CP_CORE_LOG_WARNING( "CPstring->str malloc failed in IntToString." );
		free( str );
		return CP_NULL;
	}
	CP_CORE_LOG_WARNING( "CPstring malloc failed in IntToString." );
	return CP_NULL;
}

CPpstring    cpShortToString( short x )
{
	CPpstring str = malloc( sizeof( CPstring ) );
	if( str ) {
		str->length = 0;
		short y = abs( x );
		for( short i = 1; y / i > 0; i *= 10 ) str->length++;
		if( x != y ) {
			str->length++;
			str->str = malloc( str->length+1 );
			if( str->str )
				str->str[0] = '-';
		}
		else
			str->str = malloc( str->length+1 );
		if( str->str ) {
			str->str[str->length] = 0;
			CPsize index = 0;
			while( y > 0 ) {
				str->str[str->length - index - 1] = ( y % 10 ) + '0';
				index++;
				y /= 10;
			}
			return str;
		}
		CP_CORE_LOG_WARNING( "CPstring->str malloc failed in IntToString." );
		free( str );
		return CP_NULL;
	}
	CP_CORE_LOG_WARNING( "CPstring malloc failed in IntToString." );
	return CP_NULL;
}

CPpstring    cpLongLongToString( long long x )
{
	CPpstring str = malloc( sizeof( CPstring ) );
	if( str ) {
		str->length = 0;
		long long y = abs( x );
		for( long long i = 1; y / i > 0; i *= 10 ) str->length++;
		if( x != y ) {
			str->length++;
			str->str = malloc( str->length+1 );
			if( str->str )
				str->str[0] = '-';
		}
		else
			str->str = malloc( str->length+1 );
		if( str->str ) {
			str->str[str->length] = 0;
			CPsize index = 0;
			while( y > 0 ) {
				str->str[str->length - index - 1] = ( y % 10 ) + '0';
				index++;
				y /= 10;
			}
			return str;
		}
		CP_CORE_LOG_WARNING( "CPstring->str malloc failed in IntToString." );
		free( str );
		return CP_NULL;
	}
	CP_CORE_LOG_WARNING( "CPstring malloc failed in IntToString." );
	return CP_NULL;
}

int		     cpStringToInt( CPpstring str )
{
	const char *tstr = str->str;
	int mult = 1;
	int val = 0;
	if( tstr[0] == '-' ) {
		mult = -1;
		tstr++;
	}
	while( *tstr ) {
		val = val*10 + ( *tstr++ - '0' );
	}
	return val;
}

CPdword	     cpStringToDWord( CPpstring str )
{
	const char *tstr = str->str;
	CPdword val = 0;
	while( *tstr ) {
		val = val*10 + ( *tstr++ - '0' );
	}
	return val;
}

CPword	     cpStringToWord( CPpstring str )
{
	const char *tstr = str->str;
	CPword val = 0;
	while( *tstr ) {
		val = val*10 + ( *tstr++ - '0' );
	}
	return val;
}

CPbyte	     cpStringToByte( CPpstring str )
{
	const char *tstr = str->str;
	CPbyte val = 0;
	while( *tstr ) {
		val = val*10 + ( *tstr++ - '0' );
	}
	return val;
}
 
CPqword	     cpStringToQWord( CPpstring str )
{
	const char *tstr = str->str;
	CPqword val = 0;
	while( *tstr ) {
		val = val*10 + ( *tstr++ - (CPqword)'0' );
	}
	return val;
}

double	     cpStringToDouble( CPpstring str )
{
	const char *tstr = str->str;
	double val = 0.0;
	double bval = 0.0;
	CPbool dec = CP_FALSE;
	while( *tstr && !dec ) {
		if( *tstr == '.' ) {
			dec = CP_TRUE;
		}
		else val = val*10.0 + ( *tstr++ - ( double )'0' );
	}
	tstr = &str->str[str->length-1];
	while( *tstr != '.' ) {
		bval = bval*0.1 + ( *tstr-- - ( double )'0' );
	}
	bval *= 0.1;
	val += bval;
	return val;
}

float	     cpStringToFloat( CPpstring str )
{
	const char *tstr = str->str;
	float val = 0.0f;
	float bval = 0.0f;
	CPbool dec = CP_FALSE;
	while( *tstr && !dec ) {
		if( *tstr == '.' ) {
			dec = CP_TRUE;
		}
		else val = val*10.0f + ( *tstr++ - ( float )'0' );
	}
	tstr = &str->str[str->length-1];
	while( *tstr != '.' ) {
		bval = bval*0.1f + ( *tstr-- - ( float )'0' );
	}
	bval *= 0.1f;
	val += bval;
	return val;
}

long double  cpStringToLongDouble( CPpstring str )
{
	const char *tstr = str->str;
	double val = 0.0;
	double bval = 0.0;
	CPbool dec = CP_FALSE;
	while( *tstr && !dec ) {
		if( *tstr == '.' ) {
			dec = CP_TRUE;
		}
		else val = val*10.0 + ( *tstr++ - ( long double )'0' );
	}
	tstr = &str->str[str->length-1];
	while( *tstr != '.' ) {
		bval = bval*0.1 + ( *tstr-- - ( long double )'0' );
	}
	bval *= 0.1;
	val += bval;
	return val;
}

char         cpStringToSignedByte( CPpstring str )
{
	const char *tstr = str->str;
	char mult = 1;
	char val = 0;
	if( tstr[0] == '-' ) {
		mult = -1;
		tstr++;
	}
	while( *tstr ) {
		val = val*10 + ( *tstr++ - '0' );
	}
	return val;

}

short        cpStringToShort( CPpstring str )
{
	const char *tstr = str->str;
	short mult = 1;
	short val = 0;
	if( tstr[0] == '-' ) {
		mult = -1;
		tstr++;
	}
	while( *tstr ) {
		val = val*10 + ( *tstr++ - '0' );
	}
	return val;

}

long long    cpStringToLongLong( CPpstring str )
{
	const char *tstr = str->str;
	long long mult = 1;
	long long val = 0;
	if( tstr[0] == '-' ) {
		mult = -1;
		tstr++;
	}
	while( *tstr ) {
		val = val*10 + ( *tstr++ - (long long)'0' );
	}
	return val;
}