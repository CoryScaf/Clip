#include "pch.h"
#include "Color.h"

CPbyte cpGetR( CPcolor color )
{
	return (CPbyte)( color & 0xFF0000u >> 16u );
}

CPbyte cpGetG( CPcolor color )
{
	return (CPbyte)( color & 0xFF00u >> 8u );
}

CPbyte cpGetB( CPcolor color )
{
	return (CPbyte)( color & 0xFFu );
}

CPbyte cpGetA( CPcolor color )
{
	return (CPbyte)( color & 0xFF000000u >> 24u );
}

CPcolor cpCreateColorRGB( CPbyte Rbyte, CPbyte Gbyte, CPbyte Bbyte )
{
	return ( (CPbyte)( Rbyte << 16u ) ) | ( (CPbyte)( Gbyte << 8u ) ) | Bbyte;
}

CPcolor cpCreateColorRGBA( CPbyte Abyte, CPbyte Rbyte, CPbyte Gbyte, CPbyte Bbyte )
{
	return ( (CPbyte)( Abyte << 24u ) ) | ( (CPbyte)( Rbyte << 16u ) ) | ( (CPbyte)( Gbyte << 8u ) ) | Bbyte;
}