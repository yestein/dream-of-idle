/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGEApplication.cpp
	created:	2010/3/20
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	Create a Application 
************************************************************************/
#include "YGEApplication.h"
#include "YGEDefine.h"
#include "YGED3D9Renderer.h"

using namespace YGEDefine;
/*************************************************************************
	Static Data Definitions
*************************************************************************/

// error strings displayed during initialisation
const TCHAR YGEApplication::REGISTER_CLASS_ERROR[]  = _TEXT("Failed to Register Window Class");
const TCHAR YGEApplication::CREATE_WINDOW_ERROR[]   = _TEXT("Failed to Create Window");
const TCHAR	YGEApplication::INIT_RENDERER_ERROR[]   = _TEXT("Failed to Init Render");
const TCHAR	YGEApplication::INIT_GUI_SYSTEM_ERROR[] = _TEXT("Failed to Init GUI System");
// data files path
const TCHAR	YGEApplication::DATA_FILES_PATH[]	= _TEXT("../../datafiles");

YGEApplication::YGEApplication( ):
m_pRenderer( NULL ),
m_pThisWnd( NULL ),
m_uHeight( DEFAULT_WND_HEIGHT ),
m_uWidth( DEFAULT_WND_WIDTH )
{

}
/*************************************************************************
	 Win32 'Window Procedure' function
*************************************************************************/
LRESULT YGEApplication::wndProc( HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam )
{
	switch(Message)
	{
		//窗口大小改变消息的处理
	case WM_ACTIVATEAPP:
		// 			bActive = (BOOL)wParam;
		return 0;
	case WM_SIZE:
		//获取窗口客户区的屏幕坐标系位置
		// 			GetClientRect( hWnd, &rectWin );
		// 			ClientToScreen( hWnd, (LPPOINT)&rectWin );
		// 			ClientToScreen( hWnd, (LPPOINT)&rectWin + 1 );
		return 0;

		//窗口位置改变消息的处理
	case WM_MOVE:
		//获取窗口客户区的屏幕坐标系位置
		// 			GetClientRect( hWnd, &rectWin );
		// 			ClientToScreen( hWnd, (LPPOINT)&rectWin );
		// 			ClientToScreen( hWnd, (LPPOINT)&rectWin + 1 );
		return 0;
	case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			return 0;
		}
	default:
        return DefWindowProc(hWnd, Message, wParam, lParam );
	}
}


/*************************************************************************
	Register a window Class
*************************************************************************/
bool YGEApplication::RegisterWndClass(HINSTANCE hInst,LPCTSTR szAppName)
{
	WNDCLASS WndClass;

	WndClass.style         = CS_HREDRAW|CS_VREDRAW;
	WndClass.lpfnWndProc   = wndProc;
	WndClass.cbClsExtra    = 0;
	WndClass.cbWndExtra    = 0;
	WndClass.hInstance     = hInst;
	WndClass.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hCursor       = LoadCursor(NULL,IDC_ARROW);
	WndClass.hbrBackground = GetStockBrush(BLACK_BRUSH);
	WndClass.lpszMenuName  = NULL;
	WndClass.lpszClassName = szAppName;

	return ( RegisterClass( &WndClass ) != 0 );
}


