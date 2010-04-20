/************************************************************************
	filename: 	YGEApp.h
	created:	2010/3/19
	author:		Yulei

	purpose:	Create a Application 
************************************************************************/
//------------------------------------------------------------------------
#ifndef YGEAPP_H
#define YGEAPP_H
//------------------------------------------------------------------------
#include "YGEWin32.h"
class YGEApp
{
public:
public:
private:
	HWND createWindow( HWND hWnd, HINSTANCE hInst, int nCmdShow, char *szAppName, char* szWndName, int x, int y, int width, int height );
	BOOL registerWndClass( HINSTANCE hInst, char* szAppName );
	LRESULT CALLBACK wndProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam );
private:

};
//------------------------------------------------------------------------
#endif