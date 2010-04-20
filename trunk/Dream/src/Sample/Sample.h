/************************************************************************
filename: 	Sample.cpp
created:	2010/3/21
author:		Yulei

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

	virtual bool Init( );
	virtual bool Loop( );
	virtual bool Exit( );

public:

	bool DoRender( float timeElapse );

	unsigned	m_uLastGameTimeCount;
	unsigned	m_uLastRenderTimeCount;
	unsigned	m_uCurTimeCount;

private:

private:

};
#endif