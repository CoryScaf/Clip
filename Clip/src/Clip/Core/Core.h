#ifndef _CORE_H_
#define _CORE_H_

#ifdef CL_PLATFORM_WINDOWS
#	ifdef CL_BUILD_DLL
#		define CL_API __declspec( dllexport )
#	else
#		define CL_API __declspec( dllimport )
#	endif
#endif

#if !defined( CL_API_OPENGL ) && !defined( CL_API_VULKAN ) && !defined( CL_API_DIRECTX )
#	define CL_API_OPENGL
#endif

#define CL_BIT( x ) 1 << x

#define CL_TRUE 1
#define CL_FALSE 0

#define CL_NULL (void*)0

typedef unsigned char CLbyte;
typedef unsigned short CLword;
typedef unsigned int CLdword;
typedef unsigned long long int CLqword;


CLdword CL_API clHighDWord( CLqword QWORD );
CLdword CL_API clLowDWord( CLqword QWORD );

CLword CL_API clHighWord( CLdword DWORD );
CLword CL_API clLowWord( CLdword DWORD );

CLbyte CL_API clHighByte( CLword WORD );
CLbyte CL_API clLowByte( CLword WORD );

#endif