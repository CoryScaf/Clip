#ifndef CP_PRECOMPILED_HEADER_
#define CP_PRECOMPILED_HEADER_

#include "src/CPCore/Core.h"

#if CP_PLATFORM & CP_PLATFORM_WINDOWS

#define _WIN32_WINNT 0x0601
//#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS 
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE

#define STRICT

//#include <Windows.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "src/CPCore/Misc/Color.h"
#include "src/CPCore/Misc/String.h"
#include "src/CPCore/Misc/MiscFunctions.h"

#endif
