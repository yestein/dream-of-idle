/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGED3D9Renderer.h
	created:	2010/3/31
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	Create a Render by Direct3D 9 
************************************************************************/
#ifndef _YGE_D3D9_RENDER_H
#define _YGE_D3D9_RENDER_H
//------------------------------------------------------------------------
#include "YGERenderer.h"
#include "YGECEGUIAdapter.h"
#include "RendererModules/Direct3D9/CEGUIDirect3D9Renderer.h"
#include "CEGUIDefaultResourceProvider.h"
//------------------------------------------------------------------------
class YGED3D9Renderer: public YGERenderer
{
public:

	YGED3D9Renderer( );
	~YGED3D9Renderer( ){ };

	virtual bool Initialise	( void );
	virtual bool DoRender	( float timeElapse);
	virtual void Release	( void );
	virtual bool BeginScene	( void );
	virtual void EndScene	( void );

public:

	LPDIRECT3D9			m_pDirect3D;
	LPDIRECT3DDEVICE9	m_pDirect3DDevice;
	D3DDEVTYPE			m_DeviceType;
	unsigned int		m_AdapterType;
	CEGUI::Direct3D9Renderer* m_pCeguiD3D9Renderer;
	
private:
	
private:

};

//-------YGE_D3D9_RENDER_H-------------------------------------------
#endif