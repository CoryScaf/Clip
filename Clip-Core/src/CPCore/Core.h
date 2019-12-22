#ifndef CP_CORE_H_
#define CP_CORE_H_

#ifndef CP_DIST
#include <stdio.h>
#endif

#if !defined( CP_USE_VULKAN ) && !defined( CP_USE_DIRECTX11 ) && !defined( CP_USE_DIRECTX12 ) && !defined( CP_USE_OPENGL )
#   define CP_USE_OPENGL
#endif

#define CP_PLATFORM_INVALID     0x0000u
#define CP_PLATFORM_WINDOWS     0x0001u
#define CP_PLATFORM_LINUX       0x0002u

#define CP_PROTOCOL_INVALID     0x0004u
#define CP_PROTOCOL_X11         0x0008u
#define CP_PROTOCOL_WAYLAND     0x0010u
#define CP_PROTOCOL_WIN32       0x0020u

#define CP_API_INVALID          0x0040u
#define CP_API_OPENGL           0x0080u
#define CP_API_VULKAN           0x0100u
#define CP_API_DIRECTX11        0x0200u
#define CP_API_DIRECTX12        0x0400u

#if defined( __linux )
#   if defined( CP_USE_WAYLAND )
#       if defined( CP_USE_VULKAN )
#           define CP_PLATFORM ( CP_PLATFORM_LINUX | CP_PROTOCOL_WAYLAND | CP_API_VULKAN )
#       elif defined( CP_USE_DIRECTX11 )
#           define CP_PLATFORM ( CP_PLATFORM_LINUX | CP_PROTOCOL_WAYLAND | CP_API_INVALID )
#       elif defined( CP_USE_DIRECTX12 )
#           define CP_PLATFORM ( CP_PLATFORM_LINUX | CP_PROTOCOL_WAYLAND | CP_API_INVALID )
#       else
#           define CP_PLATFORM ( CP_PLATFORM_LINUX | CP_PROTOCOL_WAYLAND | CP_API_OPENGL )
#       endif
#   else
#       if defined( CP_USE_VULKAN )
#           define CP_PLATFORM ( CP_PLATFORM_LINUX | CP_PROTOCOL_X11 | CP_API_VULKAN )
#       elif defined( CP_USE_DIRECTX12 )
#           define CP_PLATFORM ( CP_PLATFORM_LINUX | CP_PROTOCOL_X11 | CP_API_INVALID )
#       elif defined( CP_USE_DIRECTX11 )
#           define CP_PLATFORM ( CP_PLATFORM_LINUX | CP_PROTOCOL_X11 | CP_API_INVALID )
#       else
#           define CP_PLATFORM ( CP_PLATFORM_LINUX | CP_PROTOCOL_X11 | CP_API_OPENGL )
#       endif
#   endif
#elif defined( _WIN32 )
#   if defined( CP_USE_VULKAN )
#       define CP_PLATFORM ( CP_PLATFORM_WINDOWS | CP_PROTOCOL_WIN32 | CP_API_VULKAN )
#   elif defined( CP_USE_DIRECTX11 )
#       define CP_PLATFORM ( CP_PLATFORM_WINDOWS | CP_PROTOCOL_WIN32 | CP_API_DIRECTX11 )
#   elif defined( CP_USE_DIRECTX12 )
#       define CP_PLATFORM ( CP_PLATFORM_WINDOWS | CP_PROTOCOL_WIN32 | CP_API_DIRECTX12 )
#   else
#       define CP_PLATFORM ( CP_PLATFORM_WINDOWS | CP_PROTOCOL_WIN32 | CP_API_OPENGL )
#   endif
#else
#   define CP_PLATFORM ( CP_PLATFORM_INVALID | CP_PROTOCOL_INVALID | CP_API_INVALID )
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

#define CP_BIT( x ) 1 << x

#define CP_TRUE 1
#define CP_FALSE 0

#define CP_NULL (void*)0

#define CP_ERROR_UNSUPPORTED_PLATFORM   0x0001u
#define CP_ERROR_UNSUPPORTED_PROTOCOL   0x0002u
#define CP_ERROR_INVALID_API            0x0004u

typedef unsigned char CPbyte;
typedef unsigned short CPword;
typedef unsigned long int CPdword;
typedef unsigned long long int CPqword;
typedef CPqword CPsize;
typedef CPbyte CPbool;
typedef CPqword CPerror;
typedef CPerror CPerrortype;

#ifdef __cplusplus
extern "C" {
#endif

CPdword cpHighDWord( CPqword QWORD );
CPdword cpLowDWord( CPqword QWORD );

CPword cpHighWord( CPdword DWORD );
CPword cpLowWord( CPdword DWORD );

CPbyte cpHighByte( CPword WORD );
CPbyte cpLowByte( CPword WORD );

#ifdef __cplusplus
}
#endif

#endif
