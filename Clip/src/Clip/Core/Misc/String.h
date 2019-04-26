#ifndef CP_STRING_H_
#define CP_STRING_H_

#include "Clip/Core/Core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCPstring
{
	char* str;
	CPsize length;
} CPstring, *CPpstring;


CP_API CPpstring cpCreateString( const char* str );
CP_API void cpDeleteString( CPpstring str );
CP_API char cpStrGetChar( CPpstring str, CPsize loc );
CP_API CPsize cpStrFind( CPpstring str, const char* find );
CP_API void cpStrAppend( CPpstring str, const char* cstr );
CP_API void cpStrReplace( CPpstring str, const char* find, const char* replace );
CP_API void cpStrInsert( CPpstring str, const char* ins, CPsize loc );
CP_API CPpstring cpStrSubStr( CPpstring str, CPsize loc, CPsize count );

#ifdef __cplusplus
}
#endif

#endif