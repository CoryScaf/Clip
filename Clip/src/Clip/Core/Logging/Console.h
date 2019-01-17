#ifndef CLP_CONSOLE_H_
#define CLP_CONSOLE_H_

#include <stdio.h>

typedef enum tagCLPconsoleparsetype
{
	CLP_CONSOLE_PARSE_PRINTF_STYLE,
	CLP_CONSOLE_PARSE_BRACE_STYLE
} CLPconsoleparsetype;

typedef struct tagCLPconsole
{
	CLPconsoleparsetype parseType;
} CLPconsole;


#ifdef CLP_DIST
#	define CLP_CORE_LOG_FATAL( ... )
#	define CLP_CORE_LOG_ERROR( ... )
#	define CLP_CORE_LOG_WARNING( ... )
#	define CLP_CORE_LOG_INFO( ... )
#else
#	define CLP_CORE_LOG_FATAL( ... ) printf( __VA_ARGS__ )
#	define CLP_CORE_LOG_ERROR( ... ) printf( __VA_ARGS__ ) 
#	define CLP_CORE_LOG_WARNING( ... ) printf( __VA_ARGS__ )
#	define CLP_CORE_LOG_INFO( ... ) printf( __VA_ARGS__ )
#endif

#endif