#ifndef CLP_CORE_H_
#define CLP_CORE_H_

#ifdef CLP_PLATFORM_WINDOWS
#	ifdef CLP_BUILD_DLL
#		define CLP_API __declspec( dllexport )
#	else
#		define CLP_API __declspec( dllimport )
#	endif
#endif

#if !defined( CLP_API_OPENGL ) && !defined( CLP_API_VULKAN ) && !defined( CLP_API_DIRECTX )
#	define CLP_API_OPENGL
#endif

#define CLP_BIT( x ) 1 << x

#define CLP_TRUE 1
#define CLP_FALSE 0

#define CLP_NULL (void*)0

typedef unsigned char CLPbyte;
typedef unsigned short CLPword;
typedef unsigned int CLPdword;
typedef unsigned long long int CLPqword;


CLPdword CLP_API clpHighDWord( CLPqword QWORD );
CLPdword CLP_API clpLowDWord( CLPqword QWORD );

CLPword CLP_API clpHighWord( CLPdword DWORD );
CLPword CLP_API clpLowWord( CLPdword DWORD );

CLPbyte CLP_API clpHighByte( CLPword WORD );
CLPbyte CLP_API clpLowByte( CLPword WORD );

#endif