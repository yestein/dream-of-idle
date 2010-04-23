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

/*************************************************************************
	Static Data Definitions
*************************************************************************/
// Applicaiton for Win32 Window
YGEApplication*	YGEAppFrame::ms_pApplication = NULL;
// variable for tracking Win32 cursor
bool YGEAppFrame::ms_bMouseInWindow = false;

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

	ms_pApplication = AppParam.pApplication;
	m_hInstance = AppParam.hInstance;
	m_hPrevInst = AppParam.hPrevInst;
	_tcsncpy( m_szAppName, AppParam.szAppName, DEFAULT_TITLE_NAME_LEN );
	_tcsncpy( m_szWndTitleName, AppParam.szWndTitleName, DEFAULT_TITLE_NAME_LEN );

	if( !m_hPrevInst )
	{
		// 注册窗口
		if( !registerWndClass( m_hInstance, AppParam.szAppName ) )
		{
			MessageBox( 0, YGEApplication::REGISTER_CLASS_ERROR, m_szAppName, MB_ICONERROR|MB_OK );
			return false;
		}
	}
	// 创建窗口，成功则初始化程序，并顺序初始化渲染器，和GUI系统
	m_wndMain = ms_pApplication->CreateWnd( m_hInstance, m_szAppName, m_szWndTitleName, AppParam.uScreenWidth, AppParam.uScreenHeight, AppParam.bWindowed );
	if( m_wndMain )
	{
		if( ms_pApplication->InitRenderer( ) )
		{
			if( ms_pApplication->InitGUISystem( ) )
			{
				ms_pApplication->Init( );
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
			ms_pApplication->Loop( );
		}
	}
	ms_pApplication->ReleaseRender( );
	ms_pApplication->Exit( );
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
/*************************************************************************
Win32 'Window Procedure' function
*************************************************************************/
LRESULT YGEAppFrame::wndProc( HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam )
{
	switch( Message )
	{
	case WM_CHAR:
		{
 			InjectUnicode( (CEGUI::utf32)wParam );
// 			CEGUI::System::getSingleton( ).injectChar( (CEGUI::utf32)wParam );
			YGEAppFrame::ms_pApplication->HandleInput( Message, wParam, lParam );
		}
		break;
	case WM_LBUTTONDOWN:
		{
			CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
			YGEAppFrame::ms_pApplication->HandleInput( Message, wParam, lParam );
		}		
		break;

	case WM_LBUTTONUP:
		{
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
			YGEAppFrame::ms_pApplication->HandleInput( Message, wParam, lParam );
		}
		break;

	case WM_RBUTTONDOWN:
		{
			CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
			YGEAppFrame::ms_pApplication->HandleInput( Message, wParam, lParam );
		}
		break;

	case WM_RBUTTONUP:
		{
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
			YGEAppFrame::ms_pApplication->HandleInput( Message, wParam, lParam );
		}
		break;

	case WM_MBUTTONDOWN:
		{
			CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
			YGEAppFrame::ms_pApplication->HandleInput( Message, wParam, lParam );
		}
		break;

	case WM_MBUTTONUP:
		{
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
			YGEAppFrame::ms_pApplication->HandleInput( Message, wParam, lParam );
		}
		break;
	case WM_MOUSEMOVE:
		{
			mouseEnter( );
			CEGUI::System::getSingleton().injectMousePosition((float)(LOWORD(lParam)), (float)(HIWORD(lParam)));
			YGEAppFrame::ms_pApplication->HandleInput( Message, wParam, lParam );
		}
		break;
	case WM_NCMOUSELEAVE:
	case WM_MOUSELEAVE:
		{
			mouseLeave( );
		}
		break;
	case 0x020A: // WM_MOUSEWHEEL:
		{
			CEGUI::System::getSingleton().injectMouseWheelChange(static_cast<float>((short)HIWORD(wParam)) / static_cast<float>(120));
			YGEAppFrame::ms_pApplication->HandleInput( Message, wParam, lParam );
		}
		break;
	case WM_KEYDOWN:  
		{  
			setIMEFollow(hWnd);  
			//输入法状态时，输入不传递到UI系统中去。  
			UINT vk = (UINT)ImmGetVirtualKey(hWnd);   
			if(vk == wParam)  
				break;  
          	CEGUI::System::getSingleton().injectKeyDown((CEGUI::utf32)(virtualKeyToScanCode(wParam, lParam)));  
		}  
		break;  
	case WM_KEYUP:  
		{
			CEGUI::System::getSingleton().injectKeyUp((CEGUI::utf32)(virtualKeyToScanCode(wParam, lParam)));  
		}
		break;  
		//窗口大小改变消息的处理
	case WM_ACTIVATEAPP:
		// 			bActive = (BOOL)wParam;
		break;
	case WM_SIZE:
		{
			// get CEGUI::System as a pointer so we can detect if it's not
			// instantiated yet.
			CEGUI::System* cegui_system = CEGUI::System::getSingletonPtr();

			// only continue if CEGUI is up an running and window was not
			// minimised (else it's just a waste of time)
			if ((cegui_system != 0) && (wParam != SIZE_MINIMIZED))
			{
				// get renderer identification string
				CEGUI::Renderer* renderer = cegui_system->getRenderer();
				CEGUI::String id(renderer->getIdentifierString());
			}
		}
		break;
	case WM_PAINT:
		{
			HDC         hDC;
			PAINTSTRUCT ps;

			hDC = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;
		//窗口位置改变消息的处理
	case WM_MOVE:
		//获取窗口客户区的屏幕坐标系位置
		// 			GetClientRect( hWnd, &rectWin );
		// 			ClientToScreen( hWnd, (LPPOINT)&rectWin );
		// 			ClientToScreen( hWnd, (LPPOINT)&rectWin + 1 );
		break;
	case WM_DESTROY:
		{
			PostQuitMessage( 0 );
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam );
	}
	return 0;
}
/*************************************************************************
Register a window Class
*************************************************************************/
bool YGEAppFrame::registerWndClass(HINSTANCE hInst,LPCTSTR szAppName)
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
	handle Mouse Enter 
*************************************************************************/
void YGEAppFrame::mouseEnter( void )
{
	if( !ms_bMouseInWindow )
	{
		ms_bMouseInWindow = true;
		ShowCursor( false );
	}
}
/*************************************************************************
	handle Mouse Leave
*************************************************************************/
void YGEAppFrame::mouseLeave( void )
{
	if( ms_bMouseInWindow )
	{
		ms_bMouseInWindow = false;
		ShowCursor( true );
	}
}

UINT YGEAppFrame::virtualKeyToScanCode( WPARAM wParam, LPARAM lParam )
{  
	if(HIWORD(lParam) & 0x0F00)   
	{   
		UINT scancode = MapVirtualKey(wParam, 0);   
		return scancode | 0x80;   
	}   
	else   
	{   
		return HIWORD(lParam) & 0x00FF;   
	}   
}  
bool YGEAppFrame::setIMEFollow( HWND hWnd )
{  
    //判断输入法是否打开  
    if (!ImmIsIME(GetKeyboardLayout(0)))  
        return false;  
      
    //获得输入框左上坐标  
    bool result;  
    POINT point;  
    float height;  
	result = getFocusedInputBoxCoord(point, height);  
    if(!result)  
        return false;  
      
    //获得客户区的坐标  
    RECT rect;  
    GetClientRect(hWnd, &rect);  
    point.x+=rect.left;  
    point.y+=rect.top;  
  
    //设置输入法位置  
    HIMC hImc = ImmGetContext(hWnd);  
    if(hImc==NULL) return false;  
    COMPOSITIONFORM form;  
    ImmGetCompositionWindow(hImc, &form);  
    form.ptCurrentPos.x = point.x;  
    form.ptCurrentPos.y = point.y + height;  
    ImmSetCompositionWindow(hImc, &form);  
  
    return true;      
}  
//寻找到有输入焦点的EditBox的左上坐标  
bool YGEAppFrame::getFocusedInputBoxCoord( POINT& point, float& height )  
{  
    //遍历所有窗口  
    CEGUI::WindowManager::WindowIterator wit = CEGUI::WindowManager::getSingleton().getIterator();  
    while(!wit.isAtEnd())  
    {  
        const CEGUI::Window* widget = (*wit)->getActiveChild();  
        //如果是EditBox或者 MultiLineEditBox  
        if(widget)  
        {  
            CEGUI::String windowType = widget->getType();  
            if(windowType == "TaharezLook/Editbox") //根据具体的scheme来修改  
            {  
                const CEGUI::UVector2& winPos = widget->getPosition();  
                height = widget->getPixelSize().d_height;
                     
                CEGUI::Vector2 winPos1 = CEGUI::CoordConverter::windowToScreen(*widget, winPos);  
  
                point.x = winPos1.d_x;  
                point.y = winPos1.d_y;  
                return true;  
            }  
        }  
        wit++;  
    }  
  
    return false;  
}
bool YGEAppFrame::InjectUnicode( CEGUI::utf32 code_point ) 
{
#ifndef UNICODE
	static char     s_tempChar[3]  = "";
	static wchar_t  s_tempWchar[2] = L"";
	static bool s_flag = false;
	unsigned char  uch  = (unsigned char)code_point;
	if( uch >= 0xA1 )
	{
		if( !s_flag )
		{
			s_tempChar[0] = (char)uch; //第一个字节
			s_flag = true;
			return true;
		}
		else if( uch >= 0xA1 )
		{
			s_tempChar[1] = (char)uch; //第二个字节
			s_flag = false;
			MultiByteToWideChar( 0, 0, s_tempChar, 2, s_tempWchar, 1); //转成宽字节
			s_tempWchar[1] = L'\0';
			CEGUI::utf32 code = (CEGUI::utf32)s_tempWchar[0];
			//Font* fnt = System::getSingleton().getDefaultFont();
			return CEGUI::System::getSingleton().injectChar( code );
		}
		else
		{
			return CEGUI::System::getSingleton().injectChar(code_point);
		}
	}
	else
	{
		s_flag = false;
		return CEGUI::System::getSingleton().injectChar(code_point);
	}
#else
	return CEGUI::System::getSingleton().injectChar(code_point );
#endif
}