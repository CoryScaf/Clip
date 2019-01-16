#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <stdio.h>

typedef enum tagCLconsoleparsetype
{
	CL_CONSOLE_PARSE_PRINTF_STYLE,
	CL_CONSOLE_PARSE_BRACE_STYLE
} CLconsoleparsetype;

typedef struct _tagCLconsole
{
	CLconsoleparsetype parseType;
} _CLconsole;


#ifdef CL_DIST
#	define CL_CORE_LOG_FATAL( ... )
#	define CL_CORE_LOG_ERROR( ... )
#	define CL_CORE_LOG_WARNING( ... )
#	define CL_CORE_LOG_INFO( ... )
#else
#	define CL_CORE_LOG_FATAL( ... ) printf( __VA_ARGS__ )
#	define CL_CORE_LOG_ERROR( ... ) printf( __VA_ARGS__ ) 
#	define CL_CORE_LOG_WARNING( ... ) printf( __VA_ARGS__ )
#	define CL_CORE_LOG_INFO( ... ) printf( __VA_ARGS__ )
#endif

#endif