/*************************************************************************
	Create a window 
*************************************************************************/
HWND YGEApplication::CreateWnd( HINSTANCE hInstance,
							LPCTSTR szAppName,LPCTSTR szWndTitleName,
							int width,int height, bool bWindowed )
{
	m_bWindowed = bWindowed;
	// 计算窗口实际需要大小，并将位置设定在屏幕正中间 
	int ScreenWidth = GetSystemMetrics( SM_CXSCREEN );
	int ScreenHeight = GetSystemMetrics( SM_CYSCREEN );

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect( &rc, WS_VISIBLE | WS_SYSMENU | WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX, FALSE );

	int adjustWndWidth = rc.right - rc.left;
	int adjustWndHeight = rc.bottom - rc.top;
	int	adjustX = ( ScreenWidth - adjustWndWidth ) / 2;
	int adjustY = ( ScreenHeight - adjustWndHeight ) / 2;

	// 创建窗口
	m_pThisWnd = ::CreateWindow( szAppName, szWndTitleName,
		WS_VISIBLE | WS_SYSMENU | WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX,
		adjustX, adjustY, adjustWndWidth, adjustWndHeight, NULL, NULL, hInstance, NULL );

	// 保存窗口大小属性
	m_uWidth = width;
	m_uHeight = height;

	if( NULL == m_pThisWnd )
	{
		return NULL;
	}
	return m_pThisWnd;
}
/*************************************************************************
	Init Render(D3D,OpenGL...)
*************************************************************************/
bool YGEApplication::InitRenderer( )
{
	if( !m_pRenderer )
	{
		m_pRenderer = new YGED3D9Renderer( );
		m_pRenderer->SetWndOwner( m_pThisWnd );
		m_pRenderer->SetScreenHeight( m_uHeight );
		m_pRenderer->SetScreenWidth( m_uWidth );
		m_pRenderer->SetWindowed( m_bWindowed );
		m_pRenderer->Initialise( );
		return true;
	}
	return true;	
}
/*************************************************************************
	Relase Render
*************************************************************************/
bool YGEApplication::ReleaseRender( )
{
	if( m_pRenderer )
	{
		m_pRenderer->Release( );
		delete m_pRenderer;
		m_pRenderer = 0;
		return true;
	}
	return false;	
}

/*************************************************************************
	Init GUI System ( CEGUI )
*************************************************************************/
bool YGEApplication::InitGUISystem( )
{
	if( !m_pRenderer->m_pCeguiD3D9Renderer  )
		return false;

	new CEGUI::System( m_pRenderer->m_pCeguiD3D9Renderer );

	// initialise the required dirs for the DefaultResourceProvider
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
		(CEGUI::System::getSingleton().getResourceProvider());

	if( !rp )
		return false;

	const char* dataPathPrefix = DATA_FILES_PATH;
	char resourcePath[MAX_FILE_NAME_LENGTH];

	// for each resource type, set a resource group directory
	sprintf(resourcePath, "%s/%s", dataPathPrefix, "schemes/");
	rp->setResourceGroupDirectory("schemes", resourcePath);
	sprintf(resourcePath, "%s/%s", dataPathPrefix, "imagesets/");
	rp->setResourceGroupDirectory("imagesets", resourcePath);
	sprintf(resourcePath, "%s/%s", dataPathPrefix, "fonts/");
	rp->setResourceGroupDirectory("fonts", resourcePath);
	sprintf(resourcePath, "%s/%s", dataPathPrefix, "layouts/");
	rp->setResourceGroupDirectory("layouts", resourcePath);
	sprintf(resourcePath, "%s/%s", dataPathPrefix, "looknfeel/");
	rp->setResourceGroupDirectory("looknfeels", resourcePath);
	sprintf(resourcePath, "%s/%s", dataPathPrefix, "lua_scripts/");
	rp->setResourceGroupDirectory("lua_scripts", resourcePath);
#if defined(CEGUI_WITH_XERCES) && (CEGUI_DEFAULT_XMLPARSER == XercesParser)
	sprintf(resourcePath, "%s/%s", dataPathPrefix, "XMLRefSchema/");
	rp->setResourceGroupDirectory("schemas", resourcePath);
#endif
	CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);


	CEGUI::Imageset::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
#ifdef CEGUI_WITH_XERCES
	CEGUI::XercesParser::setSchemaDefaultResourceGroup("schemas");
#endif
	new YGELuaUIWndMgr( );
	YGELuaUIWndMgr::getSingleton( ).LoadScript( "..\\..\\datafiles\\lua_scripts\\demo7.lua" );

	return true;	
}


