/************************************************************************
	filename: 	Sample.cpp
	created:	2010/3/5
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	Create First Win32 Window
************************************************************************/

#include "Sample.h"
#include "Sprite.h"
#include "CEGUI.h"

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nCmdShow)
{

	YGEGame Game;

	YGEAppParam AppParam;
	AppParam.hInstance = hInst;
	AppParam.pApplication = &Game;
	AppParam.hPrevInst = hPrevInst;
	AppParam.bWindowed = true;
	AppParam.bMulti = false;
	AppParam.bShowMouse = true;
	AppParam.uScreenHeight = 600;
	AppParam.uScreenWidth = 800;
	_tcsncpy( AppParam.szAppName, (TCHAR*)"Sample", DEFAULT_TITLE_NAME_LEN );
	_tcsncpy( AppParam.szWndTitleName, (TCHAR*)"Hello World!", DEFAULT_TITLE_NAME_LEN );

	YGEAppFrame App;
	App.CreateApplication( AppParam );
	App.RunApplication( );
	return 0;
}
YGEGame::YGEGame( )
{
// 	m_Sprite = new Sprite( );
// 	m_Map = new Map( );
// 	m_uLastTime = ::GetTickCount( );
}
int YGEGame::HandleInput( UINT Message,WPARAM wParam,LPARAM lParam )
{
	switch( Message )
	{
	case WM_CHAR:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
	case WM_NCMOUSELEAVE:
	case WM_MOUSELEAVE:
	case 0x020A: // WM_MOUSEWHEEL:
		break;
	}
	return 0;
}
bool YGEGame::Init( )
{
	using namespace CEGUI;

// 	// we will use of the WindowManager.
// 	WindowManager& winMgr = WindowManager::getSingleton();
// 
// 	// load scheme and set up defaults
// 	SchemeManager::getSingleton().loadScheme("TaharezLook.scheme");
// 	System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
// 	if(!FontManager::getSingleton().isFontPresent("Commonwealth-10"))
// 		FontManager::getSingleton().createFont("Commonwealth-10.font");
// 
// 	// load an image to use as a background
// 	ImagesetManager::getSingleton().createImagesetFromImageFile("BackgroundImage", "GPN-2000-001437.tga");
// 
// 	// here we will use a StaticImage as the root, then we can use it to place a background image
// 	Window* background = winMgr.createWindow("TaharezLook/StaticImage", "background_wnd");
// 	// set position and size
// 	background->setPosition(UVector2(cegui_reldim(0), cegui_reldim( 0)));
// 	background->setSize(UVector2(cegui_reldim(1), cegui_reldim( 1)));
// 	// disable frame and standard background
// 	background->setProperty("FrameEnabled", "false");
// 	background->setProperty("BackgroundEnabled", "false");
// 	// set the background image
// 	background->setProperty("Image", "set:BackgroundImage image:full_image");
// 	// install this as the root GUI sheet
// 	System::getSingleton().setGUISheet(background);
// 
// 	// load the windows for Demo7 from the layout file.
// 	Window* sheet = winMgr.loadWindowLayout("Demo7Windows.layout");
// 	// attach this to the 'real' root
// 	background->addChildWindow(sheet);
	// set-up the contents of the list boxes.

// 	m_pRenderer = new YGERender( m_pThisWnd, false, m_uWidth, m_uHeight, 16 );
// 	m_pRenderer->Initialise( );
// 	m_pRenderer->m_pDDrawRender->CreateBMPSurface(m_Map->lpSMap,0,0,"background.bmp", DDSCAPS_SYSTEMMEMORY);
// 	m_pRenderer->m_pDDrawRender->CreateBMPSurface(m_Sprite->lpSSprite,0,0,"1.bmp", DDSCAPS_SYSTEMMEMORY);
// 	m_pRenderer->m_pDDrawRender->DDSetColorKey( m_Sprite->lpSSprite, CLR_INVALID );
// 
// 	m_pRenderer->m_pDDrawRender->BlitBack(
// 		0,0,m_Map->lpSMap,
// 		&m_pRenderer->m_pDDrawRender->GetRect(0,0,640,480),
// 		DDBLTFAST_NOCOLORKEY );
// 	m_pRenderer->m_pDDrawRender->BlitBack(
// 		m_Sprite->GetX(),m_Sprite->GetY(),m_Sprite->lpSSprite,
// 		&m_pRenderer->m_pDDrawRender->GetRect(m_Sprite->GetCurFram()*m_Sprite->GetWidth(),m_Sprite->GetDir()*m_Sprite->GetHeight(),m_Sprite->GetCurFram()*m_Sprite->GetWidth()+m_Sprite->GetWidth(),m_Sprite->GetDir()*m_Sprite->GetHeight()+m_Sprite->GetHeight()),
// 		DDBLTFAST_SRCCOLORKEY );
// 	//ÏÔÊ¾
// 	RECT rectWin;
// 	GetClientRect( m_pThisWnd, &rectWin );
// 	ClientToScreen( m_pThisWnd, (LPPOINT)&rectWin );
// 	ClientToScreen( m_pThisWnd, (LPPOINT)&rectWin + 1 );
// 	m_pRenderer->m_pDDrawRender->Flip( &rectWin);
	m_uLastGameTimeCount = m_uLastRenderTimeCount = ::GetTickCount( );
	return true;
}
bool YGEGame::Loop( )
{
	m_uCurTimeCount = ::GetTickCount( );
	if( m_uCurTimeCount - m_uLastGameTimeCount > 1000 / YGEDefine::GAME_FPS )
	{
		m_uLastGameTimeCount += 1000 / GAME_FPS;
		// To do
	}
	if( m_uCurTimeCount - m_uLastRenderTimeCount > 1000 / YGEDefine::RENDER_FPS )
	{

		// To do
		float timeElapse = float( m_uCurTimeCount - m_uLastRenderTimeCount );
		m_uLastRenderTimeCount += 1000 / RENDER_FPS;

		DoRender( timeElapse );		
	}
// 	if( ::GetTickCount() - m_uLastTime >= 1000 )
// 	{
// 		m_uLastTime += 1000;
// 		m_pRenderer->m_pDDrawRender->BlitBack(
// 			0,0,m_Map->lpSMap,
// 			&m_pRenderer->m_pDDrawRender->GetRect(0,0,640,480),
// 			DDBLTFAST_NOCOLORKEY );
// 		m_pRenderer->m_pDDrawRender->BlitBack(
// 			m_Sprite->GetX(),m_Sprite->GetY(),m_Sprite->lpSSprite,
// 			&m_pRenderer->m_pDDrawRender->GetRect(m_Sprite->GetCurFram()*m_Sprite->GetWidth(),m_Sprite->GetDir()*m_Sprite->GetHeight(),m_Sprite->GetCurFram()*m_Sprite->GetWidth()+m_Sprite->GetWidth(),m_Sprite->GetDir()*m_Sprite->GetHeight()+m_Sprite->GetHeight()),
// 			DDBLTFAST_SRCCOLORKEY );
// 		//ÏÔÊ¾
// 		RECT rectWin;
// 		GetClientRect( m_pThisWnd, &rectWin );
// 		ClientToScreen( m_pThisWnd, (LPPOINT)&rectWin );
// 		ClientToScreen( m_pThisWnd, (LPPOINT)&rectWin + 1 );
// 		m_pRenderer->m_pDDrawRender->Flip( &rectWin);
// 	}
	
	return true;
}
bool YGEGame::DoRender( float timeElapse )
{
	HRESULT coop;
	coop = m_pRenderer->m_pDirect3DDevice->TestCooperativeLevel();

	CEGUI::System& guiSystem = CEGUI::System::getSingleton();
	guiSystem.injectTimePulse(timeElapse);

	if (coop == D3DERR_DEVICELOST)
	{
		Sleep(500);
		return false;
	}
	else if (coop == D3DERR_DEVICENOTRESET)
	{

	}

	// draw display
	if (FAILED(m_pRenderer->m_pDirect3DDevice->BeginScene()))
	{
		return false;
	}

	m_pRenderer->m_pDirect3DDevice->Clear(0, 0, D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	guiSystem.renderGUI();
	m_pRenderer->m_pDirect3DDevice->EndScene();
	m_pRenderer->m_pDirect3DDevice->Present(0, 0, 0, 0);

	return true;
}
bool YGEGame::Exit( )
{
	return true;
}