#ifndef CP_CORE_H_
#define CP_CORE_H_

#ifndef CP_DIST
#include <stdio.h>
#endif

#ifdef _WIN32
#define CP_PLATFORM_WINDOWS
#elif defined( __linux )
#define CP_PLATFORM_LINUX
#endif

#if defined( __clang__ )
#define CP_COMPILER_CLANG
#elif defined( __ICC ) || defined( __INTEL_COMPILER )
#define CP_COMPILER_INTEL
#elif defined( __GNUC__ ) || defined( __GNUG__ )
#define CP_COMPILER_GCC
#elif defined( __HPP_cc ) || defined( __HP_aCC )
#define CP_COMPILER_HOWLETT_PACKARD
#elif defined( __IBMC__ ) || defined( __IBMCPP__ )
#define CP_COMPILER_IBM_XL
#elif defined( _MSC_VER )
#define CP_COMPILER_VISUAL_STUDIO
#elif defined( __PGI )
#define CP_COMPILER_PGCC
#elif defined( __SUNPRO_C ) || defined( __SUNPRO_CC )
#define CP_COMPILER_SOLARIS_STUDIO
#endif

#ifdef CP_PLATFORM_WINDOWS
#	ifdef CP_BUILD_DLL
#		define CP_API __declspec( dllexport )
#	else
#		define CP_API __declspec( dllimport )
#	endif
#endif

#if !defined( CP_API_OPENGL ) && !defined( CP_API_VULKAN ) && !defined( CP_API_DIRECTX )
#	define CP_API_OPENGL
#endif

#define CP_BIT( x ) 1 << x

#define CP_TRUE 1
#define CP_FALSE 0

#define CP_NULL (void*)0

typedef unsigned char CPbyte;
typedef unsigned short CPword;
typedef unsigned int CPdword;
typedef unsigned long long int CPqword;
typedef CPqword CPsize;
typedef CPbyte CPbool;

#ifdef __cplusplus
extern "C" {
#endif

CPdword CP_API cpHighDWord( CPqword QWORD );
CPdword CP_API cpLowDWord( CPqword QWORD );

CPword CP_API cpHighWord( CPdword DWORD );
CPword CP_API cpLowWord( CPdword DWORD );

CPbyte CP_API cpHighByte( CPword WORD );
CPbyte CP_API cpLowByte( CPword WORD );

#ifdef __cplusplus
}
#endif

#endif