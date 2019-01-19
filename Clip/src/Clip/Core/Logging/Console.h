#ifndef CP_CONSOLE_H_
#define CP_CONSOLE_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef enum tagCPconsoleparsetype
	{
		CP_CONSOLE_PARSE_PRINTF_STYLE,
		CP_CONSOLE_PARSE_BRACE_STYLE
	} CPconsoleparsetype;

	typedef struct tagCPconsole
	{
		CPconsoleparsetype parseType;
	} CPconsole;


#ifdef CP_DIST
#	define CP_CORE_LOG_FATAL( ... )
#	define CP_CORE_LOG_ERROR( ... )
#	define CP_CORE_LOG_WARNING( ... )
#	define CP_CORE_LOG_INFO( ... )
#else
#	define CP_CORE_LOG_FATAL( ... ) printf( __VA_ARGS__ )
#	define CP_CORE_LOG_ERROR( ... ) printf( __VA_ARGS__ ) 
#	define CP_CORE_LOG_WARNING( ... ) printf( __VA_ARGS__ )
#	define CP_CORE_LOG_INFO( ... ) printf( __VA_ARGS__ )
#endif

#ifdef __cplusplus
}
#endif

#endif