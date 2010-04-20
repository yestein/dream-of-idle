/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 
	 
	filename: 	YGELuaUIWnd.cpp
	created:	2010-04-20 15:31 PM
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	GUI Window created by Lua Script
************************************************************************/

#include "YGELuaUIWnd.h"

//========================================
//	Register Event of Each Comment Action
//========================================
void YGELuaUIWnd::RegisterEvent( const char* commentName, const char* EventName, const char* funName, int EventType )
{
	YGELuaUIWndMgr::getSingleton( ).RegisterEvent( commentName, EventName, funName, EventType );
}
//========================================
//	Load a Window from file
//========================================
bool YGELuaUIWnd::Load( )
{
	if( m_UIName.empty( ) || !m_pRootWnd )
	{
		return false;
	}
	WindowManager& winMgr = WindowManager::getSingleton( );
	m_pThisWnd = winMgr.loadWindowLayout( m_UIName.c_str( ) );
	m_pRootWnd->addChildWindow( m_pThisWnd );
	YGELuaUIWndMgr::getSingleton( ).RegisterWnd( std::string( m_UIName.c_str( ) ), this );
	return true;
}
//========================================
//	Reload this Window from file
//========================================
void YGELuaUIWnd::Reload( )
{
	if( !m_pThisWnd || !m_pRootWnd)
		return;

	WindowManager& winMgr = WindowManager::getSingleton( );

	// 先将当前窗口从CEGUI系统中移除再重新加载
	m_pRootWnd->removeChildWindow( m_pThisWnd );
	winMgr.destroyWindow( m_pThisWnd );

	m_pThisWnd = winMgr.loadWindowLayout( m_UIName.c_str( ) );
	m_pRootWnd->addChildWindow( m_pThisWnd );
}
//========================================
//	Make a Window Visible
//========================================
void YGELuaUIWnd::Show( )
{
	if( !m_pThisWnd || !m_pRootWnd )
		return ;
	m_pRootWnd->addChildWindow( m_pThisWnd );
	m_pThisWnd->show( );

}
//========================================
//	Make a Window Invisible
//========================================
void YGELuaUIWnd::Hide( )
{
	if( !m_pThisWnd || !m_pRootWnd )
		return ;
	m_pRootWnd->removeChildWindow( m_pThisWnd );
	m_pThisWnd->hide( );
}
bool YGELuaUIWnd::IsVisible( )
{
	if( !m_pThisWnd )
	{
		return false;
	}
	return m_pThisWnd->isVisible( );
}

//==========================================================
//	Call Fucntion Defined in Lua
//==========================================================
void YGELuaUIWnd::CallLuaFunction( std::string funcName )
{
	if( m_LuaFuncMap.find( funcName) == m_LuaFuncMap.end( ) )
		return;
	lua_State* L = YGELuaUIWndMgr::getSingleton( ).GetLuaState( );
	lua_getglobal( L , m_LuaFuncMap[funcName].FuncName.c_str( ) );
	lua_pcall( L, 0, 0, 0 );
}
//==========================================================
//	Use for Register Lua Function
//==========================================================
void YGELuaUIWnd::RegisterFunction( const char* funcName, const char* LuaFunctionName, int input )
{
	std::string CFunName = std::string( funcName );
	std::string LuaFunName = std::string( LuaFunctionName );
	LuaFun LFun;
	LFun.FuncName = LuaFunName;
	LFun.input = input;
	m_LuaFuncMap[CFunName] = LFun;
}
//==========================================================
//	Functions used for Set Property of Comment
//==========================================================
void YGELuaUIWnd::ShowComment( const char* commentName )
{
	WindowManager& winMgr = WindowManager::getSingleton( );
	winMgr.getWindow( String( commentName ) )->setVisible( true );
}
void YGELuaUIWnd::HideComment( const char* commentName )
{
	WindowManager& winMgr = WindowManager::getSingleton( );
	winMgr.getWindow( String( commentName ) )->setVisible( false );
}
bool YGELuaUIWnd::IsCommentShow( const char* commentName )
{
	WindowManager& winMgr = WindowManager::getSingleton( );
	return winMgr.getWindow( String( commentName ) )->isVisible( );
}
void YGELuaUIWnd::SetCommentPosition( const char* commentName, float PositionX, float PositionY )
{

}
float YGELuaUIWnd::GetCommentWidth( const char* commentName )
{
	return 0;
}
void YGELuaUIWnd::SetCommentWidth( const char* commentName, float width )
{

}
float YGELuaUIWnd::GetcommentHeight( const char* commentName )
{
	return 0;
}
void YGELuaUIWnd::SetCommentHeight( const char* commentName, float height )
{

}