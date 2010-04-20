/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGERender.h
	created:	2010/3/23
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	Create a Render
************************************************************************/
#ifndef YGE_RENDER_H
#define YGE_RENDER_H
//-----------------------------------------------------------------------
#include "YGEDirectX.h"
//------------------------------------------------------------------------
class YGERenderer
{
public:
	
	YGERenderer( );
	~YGERenderer( ){ }
	
	virtual bool Initialise( void ) = 0;
	virtual bool DoRender( float timeElapse ) = 0;
	virtual void Release( void ) = 0;
	virtual bool BeginScene( void ) = 0;
	virtual void EndScene( void ) = 0;

	HWND	GetWndOwner	( void ){ return m_wndOwner; }
	bool	IsWindowed	( void ){ return m_bWindowed; }

	unsigned int GetScreenWidth	( void ){ return m_uScreenWidth; }
	unsigned int GetScreenHeight( void ){ return m_uScreenHeight; }
	unsigned int GetBitCount	( void ){ return m_uBitCount; }

	void	SetWndOwner		( HWND hwnd ){ m_wndOwner = hwnd; }
	void	SetWindowed		( bool windowed ){ m_bWindowed = windowed; }
	void	SetScreenWidth	( unsigned int width ){ m_uScreenWidth = width; }
	void	SetScreenHeight	( unsigned int height ){ m_uScreenHeight = height; }
	void	SetBitCount		( unsigned int bitCount ){ m_uBitCount = bitCount; }



protected:

	HWND			m_wndOwner;
	bool			m_bWindowed;
	unsigned int	m_uScreenWidth;
	unsigned int	m_uScreenHeight;
	unsigned int	m_uBitCount;


private:

private:


};
//------YGE_RENDER_H-----------------------------------------------------
#endif