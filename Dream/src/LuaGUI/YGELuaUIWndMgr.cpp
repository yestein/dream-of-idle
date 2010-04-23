/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGELuaWndMgr.cpp
	created:	2009-12-10 14:58 PM
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	GUI Window created by Lua Script
************************************************************************/

#include "YGELuaUIWndMgr.h"
#include "YGEWin32.h"
using namespace CEGUI;
/*************************************************************************
	Static Data Definitions
*************************************************************************/

YGELuaUIWndMgr* YGELuaUIWndMgr::ms_Singleton = NULL;

//========================================
//	KLuaUI��CEGUI�ĳ�ʼ������
//========================================
void YGELuaUIWndMgr::initialize( void )
{
	using namespace CEGUI;

	WindowManager& winMgr = WindowManager::getSingleton( );
	SchemeManager::getSingleton( ).create("TaharezLook.scheme");
	System::getSingleton( ).setDefaultMouseCursor("TaharezLook", "MouseArrow");
	FontManager::getSingleton( ).create("msyhbd.font");
	CEGUI::System::getSingleton( ).setDefaultFont( "msyhbd");
	m_RootWnd = winMgr.createWindow("DefaultWindow", "root" );
	CEGUI::System::getSingleton( ).setGUISheet( m_RootWnd );
}
//========================================
//	KLuaUI����ȡ�ű��ļ�
//========================================
void YGELuaUIWndMgr::LoadScript( const char* scriptPath )
{
	if( d_state != NULL )
		lua_close( d_state );
	d_state = luaL_newstate();    
	luaopen_base(d_state);     
	tolua_LuaGUI_open(d_state);    
	luaL_dofile( d_state, scriptPath );
}
//========================================
//	KLuaUI����CEGUIע��lua�¼�������
//========================================
void YGELuaUIWndMgr::RegisterEvent( const char* commentName, const char* EventName, const char* funName, int EventType )
{
	WindowManager& winMgr = WindowManager::getSingleton( );
	Window* comment = winMgr.getWindow( String( commentName ) );
	YGELuaFunctor functor( d_state, String( funName ), LUA_NOREF, EventType );
	comment->subscribeEvent( String( EventName ), Event::Subscriber(functor) );
}
//=========================================================
//	KLuaUI�����ű�������LuaWnd��ע�ᵽKLuaUI�෽�����
//=========================================================
void YGELuaUIWndMgr::RegisterWnd( std::string WndName, YGELuaUIWnd* Wnd )
{
	m_WndMap[WndName] = Wnd;
}
//=========================================================
//	KLuaUI����ȡ�ɽű���������ָ��
//=========================================================
YGELuaUIWnd* YGELuaUIWndMgr::GetWndClass( std::string WndName )
{
	if ( m_WndMap.find( WndName ) != m_WndMap.end( ) )
	{
		return m_WndMap[WndName];
	}
	return NULL;
}
//=========================================================
//	KLuaUI�������߼��ص����������ݶ�ȡ�ű���ĺ���
//=========================================================
void YGELuaUIWndMgr::CoreDataChanged( unsigned int uDataId, unsigned int uParam, int nParam )
{
	lua_getglobal( d_state, "CoreDataChanged" );
	lua_pushinteger( d_state, uDataId );
	lua_pushinteger( d_state, uParam );
	lua_pushinteger( d_state, nParam );
	lua_pcall( d_state, 3, 0, 0 );
}