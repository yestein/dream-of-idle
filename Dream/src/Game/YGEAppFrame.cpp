/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGEAppFrame.cpp
	created:	2010/3/5
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	Create Application Frame
************************************************************************/
#include "YGEAppFrame.h"

YGEAppFrame::YGEAppFrame( ):
m_hInstance( NULL ),
m_hPrevInst( NULL ),
m_wndMain( NULL ),
m_bFullScr( false ),
m_bIdle( false )
{
	memset( m_szAppName, 0, DEFAULT_TITLE_NAME_LEN );
	memset( m_szWndTitleName, 0, DEFAULT_TITLE_NAME_LEN );
}
bool YGEAppFrame::CreateApplication( YGEAppParam& AppParam )
{

	m_pApplication = AppParam.pApplication;
	m_hInstance = AppParam.hInstance;
	m_hPrevInst = AppParam.hPrevInst;
	_tcsncpy( m_szAppName, AppParam.szAppName, DEFAULT_TITLE_NAME_LEN );
	_tcsncpy( m_szWndTitleName, AppParam.szWndTitleName, DEFAULT_TITLE_NAME_LEN );

	if( !m_hPrevInst )
	{
		// 注册窗口
		if( !m_pApplication->RegisterWndClass( m_hInstance, AppParam.szAppName ) )
		{
			MessageBox( 0, YGEApplication::REGISTER_CLASS_ERROR, m_szAppName, MB_ICONERROR|MB_OK );
			return false;
		}
	}
	// 创建窗口，成功则初始化程序，并顺序初始化渲染器，和GUI系统
	m_wndMain = m_pApplication->CreateWnd( m_hInstance, m_szAppName, m_szWndTitleName, AppParam.uScreenWidth, AppParam.uScreenHeight, AppParam.bWindowed );
	if( m_wndMain )
	{
		if( m_pApplication->InitRenderer( ) )
		{
			if( m_pApplication->InitGUISystem( ) )
			{
				m_pApplication->Init( );
				return true;
			}
			else
			{
				::MessageBox( 0, YGEApplication::INIT_RENDERER_ERROR, m_szAppName, MB_ICONERROR|MB_OK );
				return false;
			}		
		}
		else
		{
			::MessageBox( 0, YGEApplication::INIT_RENDERER_ERROR, m_szAppName, MB_ICONERROR|MB_OK );
			return false;
		}
	}
	else
	{
		::MessageBox( 0, YGEApplication::CREATE_WINDOW_ERROR, m_szAppName, MB_ICONERROR|MB_OK );
		return false;
	}
}
bool YGEAppFrame::RunApplication( )
{
	ShowWindow( m_wndMain, SW_NORMAL );
	UpdateWindow( m_wndMain );

	while( doWin32Event( m_bIdle ) )
	{
		if( m_bIdle )
		{
			m_pApplication->Loop( );
		}
	}
	m_pApplication->ReleaseRender( );
	m_pApplication->Exit( );
	return true;
}

bool YGEAppFrame::doWin32Event( bool& idle )
{
	MSG msg;
	if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
	{
		if( msg.message == WM_QUIT )
		{
			return false;
		}

		TranslateMessage( &msg );
		DispatchMessage( &msg );

		idle = false;
	}
	else
	{
		idle = true;	
	}
	return true;
}