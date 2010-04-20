/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGELuaWnd.h
	created:	2010-04-20 15:31 PM
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	GUI Window created by Lua Script
************************************************************************/
#ifndef YGE_LUA_WND_H
#define YGE_LUA_WND_H

//------------------------------------------------------------------------
#include "YGELuaUIWndMgr.h"

using namespace CEGUI;
struct LuaFun
{
	std::string FuncName;
	int input;
};

class YGELuaUIWnd
{
public:

public:
	YGELuaUIWnd( ): m_pThisWnd(NULL), m_UIName("")
	{
		m_pRootWnd = YGELuaUIWndMgr::getSingleton( ).GetRootWnd( );
	}
	YGELuaUIWnd( const char* fileName ):m_pThisWnd(NULL), m_UIName(String( fileName ))
	{
		m_pRootWnd = YGELuaUIWndMgr::getSingleton( ).GetRootWnd( );
	}
	~YGELuaUIWnd( )
	{
		m_pThisWnd = NULL;
	}
	bool	Load				( void );				// 载入界面文件
	void	Reload				( void );				// 重新载入界面文件
	void	Hide				( void );				// 隐藏当前窗口
	void	Show				( void );				// 显示当前窗口
	bool	IsVisible			( void );				// 当前窗口是否可见
	void	RegisterEvent		( const char* commentName, const char* EventName, const char* funName, int EventType = 1 ); //绑定事件处理函数
	void	RegisterFunction	( const char* funcName, const char* LuaFuncName , int input );			// 注册程序接口
	void	SetCommentPosition	( const char* commentName, float PositionX, float PositionY );	//设置控件的位置
	void	SetCommentWidth		( const char* commentName, float width );		// 设置控件的宽度
	void	SetCommentHeight	( const char* commentName, float height );	// 设置控件的高度 
	void	ShowComment			( const char* commentName );					// 显示控件	
	void	HideComment			( const char* commentName );					// 隐藏控件
	bool	IsCommentShow		( const char* commentName );					// 该控件是否可见
	float	GetCommentWidth		( const char* commentName );					// 获取控件宽度
	float	GetcommentHeight	( const char* commentName );					// 获取控件高度
	// 提供给程序调用脚本的接口

	void	CallLuaFunction		( std::string );				//根据名称调用脚本函数

private:

private:
	Window*		m_pRootWnd;
	Window*		m_pThisWnd;
	String		m_UIName;
	std::map<std::string, LuaFun> m_LuaFuncMap;
};
//------------------------------------------------------------------------
#endif