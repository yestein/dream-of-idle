/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGEApplication.h
	created:	2010/3/23
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	Create a Render
************************************************************************/
#include "YGERenderer.h"
#include "YGEDefine.h"

YGERenderer::YGERenderer( ):
m_wndOwner( NULL ),
m_bWindowed( true ),
m_uScreenWidth( YGEDefine::DEFAULT_WND_WIDTH ),
m_uScreenHeight( YGEDefine::DEFAULT_WND_HEIGHT ),
m_uBitCount( 16 )
{
	
}