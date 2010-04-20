/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGEWin32.h
	created:	2010/3/19
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	Percompiled header files of DirectX
************************************************************************/
#ifndef YGEWIN32_H
#define YGEWIN32_H
//-------------------------Windows---------------------------------------
	#ifndef _linux

		#include <windows.h>
		#include <windowsx.h>
		#include <tchar.h>
		#include <mmsystem.h>

		#pragma comment( lib,"winmm.lib" )

//-------------------------Linux------------------------------------------
	#endif
//------------------------------------------------------------------------
#endif