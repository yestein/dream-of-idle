/************************************************************************
	filename: 	Sample.cpp
	created:	2010/3/21
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)


	purpose:	Create First Win32 Window
************************************************************************/
//------------------------------------------------------------------------
#ifndef YGE_HELLOWORLD_H
#define YGE_HELLOWORLD_H
//------------------------------------------------------------------------
#include "YGEAppFrame.h"

class YGEGame : public YGEApplication
{
public:
	YGEGame( );
	~YGEGame( ){ }

	virtual int		HandleInput( UINT Message,WPARAM wParam,LPARAM lParam );
	virtual bool	Init( );
	virtual bool	Loop( );
	virtual bool	Exit( );

public:

	bool DoRender( float timeElapse );

	unsigned	m_uLastGameTimeCount;
	unsigned	m_uLastRenderTimeCount;
	unsigned	m_uCurTimeCount;

private:

private:

};
#endif