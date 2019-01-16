#include "Core.h"

CLdword CL_API clHighDWord( CLqword QWORD )
{
	QWORD &= 0xFFFFFFFFu;
	QWORD >>= 4u;
	return (CLdword)QWORD;
}

CLdword CL_API clLowDWord( CLqword QWORD )
{
	QWORD &= 0xFFFFFFFF00000000u;
	return (CLdword)QWORD;
}

CLword CL_API clHighWord( CLdword DWORD )
{
	DWORD &= 0xFFFFu;
	DWORD >>= 2u;
	return (CLword)DWORD;
}

CLword CL_API clLowWord( CLdword DWORD )
{
	DWORD &= 0xFFFF0000u;
	return (CLword)DWORD;
}

CLbyte CL_API clHighByte( CLword WORD )
{
	WORD &= 0xFFu;
	WORD >>= 1u;
	return (CLbyte)WORD;
}

CLbyte CL_API clLowByte( CLword WORD )
{
	WORD &= 0xFF00u;
	return (CLbyte)WORD;
}