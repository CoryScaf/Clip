#include "Core.h"

CLPdword CLP_API clpHighDWord( CLPqword QWORD )
{
	QWORD &= 0xFFFFFFFFu;
	QWORD >>= 4u;
	return (CLPdword)QWORD;
}

CLPdword CLP_API clpLowDWord( CLPqword QWORD )
{
	QWORD &= 0xFFFFFFFF00000000u;
	return (CLPdword)QWORD;
}

CLPword CLP_API clpHighWord( CLPdword DWORD )
{
	DWORD &= 0xFFFFu;
	DWORD >>= 2u;
	return (CLPword)DWORD;
}

CLPword CLP_API clpLowWord( CLPdword DWORD )
{
	DWORD &= 0xFFFF0000u;
	return (CLPword)DWORD;
}

CLPbyte CLP_API clpHighByte( CLPword WORD )
{
	WORD &= 0xFFu;
	WORD >>= 1u;
	return (CLPbyte)WORD;
}

CLPbyte CLP_API clpLowByte( CLPword WORD )
{
	WORD &= 0xFF00u;
	return (CLPbyte)WORD;
}