/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGED3D9Renderer.cpp
	created:	2010/3/31
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	Create a Render by Direct3D 9
************************************************************************/
#include "YGED3D9Renderer.h"
#include "CEGUI.h"

YGED3D9Renderer::YGED3D9Renderer( ):
m_pDirect3D( NULL ),
m_pDirect3DDevice( NULL ),
m_DeviceType( D3DDEVTYPE_HAL ),
m_AdapterType( D3DADAPTER_DEFAULT )
{

}

bool YGED3D9Renderer::Initialise( )
{

	m_pDirect3D = Direct3DCreate9( D3D_SDK_VERSION );

	if( !m_pDirect3D )   
	{   
		::MessageBox( 0, YGED3D::CREATE_D3D_ERROR, 0, MB_ICONERROR|MB_OK );   
		return false;   
	}  

	// �������ʾ�豸��������D3DCAPS9�ṹ��
	D3DCAPS9 caps;
	m_pDirect3D->GetDeviceCaps(
		m_AdapterType, // ����ʾ�豸
		m_DeviceType, // �豸���ͣ�һ����D3DDEVTYPE_HAL.
		&caps); // ���������D3DCAPS9 �ṹ����������ʾ�豸������

	// �Ƿ����ʹ��Ӳ�����㴦��?
	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		// �ǣ�֧��Ӳ�����㴦��
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		// ����ֻ����������㴦��
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DDISPLAYMODE d3ddm;
	m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	D3DFORMAT format = d3ddm.Format;

	D3DPRESENT_PARAMETERS d3dParam;
	ZeroMemory( &d3dParam, sizeof( d3dParam ) );
	d3dParam.BackBufferWidth = m_uScreenWidth;
	d3dParam.BackBufferHeight = m_uScreenHeight;
	d3dParam.BackBufferFormat = format; //���ظ�ʽ
	d3dParam.BackBufferCount = 1;
	d3dParam.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dParam.MultiSampleQuality = 0;
	d3dParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dParam.hDeviceWindow = m_wndOwner;
	d3dParam.Windowed = m_bWindowed; 
	d3dParam.EnableAutoDepthStencil = true;
	d3dParam.AutoDepthStencilFormat = D3DFMT_D24S8; // depth format
	d3dParam.Flags = 0;
	d3dParam.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	int hr = m_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		m_DeviceType, // device type
		m_wndOwner, // window associated with device
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, // vertex processing type
		&d3dParam, // present parameters
		&m_pDirect3DDevice); // returned created device

	if( FAILED( hr ) )
	{
		::MessageBox( 0, YGED3D::CREATE_D3DDEVICE_ERROR, 0, MB_ICONERROR|MB_OK );
		return FALSE;
	}
	m_pCeguiD3D9Renderer = &CEGUI::Direct3D9Renderer::create( m_pDirect3DDevice );
	return TRUE;
}

void YGED3D9Renderer::Release( )
{
	if( m_pDirect3D )
	{
		m_pDirect3D->Release( );
	}
	if( m_pDirect3DDevice )
	{
		m_pDirect3DDevice->Release( );
	}
}
bool YGED3D9Renderer::DoRender( float timeElapse )
{
	if (FAILED(m_pDirect3DDevice->BeginScene()))
	{
		return false;
	}
	CEGUI::System& guiSystem = CEGUI::System::getSingleton();
	guiSystem.injectTimePulse( timeElapse );
	char fpsbuff[16];
	sprintf( fpsbuff, "FPS: %d", 50 );
	m_pDirect3DDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	guiSystem.renderGUI();

	// render FPS:
// 	CEGUI::Font* fnt = guiSystem.getDefaultFont();
// 	if (fnt)
// 	{
// 		guiSystem.getRenderer()->setQueueingEnabled(false);
// 		fnt->drawText(fpsbuff, CEGUI::Vector3(0, 0, 0), guiSystem.getRenderer()->getRect());
// 	}
	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present(0, 0, 0, 0);
	return true;
}
bool YGED3D9Renderer::BeginScene( )
{
	if (FAILED(m_pDirect3DDevice->BeginScene()))
	{
		return false;
	}
	return true;
}
void YGED3D9Renderer::EndScene( )
{

}

