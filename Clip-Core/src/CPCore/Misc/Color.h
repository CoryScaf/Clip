#ifndef CP_COLOR_H_
#define CP_COLOR_H_

#include "CPCore/Core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef CPdword CPcolor;

CPbyte cpGetR( CPcolor color );
CPbyte cpGetG( CPcolor color );
CPbyte cpGetB( CPcolor color );
CPbyte cpGetA( CPcolor color );

CPcolor cpCreateColorRGBA( CPbyte Abyte, CPbyte Rbyte, CPbyte Gbyte, CPbyte Bbyte );
CPcolor cpCreateColorRGB( CPbyte Rbyte, CPbyte Gbyte, CPbyte Bbyte );

#define CP_COLOR_WHITE cpCreateColor( 255, 255, 255 )
#define CP_COLOR_BLACK cpCreateColor( 0, 0, 0 )
#define CP_COLOR_RED cpCreateColor( 255, 0, 0 )
#define CP_COLOR_GREEN cpCreateColor( 0, 255, 0 )
#define CP_COLOR_BLUE cpCreateColor( 0, 0, 255 )
#define CP_COLOR_YELLOW cpCreateColor( 255, 255, 0 );
#define CP_COLOR_AQUA cpCreateColor( 0, 255, 255 );
#define CP_COLOR_MAGENTA cpCreateColor( 255, 0, 255 );
#define CP_COLOR_ORANGE cpCreateColor( 255, 128, 0 );

#ifdef __cplusplus
}
#endif

#endif
