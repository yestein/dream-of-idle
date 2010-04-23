/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGEAppFrame.h
	created:	2010/3/5
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	Create a Application Frame(containfer)
************************************************************************/
#ifndef YGEAPPFRAME_H
#define YGEAPPFRAME_H
//------------------------------------------------------------------------
#include "YGEWin32.h"
#include "YGEApplication.h"
#include "YGEDefine.h"
using namespace YGEDefine;
//------------------------------------------------------------------------

struct YGEAppParam
{
	HINSTANCE		hInstance;
	HINSTANCE		hPrevInst;
	TCHAR			szAppName[DEFAULT_TITLE_NAME_LEN];
	TCHAR			szWndTitleName[DEFAULT_TITLE_NAME_LEN];
	YGEApplication* pApplication;
	bool			bWindowed;
	bool			bShowMouse;
	bool			bMulti;
	unsigned int	uScreenHeight;
	unsigned int	uScreenWidth;
	unsigned int	uMouseHoverTimeSetting;

};

class YGEAppFrame
{
public:

	YGEAppFrame( );
	~YGEAppFrame( ){ }

	bool		CreateApplication	( YGEAppParam& AppParam );
	bool		RunApplication		( void );
	HINSTANCE	GetHinstance		( void ){ return m_hInstance; }
	HWND		GetMainWindow		( void ){ return m_wndMain; }

public:
	
private:
	static LRESULT CALLBACK wndProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam );

	static void	mouseEnter( void );
	static void	mouseLeave( void );
	static UINT virtualKeyToScanCode( WPARAM wParam, LPARAM lParam ); 
	static bool setIMEFollow( HWND hWnd );  
	static bool getFocusedInputBoxCoord( POINT& point, float& height );
	static bool InjectUnicode( CEGUI::utf32 code_point );

	bool	doWin32Event( bool& idle );
	bool	registerWndClass( HINSTANCE hInst, LPCTSTR szAppName );

private:

	static YGEApplication*	ms_pApplication;
	static bool		ms_bMouseInWindow;

	HINSTANCE		m_hInstance;
	HINSTANCE		m_hPrevInst;
	HWND			m_wndMain;
	bool			m_bFullScr;
	bool			m_bIdle;
	TCHAR			m_szAppName[DEFAULT_TITLE_NAME_LEN];
	TCHAR			m_szWndTitleName[DEFAULT_TITLE_NAME_LEN];

};
//----------------------YGEAPPFRAME_H--------------------------------------
#endif