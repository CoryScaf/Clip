#ifndef CP_MISCFUNCTIONS_H_
#define CP_MISCFUNCTIONS_H_

#include "String.h"
#include "CPCore/Core.h"

#ifdef __cplusplus
extern "C" {
#endif

CPpstring cpIntToString( int x );
CPpstring cpDWordToString( CPdword x );
CPpstring cpWordToString( CPword x );
CPpstring cpByteToString( CPbyte x );
CPpstring cpQWordToString( CPqword x );
CPpstring cpDoubleToString( double x, CPsize precision );
CPpstring cpFloatToString( float x, CPsize precision );
CPpstring cpLongDoubleToString( long double x, CPsize precision );
CPpstring cpSignedByteToString( char x );
CPpstring cpShortToString( short x );
CPpstring cpLongLongToString( long long x );

int			cpStringToInt( CPpstring str );
CPdword		cpStringToDWord( CPpstring str );
CPword		cpStringToWord( CPpstring str );
CPbyte		cpStringToByte( CPpstring str );
CPqword		cpStringToQWord( CPpstring str );
double		cpStringToDouble( CPpstring str );
float		cpStringToFloat( CPpstring str );
long double  cpStringToLongDouble( CPpstring str );
char         cpStringToSignedByte( CPpstring str );
short        cpStringToShort( CPpstring str );
long long    cpStringToLongLong( CPpstring str );

#ifdef __cplusplus
}
#endif

#endif
