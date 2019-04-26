#ifndef CP_MISCFUNCTIONS_H_
#define CP_MISCFUNCTIONS_H_

#include "String.h"
#include "Clip/Core/Core.h"

#ifdef __cplusplus
extern "C" {
#endif

CP_API CPpstring cpIntToString( int x );
CP_API CPpstring cpDWordToString( CPdword x );
CP_API CPpstring cpWordToString( CPword x );
CP_API CPpstring cpByteToString( CPbyte x );
CP_API CPpstring cpQWordToString( CPqword x );
CP_API CPpstring cpDoubleToString( double x, CPsize precision );
CP_API CPpstring cpFloatToString( float x, CPsize precision );
CP_API CPpstring cpLongDoubleToString( long double x, CPsize precision );
CP_API CPpstring cpSignedByteToString( char x );
CP_API CPpstring cpShortToString( short x );
CP_API CPpstring cpLongLongToString( long long x );

CP_API int			cpStringToInt( CPpstring str );
CP_API CPdword		cpStringToDWord( CPpstring str );
CP_API CPword		cpStringToWord( CPpstring str );
CP_API CPbyte		cpStringToByte( CPpstring str );
CP_API CPqword		cpStringToQWord( CPpstring str );
CP_API double		cpStringToDouble( CPpstring str );
CP_API float		cpStringToFloat( CPpstring str );
CP_API long double  cpStringToLongDouble( CPpstring str );
CP_API char         cpStringToSignedByte( CPpstring str );
CP_API short        cpStringToShort( CPpstring str );
CP_API long long    cpStringToLongLong( CPpstring str );

#ifdef __cplusplus
}
#endif

#endif