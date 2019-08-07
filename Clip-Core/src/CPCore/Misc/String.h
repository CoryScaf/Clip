#ifndef CP_STRING_H_
#define CP_STRING_H_

#include "CPCore/Core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCPstring
{
	char* str;
	CPsize length;
} CPstring, *CPpstring;


CPpstring cpCreateString( const char* str );
void cpDeleteString( CPpstring str );
char cpStrGetChar( CPpstring str, CPsize loc );
CPsize cpStrFind( CPpstring str, const char* find );
void cpStrAppend( CPpstring str, const char* cstr );
void cpStrReplace( CPpstring str, const char* find, const char* replace );
void cpStrInsert( CPpstring str, const char* ins, CPsize loc );
CPpstring cpStrSubStr( CPpstring str, CPsize loc, CPsize count );

#ifdef __cplusplus
}
#endif

#endif
