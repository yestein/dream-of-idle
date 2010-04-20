/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGEDirectX.h
	created:	2010/3/19
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	DirectX的封装( DDraw & D3D )
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
	//变量的声明
protected:
	BOOL	bFullScr;//bFullScr值是1表示全屏模式;值为0表示窗口模式
	DWORD   ScreenW;//主表面的宽
	DWORD   ScreenH;//主表面的高
	DWORD   ScreenC;//颜色深度
	HWND	hWnd;

	LPDIRECTDRAW7         lpDD;//DirectDraw对象
	LPDIRECTDRAWSURFACE7  lpDDSPrimary;//主表面
	LPDIRECTDRAWSURFACE7  lpDDSBack;//翻转缓冲面

	//	void    CheckDisplayMode( void );

public:
	YGEDDraw();
	~YGEDDraw();

	//功能函数声明
	BOOL InitDDraw( HWND hWd,bool bFScr,DWORD ScrW,DWORD ScrH,DWORD BitCount) ;

	BOOL LoadBMPSurface(  //将BitmapFile 指定的位图格式图像载入到刚刚指定的表面
		LPDIRECTDRAWSURFACE7 &lpSurf,  //要载入的表面的指针
		LPCSTR BitmapFile );   //图像的路径

	BOOL CreateNULLSurface(    //创建指定的表面，是空表面
		LPDIRECTDRAWSURFACE7 &lpSurf,   //要创建的表面指针
		LONG W,LONG H,   //要创建的表面的宽与高
		DWORD MemoryFlag);   //表面图像的存储方式

	BOOL CreateBMPSurface(   //创建指定的表面，并将指定的位图格式图像载入刚刚创建的表面
		LPDIRECTDRAWSURFACE7 &lpSurf,   //要载入位图的表面指针
		LONG W,LONG H,    //创建的表面的宽和高
		LPCSTR BitmapFile,   //图像的路径
		DWORD MemoryFlag);    //图像的存储格式

	HRESULT Blit(   //将pRtSrc指定的在源表面ss上的图片复制到lpSurfDest指定的目标表面
		LPDIRECTDRAWSURFACE7 lpSurfDest,  //目标表面指针
		LONG x,LONG y,  //复制到目标表面的位置
		LPDIRECTDRAWSURFACE7 lpSurfSrc,  //源表面的指针
		RECT * pRtSrc,  //要复制的源表面的图片位置。值为NULL表示整个表面
		DWORD dwTrans );  //传送的方式

	HRESULT BlitBack(
		LONG x,LONG y,
		LPDIRECTDRAWSURFACE7 lpSurfSrc,
		RECT * pRtSrc,
		DWORD dwTrans );

	DWORD DDColorMatch(  //获得由rgb指定颜色值所对应的pdds表面的索引值
		LPDIRECTDRAWSURFACE7 pdds,
		COLORREF rgb); //如果rgb的值是CLR_INVALID，将使用表面左上角的像素作为关键色

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