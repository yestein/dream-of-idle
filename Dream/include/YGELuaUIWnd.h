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
	bool	Load				( void );				// ��������ļ�
	void	Reload				( void );				// ������������ļ�
	void	Hide				( void );				// ���ص�ǰ����
	void	Show				( void );				// ��ʾ��ǰ����
	bool	IsVisible			( void );				// ��ǰ�����Ƿ�ɼ�
	void	RegisterEvent		( const char* commentName, const char* EventName, const char* funName, int EventType = 1 ); //���¼�������
	void	RegisterFunction	( const char* funcName, const char* LuaFuncName , int input );			// ע�����ӿ�
	void	SetCommentPosition	( const char* commentName, float PositionX, float PositionY );	//���ÿؼ���λ��
	void	SetCommentWidth		( const char* commentName, float width );		// ���ÿؼ��Ŀ��
	void	SetCommentHeight	( const char* commentName, float height );	// ���ÿؼ��ĸ߶� 
	void	ShowComment			( const char* commentName );					// ��ʾ�ؼ�	
	void	HideComment			( const char* commentName );					// ���ؿؼ�
	bool	IsCommentShow		( const char* commentName );					// �ÿؼ��Ƿ�ɼ�
	float	GetCommentWidth		( const char* commentName );					// ��ȡ�ؼ����
	float	GetcommentHeight	( const char* commentName );					// ��ȡ�ؼ��߶�
	// �ṩ��������ýű��Ľӿ�

	void	CallLuaFunction		( std::string );				//�������Ƶ��ýű�����

private:

private:
	Window*		m_pRootWnd;
	Window*		m_pThisWnd;
	String		m_UIName;
	std::map<std::string, LuaFun> m_LuaFuncMap;
};
//------------------------------------------------------------------------
#endif