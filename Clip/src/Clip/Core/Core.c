#include "Core.h"

CPdword CP_API cpHighDWord( CPqword QWORD )
{
	QWORD &= 0xFFFFFFFFu;
	QWORD >>= 4u;
	return (CPdword)QWORD;
}

CPdword CP_API cpLowDWord( CPqword QWORD )
{
	QWORD &= 0xFFFFFFFF00000000u;
	return (CPdword)QWORD;
}

CPword CP_API cpHighWord( CPdword DWORD )
{
	DWORD &= 0xFFFFu;
	DWORD >>= 2u;
	return (CPword)DWORD;
}

CPword CP_API cpLowWord( CPdword DWORD )
{
	DWORD &= 0xFFFF0000u;
	return (CPword)DWORD;
}

CPbyte CP_API cpHighByte( CPword WORD )
{
	WORD &= 0xFFu;
	WORD >>= 1u;
	return (CPbyte)WORD;
}

CPbyte CP_API cpLowByte( CPword WORD )
{
	WORD &= 0xFF00u;
	return (CPbyte)WORD;
}