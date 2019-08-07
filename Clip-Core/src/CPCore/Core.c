#include "pch.h"
#include "Core.h"

CPdword cpHighDWord( CPqword QWORD )
{
	QWORD &= 0xFFFFFFFFu;
	QWORD >>= 4u;
	return (CPdword)QWORD;
}

CPdword cpLowDWord( CPqword QWORD )
{
	QWORD &= 0xFFFFFFFF00000000u;
	return (CPdword)QWORD;
}

CPword cpHighWord( CPdword DWORD )
{
	DWORD &= 0xFFFFu;
	DWORD >>= 2u;
	return (CPword)DWORD;
}

CPword cpLowWord( CPdword DWORD )
{
	DWORD &= 0xFFFF0000u;
	return (CPword)DWORD;
}

CPbyte cpHighByte( CPword WORD )
{
	WORD &= 0xFFu;
	WORD >>= 1u;
	return (CPbyte)WORD;
}

CPbyte cpLowByte( CPword WORD )
{
	WORD &= 0xFF00u;
	return (CPbyte)WORD;
}