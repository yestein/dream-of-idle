/************************************************************************
    Copyright (c) Yu Lei. All rights reserved. 

    filename: 	YGELuaWndMgr.h
    created:	2009-12-10 14:58 PM
    author:		Yu Lei(nl-nl-@163.com)
    <change list>
    1. create file (Yu Lei)

    purpose:GUI Window(created by Lua)Manager, Load Script, Connect CEGUI, 
************************************************************************/
#ifndef YGE_LUA_WND_MGR_H
#define YGE_LUA_WND_MGR_H
//------------------------------------------------------------------------
#include "CEGUI.h"
#include "YGELuaFunctor.h"

int  tolua_LuaGUI_open (lua_State* tolua_S);
#include "tolua++.h"
#include <map>

using namespace CEGUI;
//------------------------------------------------------------------------
class YGELuaUIWnd;

class YGELuaUIWndMgr
{
public:

public:
	YGELuaUIWndMgr( ):
	  d_state( NULL )
	{
		ms_Singleton = static_cast<YGELuaUIWndMgr*>( this );
		initialize( );
	}
	~YGELuaUIWndMgr( )
	{
		ms_Singleton = NULL;
	}
 	static YGELuaUIWndMgr& getSingleton	( void ) { return *ms_Singleton; }

	void			LoadScript		( const char* scriptPath );	
	void			RegisterEvent	( const char* commentName, const char* EventName, const char* funName, int EventType );	// 将Lua函数与事件绑定
	void			RegisterWnd		( std::string WndName, YGELuaUIWnd* Wnd );
	void			CoreDataChanged	( unsigned int uDataId, unsigned int uParam, int nParam );	//　handle Game CallBack
	void			Breathe			( void );
	Window*			GetRootWnd		( void ){ return m_RootWnd; }
	YGELuaUIWnd*	GetWndClass		( std::string WndName );
	lua_State*		GetLuaState		( void ){ return d_state; }

private:
	static YGELuaUIWndMgr*	ms_Singleton;
	Window*			m_RootWnd;
	lua_State*		d_state;
	std::map<std::string,YGELuaUIWnd* >		m_WndMap;

private:
	void initialize ( void );
};
//------------------------------------------------------------------------
#endif