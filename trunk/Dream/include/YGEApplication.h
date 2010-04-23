/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGEApplication.h
	created:	2010/3/20
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	Create a Application 
************************************************************************/
#ifndef YGE_APPLICATION_H
#define YGE_APPLICATION_H
//------------------------------------------------------------------------
#include "YGEWin32.h"
#include "YGED3D9Renderer.h"
#include "YGELuaUIWndMgr.h"
#include "YGELuaUIWnd.h"
//------------------------------------------------------------------------
class YGEApplication
{
public:
	YGEApplication( );
	~YGEApplication( ){}

	HWND	CreateWnd( HINSTANCE hInst, LPCTSTR szAppName, LPCTSTR szWndTitleName, int width, int height, bool bWindowed );
	bool	InitRenderer( void );
	bool	InitGUISystem( void );
	bool	ReleaseRender( void );

	virtual int	HandleInput( UINT Message,WPARAM wParam,LPARAM lParam ) = 0;
	virtual bool Init( ) = 0;
	virtual bool Loop( ) = 0;
	virtual bool Exit( ) = 0;

public:

	/*************************************************************************
		Constants
	*************************************************************************/

	// error strings displayed during initialisation
	static const TCHAR  REGISTER_CLASS_ERROR[];
	static const TCHAR  CREATE_WINDOW_ERROR[];
	static const TCHAR	INIT_RENDERER_ERROR[];
	static const TCHAR	INIT_GUI_SYSTEM_ERROR[];

	// data files path
	static const TCHAR	DATA_FILES_PATH[];

private:

private:

protected:

	HWND				m_pThisWnd;
	bool				m_bWindowed;
	unsigned int		m_uWidth;
	unsigned int		m_uHeight;	
	YGED3D9Renderer*	m_pRenderer;

};
//-------------------------YGE_APPLICATION_H-----------------------------------------
#endif 
