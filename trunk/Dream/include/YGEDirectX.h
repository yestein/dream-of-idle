/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGEDirectX.h
	created:	2010/3/19
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	DirectX�ķ�װ( DDraw & D3D )
************************************************************************/
#ifndef YGEDIRECTX_H
#define YGEDIRECTX_H
//------------------------------------------------------------------------
#include "YGEWin32.h"
#include <ddraw.h>
#pragma comment( lib,"ddraw.lib" )
#pragma comment( lib,"dxguid.lib" )

#include <d3dx9.h>
#include <limits>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

typedef struct IDirect3D9 *LPDIRECT3D9, *PDIRECT3D9;
typedef struct IDirect3DDevice9 *LPDIRECT3DDEVICE9, *PDIRECT3DDEVICE9;
//------------------------------------------------------------------------
namespace YGED3D
{
	//
	// Cleanup
	//

	template<class T> void Release(T t)
	{
		if( t )
		{
			t->Release();
			t = 0;
		}
	}

	template<class T> void Delete(T t)
	{
		if( t )
		{
			delete t;
			t = 0;
		}
	}

	/*************************************************************************
		Build Struct Function
	*************************************************************************/

	// Lights
	D3DLIGHT9 InitDirectionalLight	( D3DXVECTOR3* direction, D3DXCOLOR* color );
	D3DLIGHT9 InitPointLight		( D3DXVECTOR3* position, D3DXCOLOR* color );
	D3DLIGHT9 InitSpotLight			( D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color );

	// Materials
	D3DMATERIAL9 InitMtrl	( D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p );

	// Bounding Objects
	struct BoundingBox
	{
		BoundingBox( );

		bool isPointInside( D3DXVECTOR3& p );

		D3DXVECTOR3 _min;
		D3DXVECTOR3 _max;
	};

	struct BoundingSphere
	{
		BoundingSphere( );

		D3DXVECTOR3 _center;
		float       _radius;
	};

	// Randomness

	// Desc: Return random float in [lowBound, highBound] interval.
	float GetRandomFloat( float lowBound, float highBound );


	// Desc: Returns a random vector in the bounds specified by min and max.
	void GetRandomVector(
		D3DXVECTOR3* out,
		D3DXVECTOR3* min,
		D3DXVECTOR3* max );

	// Conversion

	DWORD FtoDw( float f );

	/*************************************************************************
		Constants
	*************************************************************************/

	const float INFINITY = std::numeric_limits<float>::infinity( );
	const float EPSILON  = 0.001f;

	// Colors

	const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(255, 255, 255) );
	const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) );
	const D3DXCOLOR        RED( D3DCOLOR_XRGB(255,   0,   0) );
	const D3DXCOLOR      GREEN( D3DCOLOR_XRGB(  0, 255,   0) );
	const D3DXCOLOR       BLUE( D3DCOLOR_XRGB(  0,   0, 255) );
	const D3DXCOLOR     YELLOW( D3DCOLOR_XRGB(255, 255,   0) );
	const D3DXCOLOR       CYAN( D3DCOLOR_XRGB(  0, 255, 255) );
	const D3DXCOLOR    MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );

	// Materials

	const D3DMATERIAL9 WHITE_MTRL  = InitMtrl( WHITE, WHITE, WHITE, BLACK, 2.0f );
	const D3DMATERIAL9 RED_MTRL    = InitMtrl( RED, RED, RED, BLACK, 2.0f );
	const D3DMATERIAL9 GREEN_MTRL  = InitMtrl( GREEN, GREEN, GREEN, BLACK, 2.0f );
	const D3DMATERIAL9 BLUE_MTRL   = InitMtrl( BLUE, BLUE, BLUE, BLACK, 2.0f );
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl( YELLOW, YELLOW, YELLOW, BLACK, 2.0f );

	const TCHAR CREATE_D3D_ERROR[]			= _TEXT("Failed to create main Direct3D object.");
	const TCHAR CREATE_D3DDEVICE_ERROR[]	= _TEXT("Failed to create Direct3D Device object.");

};

class YGEDDraw
{
	//����������
protected:
	BOOL	bFullScr;//bFullScrֵ��1��ʾȫ��ģʽ;ֵΪ0��ʾ����ģʽ
	DWORD   ScreenW;//������Ŀ�
	DWORD   ScreenH;//������ĸ�
	DWORD   ScreenC;//��ɫ���
	HWND	hWnd;

	LPDIRECTDRAW7         lpDD;//DirectDraw����
	LPDIRECTDRAWSURFACE7  lpDDSPrimary;//������
	LPDIRECTDRAWSURFACE7  lpDDSBack;//��ת������

	//	void    CheckDisplayMode( void );

public:
	YGEDDraw();
	~YGEDDraw();

	//���ܺ�������
	BOOL InitDDraw( HWND hWd,bool bFScr,DWORD ScrW,DWORD ScrH,DWORD BitCount) ;

	BOOL LoadBMPSurface(  //��BitmapFile ָ����λͼ��ʽͼ�����뵽�ո�ָ���ı���
		LPDIRECTDRAWSURFACE7 &lpSurf,  //Ҫ����ı����ָ��
		LPCSTR BitmapFile );   //ͼ���·��

	BOOL CreateNULLSurface(    //����ָ���ı��棬�ǿձ���
		LPDIRECTDRAWSURFACE7 &lpSurf,   //Ҫ�����ı���ָ��
		LONG W,LONG H,   //Ҫ�����ı���Ŀ����
		DWORD MemoryFlag);   //����ͼ��Ĵ洢��ʽ

	BOOL CreateBMPSurface(   //����ָ���ı��棬����ָ����λͼ��ʽͼ������ոմ����ı���
		LPDIRECTDRAWSURFACE7 &lpSurf,   //Ҫ����λͼ�ı���ָ��
		LONG W,LONG H,    //�����ı���Ŀ�͸�
		LPCSTR BitmapFile,   //ͼ���·��
		DWORD MemoryFlag);    //ͼ��Ĵ洢��ʽ

	HRESULT Blit(   //��pRtSrcָ������Դ����ss�ϵ�ͼƬ���Ƶ�lpSurfDestָ����Ŀ�����
		LPDIRECTDRAWSURFACE7 lpSurfDest,  //Ŀ�����ָ��
		LONG x,LONG y,  //���Ƶ�Ŀ������λ��
		LPDIRECTDRAWSURFACE7 lpSurfSrc,  //Դ�����ָ��
		RECT * pRtSrc,  //Ҫ���Ƶ�Դ�����ͼƬλ�á�ֵΪNULL��ʾ��������
		DWORD dwTrans );  //���͵ķ�ʽ

	HRESULT BlitBack(
		LONG x,LONG y,
		LPDIRECTDRAWSURFACE7 lpSurfSrc,
		RECT * pRtSrc,
		DWORD dwTrans );

	DWORD DDColorMatch(  //�����rgbָ����ɫֵ����Ӧ��pdds���������ֵ
		LPDIRECTDRAWSURFACE7 pdds,
		COLORREF rgb); //���rgb��ֵ��CLR_INVALID����ʹ�ñ������Ͻǵ�������Ϊ�ؼ�ɫ

	HRESULT DDSetColorKey(
		LPDIRECTDRAWSURFACE7 pdds,
		COLORREF rgb);

	void Flip( LPRECT pRectWin );

	RECT GetRect(
		LONG left,LONG top,
		LONG right,LONG bottom);
};
//------------------------------------------------------------------------
#endif