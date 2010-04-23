/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGEDirectX.cpp
	created:	2010/3/23
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	DirectX�ķ�װ( DDraw & D3D )
************************************************************************/
#include "YGEDirectX.h"

/************************************************************************
	Direct3D9                                                          
************************************************************************/
D3DLIGHT9 YGED3D::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_DIRECTIONAL;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Direction = *direction;

	return light;
}

D3DLIGHT9 YGED3D::InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_POINT;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Range        = 10000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

D3DLIGHT9 YGED3D::InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_SPOT;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Direction = *direction;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta        = 0.5f;
	light.Phi          = 0.7f;

	return light;
}

D3DMATERIAL9 YGED3D::InitMtrl(D3DXCOLOR a, D3DXCOLOR d,
							  D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power = p;
	return mtrl;
}

/************************************************************************
	DirectDraw7                                                          
************************************************************************/
YGEDDraw::YGEDDraw( ):
hWnd( NULL ),
bFullScr( TRUE ),
ScreenW( 640 ),
ScreenH( 480 ),
ScreenC( 16 ),
lpDD( NULL ),
lpDDSPrimary( NULL ),
lpDDSBack( NULL )

{

}

YGEDDraw::~YGEDDraw()
{
	if(lpDD!=NULL){
		if(lpDDSBack!=NULL){      //��ת������
			lpDDSBack->Release();  
			lpDDSBack = NULL;
		}
		if(lpDDSPrimary!=NULL){   ////������
			lpDDSPrimary->Release();
			lpDDSPrimary = NULL;
		}
		lpDD->Release();
		lpDD = NULL;
	}
}

BOOL YGEDDraw::InitDDraw( HWND hWd,bool bFScr,DWORD ScrW,DWORD ScrH,DWORD BitCount )
{
	hWnd = hWd;
	bFullScr=bFScr;
	if(bFScr)
	{
		//ȫ��ģʽ
		if(ScrW<=640)       { ScreenW=640;ScreenH=480;}
		else if(ScrW<=800)  { ScreenW=800;ScreenH=600;}
		else if(ScrW>800)   { ScreenW=1024;ScreenH=768;}
		else  { ScreenW=800;ScreenH=600;}

		if(BitCount<=8)    BitCount=8;
		else if(BitCount<=16)  BitCount=16;
		else if(BitCount<=24) BitCount=24;
		else if(BitCount<=32)  BitCount=32;
		else BitCount=16;

	}
	else
	{
		//����ģʽ
		ScreenW=ScrW;
		ScreenH=ScrH;
	}

	//��ʼ��DirectDraw����
	//HRESULT ��DirectDraw �������صı�׼���ͣ�����ɹ�����DD_OK��ʧ�ܷ��ش�����
	HRESULT ddrval;  ////����ָ��ĵ�ַ
	//����DirectDraw����
	/*������
	��һ��ȫ��Ψһ��־���ĵ�ַ������Ҫ��������������NULL������ǰ����ʾ��������
	�ڶ���������óɹ��򷵻���Ч��DirectDraw ����ָ��ĵ�ַ
	������Ϊ�߼�COM�����Ĳ�����һ������ΪNULL
	*/
	ddrval=DirectDrawCreateEx(NULL,(void**)&lpDD,IID_IDirectDraw7,NULL);
	if(FAILED(ddrval))
	{
		//������ʾģʽ����
		return FALSE;
	}

	//ȫ��ģʽ
	if(bFullScr)
	{
		//����Э���ȼ�
		/*������
		��һ�������ھ�������ڲ�����ָ��DDSCL_NORMAL��־ʱ������ΪNULL
		�ڶ�����ָ��Э���ȼ��ı�־DDSCL_FULLSCREEN:ȫ��ģʽ��־ DDSCL_EXCLUSIVE��ʹ�ö�ռģʽ
		DDSCL_ALLOWREBOOT��������ϼ�Ctrl+Alt+Del ��ȫ��ģʽ��������
		*/
		ddrval = lpDD->SetCooperativeLevel( hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT );
		if(FAILED(ddrval))
		{
			//����ģʽ����
			return FALSE;
		}

		//������ʾģʽ
		/*
		������
		��һ����Ҫ���÷ֱ��ʵĿ��   �ڶ�����Ҫ���÷ֱ��ʵĸ߶�  ����������ɫ��λ���
		���ĸ���Ҫ���õ�ˢ���ʵĴ�С��������NULL����ʾĬ��ˢ����  ������������ض�ģʽ�ı�־  �Զ���ΪNULL
		*/
		ddrval=lpDD->SetDisplayMode(ScreenW,ScreenH,ScreenC,NULL,DDSDM_STANDARDVGAMODE);
		if(FAILED(ddrval))
		{
			//������ʾģʽʧ��
			return FALSE;
		}

		//����������
		//DDSURFACEDUSC2:��DirectDraw ��������ݽṹ�����ĳ�ԱΪ��
		DDSURFACEDESC2 ddsd;
		/*
		������
		��һ����ָ����0������һ���ڴ�������׵�ַ
		�ڶ�����׼����0������һ���ڴ�����Ĵ�С�����ֽ�������
		*/
		ZeroMemory(&ddsd,sizeof(ddsd));
		ddsd.dwSize=sizeof(ddsd);
		/*
		���ã�ȷ����Щ��������Ч����
		DDSD_CAPS����ʾ�ṹ�е�ddsCaps ��Ա����Ч��
		DDSD_BACKBUFFERCOUNT����ʾҪ������̨�������
		*/
		ddsd.dwFlags=DDSD_CAPS|DDSD_BACKBUFFERCOUNT;
		/*
		DDSCAPS_PRIMARYSURFACE��Ҫ��������������
		DDSCAPS_FLIP��Ҫ�����ı�����ҳ�淭ת����һ����
		DDSCAPS_COMPLEX�����ӱ���
		*/
		ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE|DDSCAPS_FLIP|DDSCAPS_COMPLEX;
		//Ҫ�����ķ�ת�������еĺ�̨����ĸ���
		ddsd.dwBackBufferCount=1;
		/*
		����������һ������
		��һ���������������ݽṹ�ĵ�ַ
		�ڶ�����Ҫ�����ı���ָ���ַ
		���������ṩ��COM �ļ��ݣ�����ΪNULL
		*/
		ddrval=lpDD->CreateSurface(&ddsd,&lpDDSPrimary,NULL);
		if(ddrval!=DD_OK)
		{
			MessageBoxA(NULL," ","",MB_ICONHAND);
			//�������������
			return FALSE;
		}

		//������̨�������
		DDSCAPS2 ddscaps;
		ZeroMemory(&ddscaps,sizeof(ddscaps));
		ddscaps.dwCaps=DDSCAPS_BACKBUFFER;
		/*���ã���ȡ��̨�������
		��һ�������ݽṹ�ĵ�ַ
		�ڶ�����ָ��IDirectDrawSurface7�ӿڵ�ָ��ĵ�ַ
		*/
		ddrval=lpDDSPrimary->GetAttachedSurface(&ddscaps,&lpDDSBack);
		if(ddrval!=DD_OK)
		{
			MessageBoxA(NULL,"Failed"," ",MB_ICONHAND);
			//������̨�������ʧ��
			return FALSE;
		}
		return TRUE;
	}
	//����ģʽ
	else
	{
		//����Э���ȼ�
		//DDSCL_NORMAL:�ѱ�׼Windows Ӧ�ó�������
		ddrval=(HRESULT)lpDD->SetCooperativeLevel(hWnd,DDSCL_NORMAL);

		//����������
		DDSURFACEDESC2 ddsd;
		ZeroMemory(&ddsd,sizeof(ddsd));
		ddsd.dwSize=sizeof(ddsd);
		ddsd.dwFlags=DDSD_CAPS;  //��ʾddsCaps ��Ա����Ч��
		ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE;  //��ʾҪ��������������

		ddrval=lpDD->CreateSurface(&ddsd,&lpDDSPrimary,NULL);
		if(FAILED(ddrval))
		{
			//����ʧ��
			return FALSE;
		}

		//ʹ�òü���
		//		UseClipper();

		//������̨�������
		//		DDSURFACEDESC2 ddsd;
		ZeroMemory(&ddsd,sizeof(ddsd));
		ddsd.dwSize=sizeof(ddsd);
		//DDSD_CAPS:����ddsCaps��Ա����Ч�ġ�
		ddsd.dwFlags=DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
		//DDSCAPS_OFFSCREENPLAIN:����������档���ǲ���������ȷ�ת������صı��棬ͨ������λͼ�Ļ���
		ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;  //ʹ��ϵͳ�ڴ洴������
		ddsd.dwWidth=ScreenW;  //��ֱ���
		ddsd.dwHeight=ScreenH;  //�߷ֱ���

		//����һ��̨�������
		ddrval=lpDD->CreateSurface(&ddsd,&lpDDSBack,NULL);
		if(ddrval!=DD_OK)
		{
			//������̨�������ʧ��
			return FALSE;
		}
	}
	return TRUE;
}

#ifndef UNICODE
BOOL  YGEDDraw::CreateBMPSurface(   //����ָ���ı��棬����ָ����λͼ��ʽͼ������ոմ����ı���
							   LPDIRECTDRAWSURFACE7 &lpSurf,   //Ҫ����λͼ�ı���ָ��
							   LONG W,LONG H,    //�����ı���Ŀ�͸�
							   LPCSTR BitmapFile,   //ͼ���·��
							   DWORD MemoryFlag)   //ͼ��Ĵ洢��ʽ
#else
BOOL  YGEDDraw::CreateBMPSurface(   //����ָ���ı��棬����ָ����λͼ��ʽͼ������ոմ����ı���
								 LPDIRECTDRAWSURFACE7 &lpSurf,   //Ҫ����λͼ�ı���ָ��
								 LONG W,LONG H,    //�����ı���Ŀ�͸�
								 LPCWSTR BitmapFile,   //ͼ���·��
								 DWORD MemoryFlag)   //ͼ��Ĵ洢��ʽ
#endif
{
	HBITMAP  hbm;   //�豸���λͼ�ľ������Դ��ʶ��,��־һ��λͼ
	BITMAP   bm;    //ʵ������һ��λͼ��ʽ
	BOOL     bResult;

	//��λͼ��Ϊ�ļ�����ȡ
	/*������
	��һ����ͼ��ģ���ʵ��������OEMͼ������ΪNULL
	�ڶ�����ʵ��ΪNULL��ָ��ľ���ͼ����ļ���������ָ��ľ���ʵ��ģ���е���Դ��
	��������ָ����ת��ͼ�������
	���ģ������ָ��ͼ����߹��Ŀ�͸ߡ�������������Ϊ0�£�1�������ΪLR_DEFAULTSIZE,��ʾ����ϵͳĬ��
	��2���������ʾ������Դ��ֵ
	��������װ�����ͣ�LR_LOADFROMFILE�����ݵڶ���������ָ���ֵװ��ͼ��LR_CREATEDIBSECTION����ʾ�����豸�޹�������
	*/
	hbm=(HBITMAP)LoadImage(NULL,BitmapFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	if(hbm==NULL)
	{
		//����ͼ��ʧ��
		return FALSE;
	}

	//���Ҫ�����ı���Ŀ�͸�

	GetObject(hbm,sizeof(bm),&bm);  ////��ȡhbm ���λͼ��Ϣ��bm��
	W=(W==0 ? bm.bmWidth:W);
	H=(H==0 ? bm.bmHeight:H);

	//��������Ŀ�͸ߴ���һ���������
	bResult=CreateNULLSurface(lpSurf,W,H,DDSCAPS_SYSTEMMEMORY);

	if(bResult!=TRUE)
	{
		//��������ʧ��
		//��������Լ�¼����ʧ�ܵ���Ϣ
	}
	else if(BitmapFile!=NULL)
	{
		//��BitmapFileָ���ͼ���ļ����뵽Surf����
		bResult=LoadBMPSurface(lpSurf,BitmapFile);
	}

	DeleteObject(hbm);
	return bResult;
}

BOOL YGEDDraw::CreateNULLSurface(    //����ָ���ı��棬�ǿձ���
							   LPDIRECTDRAWSURFACE7 &lpSurf,   //Ҫ�����ı���ָ��
							   LONG W,LONG H,   //Ҫ�����ı���Ŀ����
							   DWORD MemoryFlag)   //����ͼ��Ĵ洢��ʽ
{
	DDSURFACEDESC2 ddsd;
	HRESULT  ddrval;

	//�����������Ҫ��
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize=sizeof(ddsd);
	ddsd.dwFlags=DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
	//DDSCAPS_OFFSCREENPLAIN:����������棬ͨ������λͼ�Ļ���
	ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN|MemoryFlag;
	ddsd.dwWidth=W;
	ddsd.dwHeight=H;

	//����һ�������
	/*������
	��һ�����������Խṹ�ĵ�ַ 
	�ڶ�����Ҫ�����ı���ָ��ĵ�ַ
	���������ṩ��COM �ļ��� ����ΪNULL
	*/
	ddrval=lpDD->CreateSurface(&ddsd,&lpSurf,NULL);
	if(ddrval!=DD_OK)
	{
		//�����������ʧ��
		return FALSE;
	}
	return TRUE;
}

#ifndef UNICODE
BOOL YGEDDraw::LoadBMPSurface(  //��BitmapFile ָ����λͼ��ʽͼ�����뵽�ո�ָ���ı���
							LPDIRECTDRAWSURFACE7 &lpSurf,  //Ҫ����ı����ָ��
							LPCSTR BitmapFile )   //ͼ���·��
#else
BOOL YGEDDraw::LoadBMPSurface(  //��BitmapFile ָ����λͼ��ʽͼ�����뵽�ո�ָ���ı���
							  LPDIRECTDRAWSURFACE7 &lpSurf,  //Ҫ����ı����ָ��
							  LPCWSTR BitmapFile )   //ͼ���·��
#endif
{
	HDC   hdcImage;
	HDC   hdc;
	HBITMAP  hbm;
	BITMAP   bm;
	HRESULT  ddrval;

	if(lpSurf==NULL)
		return FALSE;
	//��λͼ��Ϊ�ļ�����ȡ
	/*������
	��һ�������������װ��ͼ��ģ���ʵ������OEMͼ������ΪNULL��
	�ڶ���������ͼ��װ������OEM ͼ��ָ��ͼ����ļ���������ָ��ʵ��ģ�����Դ��
	��������װ��ͼ�������
	*/
	hbm=(HBITMAP)LoadImage(NULL,BitmapFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	if(hbm==NULL)
	{
		//����ͼ��ʧ��
		return FALSE;
	}

	//�������ܣ�����һ����ָ���豸���ݵ��ڴ��豸�����Ļ���(Device Context)
	//NULL������һ����Ӧ�ó���ĵ�ǰ��ʾ�����ݵ��ڴ��豸�����Ļ���
	hdcImage=CreateCompatibleDC(NULL);
	if(!hdcImage)
	{
		//�����豸�����Ļ���ʧ��
		return FALSE;
	}

	//ѡ��λͼ���󵽸ոմ������ڴ��豸�����Ļ�����DC��
	SelectObject(hdcImage,hbm);

	//��ȡλͼ�Ŀ�͸�
	GetObject(hbm,sizeof(bm),&bm);
	//��ȡ����Ŀ����
	DDSURFACEDESC2  ddsd;
	ddsd.dwSize=sizeof(ddsd);
	lpSurf->GetSurfaceDesc(&ddsd);  //��ñ����������Ϣ
	if(BitmapFile!=NULL)
	{
		if(ddrval=lpSurf->GetDC(&hdc)==DD_OK)
		{
			//��Դλͼ���Ƶ����棬���Խ������������
			/*������
			��1-5����Ŀ���豸��Ҫ���Ƶ���Ŀ���豸��λ��
			��6-10��Դ�豸��Ҫ���Ƶ�ԭ�豸λ��
			���ָ��������ʽ
			*/
			StretchBlt( hdc,
				0, 0, ddsd.dwWidth, ddsd.dwHeight,
				hdcImage,
				0, 0, bm.bmWidth, bm.bmHeight,
				SRCCOPY);
			lpSurf->ReleaseDC(hdc);
		}
	}
	//ɾ�������˵��豸������
	DeleteDC(hdcImage);

	if(ddrval!=DD_OK)
	{
		//���ƾ��ο�ʧ��
		return FALSE;
	}
	return TRUE;
}

HRESULT YGEDDraw::DDSetColorKey(  //������pdds����ָ���ı���Ĺؼ�ɫ
							  LPDIRECTDRAWSURFACE7 pdds,
							  COLORREF rgb)  //���rgb��ֵ��CLR_INVALID����ʹ�ñ�������Ͻǵ�������Ϊ�ؼ�ɫ
{
	DDCOLORKEY ddck;//��ɫ���Ľṹ��
	ddck.dwColorSpaceLowValue=DDColorMatch(pdds,rgb);
	ddck.dwColorSpaceHighValue=ddck.dwColorSpaceLowValue;
	return pdds->SetColorKey(DDCKEY_SRCBLT,&ddck);  //������ɫ��
}

DWORD YGEDDraw::DDColorMatch(  //�����rgbָ����ɫֵ����Ӧ��pdds���������ֵ
						   LPDIRECTDRAWSURFACE7 pdds,
						   COLORREF rgb) //���rgb��ֵ��CLR_INVALID����ʹ�ñ������Ͻǵ�������Ϊ�ؼ�ɫ
{
	if( pdds == NULL )
		return 0x00000000;

	COLORREF rgbT;
	HDC hdc;
	DWORD dw = CLR_INVALID;
	DDSURFACEDESC2 ddsd;  //DirectDrawҳ������
	HRESULT hres;

	//---------�����Ͻǵ����ɫ�滻ΪҪ���õ���ɫֵ
	if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
	{
		rgbT = GetPixel(hdc, 0, 0); //��ȡ���������������ɫ
		SetPixel(hdc, 0, 0, rgb);   //ѡ�еĵ��ϸı���ɫ
		pdds->ReleaseDC(hdc);
	}

	//---------��������ֱ�ӶԱ�����ж�����
	ddsd.dwSize = sizeof(ddsd);
	/*Lock:��������ֱ���޸�ҳ��
	��һ����ָ������Rect��ָ������ָ����������ҳ������������NULL����ʾ����ҳ��
	�ڶ�������ʾһ��DDSURFACEDESC�Ľṹ�ĵ�ַ���������ҳ��������Ϣ
	��������dwFlag
	���ĸ����涨ΪNULL
	DDLOCK_WAIT:��������̻߳�������ڽ���λת���������������������ڴ棬
	��һֱ�ȵ��ñ����������Ϊֹ�򷵻ش�����Ϣ��
	*/
	hres = pdds->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL); //��������
	if (hres == DD_OK)
	{
		/*
		��ȡ��һ��,�����Ͻǵ���ڱ������ݻ�����������ֵ
		���Ǳ������ɫ��ʽ���ܲ���32λ��ɫ���,���Ը���
		��ֵ������Ҫ���õ���ɫֵ�Ķ�Ӧ������
		*/
		dw  = *(DWORD *)ddsd.lpSurface;

		/*
		����������ɫ��ʽ���ܲ���32λ��ɫ���,��ֻ������ɫ
		��ʽ��Ӧ��λ�����磺���16λ��ȵľ�ֻҪ����dw��ǰ16
		λ��ֵ,�򷽷���dw & 0xffff�������8λ������dw & 0xff
		��32λ��ɫ��ȵĸ�ʽ,��ֵ�ʹ�����ɫֵ,���Բ��������
		*/
		if( ddsd.ddpfPixelFormat.dwRGBBitCount < 32 )
			dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1; 
		pdds->Unlock(NULL);
	}

	//---------�ָ������滻�����Ͻǵ����ɫֵ
	if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
	{
		SetPixel(hdc, 0, 0, rgbT);
		pdds->ReleaseDC(hdc);
	}

	return dw;
}

/************************************************************
* ������: Blit(...)
* ����  : ��ָ����Դ����ͼƬ���͵���̨����
*               (c)  mochsh, 2003
*************************************************************/
HRESULT YGEDDraw::BlitBack( LONG x,LONG y,
						 LPDIRECTDRAWSURFACE7 lpSurfSrc,
						 RECT * pRtSrc,
						 DWORD dwTrans )
{
	return Blit( lpDDSBack,x,y,lpSurfSrc,pRtSrc,dwTrans );
}

HRESULT YGEDDraw::Blit(   //��pRtSrcָ������Դ����ss�ϵ�ͼƬ���Ƶ�lpSurfDestָ����Ŀ�����
					 LPDIRECTDRAWSURFACE7 lpSurfDest,  //Ŀ�����ָ��
					 LONG x,LONG y,  //���Ƶ�Ŀ������λ��
					 LPDIRECTDRAWSURFACE7 lpSurfSrc,  //Դ�����ָ��
					 RECT * pRtSrc,  //Ҫ���Ƶ�Դ�����ͼƬλ�á�ֵΪNULL��ʾ��������
					 DWORD dwTrans )  //���͵ķ�ʽ
{
	HRESULT			ddrval;

	//------------------��鲢�޸�Դ���εĺ�����
	DDSURFACEDESC2	ddsdSrc;
	ddsdSrc.dwSize=sizeof(ddsdSrc);
	ddrval=lpSurfSrc->GetSurfaceDesc(&ddsdSrc);  //���Դ�������Ϣ
	if( ddrval == DD_OK && pRtSrc != NULL ) {
		LONG srcW = ddsdSrc.dwWidth;
		LONG srcH = ddsdSrc.dwHeight;
		if( srcH < pRtSrc->bottom )
			pRtSrc->bottom = srcH;
		if( srcH < pRtSrc->top )
			pRtSrc->top = srcH;
		if( srcW < pRtSrc->right )
			pRtSrc->right = srcW;
		if( srcW < pRtSrc->left )
			pRtSrc->left = srcW;
		if( pRtSrc->top < 0 )
			pRtSrc->top = 0;
		if( pRtSrc->bottom < 0 )
			pRtSrc->bottom = 0;
		if( pRtSrc->left < 0 )
			pRtSrc->left = 0;
		if( pRtSrc->right < 0 )
			pRtSrc->right = 0;
	}

	//------------------Դ���ΰ���Ŀ������С����
	DDSURFACEDESC2	ddsdDest;
	ddsdDest.dwSize=sizeof(ddsdDest);
	ddrval=lpSurfDest->GetSurfaceDesc(&ddsdDest);
	if( ddrval != DD_OK ) {
		//�޷�֪��Ŀ�����Ŀ����
		return ddrval;
	}
	else if(pRtSrc != NULL){
		LONG destW = ddsdDest.dwWidth;
		LONG destH = ddsdDest.dwHeight;
		if(x<0){//����Ŀ���������
			if((-x)>(pRtSrc->right-pRtSrc->left))
				return DD_FALSE;//��ȫ����Ŀ���������
			pRtSrc->left=pRtSrc->left-x;
			x=0;
		}
		if(x>(destW-(pRtSrc->right-pRtSrc->left)) ){
			//����Ŀ�������ұ�
			if(x>destW)
				return DD_FALSE;//��ȫ����Ŀ�������ұ�
			else
				pRtSrc->right=destW+pRtSrc->left-x;
		}
		if(y<0){//����Ŀ�������ϱ�
			if((-y)>(pRtSrc->bottom-pRtSrc->top))
				return DD_FALSE;//��ȫ����Ŀ�������ϱ�
			pRtSrc->top=pRtSrc->top-y;
			y=0;
		}
		if(y>(destH-(pRtSrc->bottom-pRtSrc->top)) ){
			//����Ŀ�����ĵױ�
			if(y>destH)
				return DD_FALSE;//��ȫ����Ŀ�����ĵױ�
			else
				pRtSrc->bottom=destH+pRtSrc->top-y;
		}
	}

	//-----------------λ�鴫��
	while( 1 )
	{
		if( pRtSrc != NULL )
			/*BltFase:λ�鴫�ͣ�
			��һ��������λ�鴫�͵�Ŀ������λ�ã�λ������Ͻǣ�
			��������Դ����ָ��
			���ĸ���Դ������νṹ��ָ��
			����������ͷ�ʽ��DDBLTFAST_SRCCOLORKEY����͸����λ�鴫�ͣ�ʹ��Դ����Ĺؼ�ɫ
			DDBLTFAST_DESTCOLORKEY����͸����λ�鴫�ͣ�ʹ��Ŀ��Ĺؼ�ɫ
			*/
			ddrval=lpSurfDest->BltFast(x,y,lpSurfSrc,pRtSrc,dwTrans);
		else {
			if(dwTrans == DDBLTFAST_SRCCOLORKEY || dwTrans == DDBLT_KEYSRC)
				/*Blt:����λ��
				��һ����Ҫ���͵���Ŀ�����ľ��νṹָ�롣����ΪNULL ��ʾ����ƽ��
				�ڶ�����Դ����ָ��
				��������Դ������νṹ��ָ�룬����ΪNULL ��ʾ���ƽ��
				���ĸ������͵ķ�ʽ
				�������DDBltFx�ṹ��ָ�룬�ýṹ������դ������������Ч��
				*/
				ddrval=lpSurfDest->Blt( NULL,lpSurfSrc,
				NULL,DDBLT_WAIT | DDBLT_KEYSRC,
				NULL);
			else if(dwTrans == DDBLTFAST_DESTCOLORKEY || dwTrans == DDBLT_KEYDEST)
				ddrval=lpSurfDest->Blt( NULL,lpSurfSrc,
				NULL,DDBLT_WAIT | DDBLT_KEYDEST,
				NULL);
			else
				ddrval=lpSurfDest->Blt( NULL,lpSurfSrc,
				NULL,DDBLT_WAIT,
				NULL);
		}
		if(	ddrval == DD_OK )
			return ddrval;
		else if( ddrval == DDERR_SURFACELOST ){
			ddrval = lpDDSBack->Restore();
			ddrval = lpDDSPrimary->Restore();
			if( ddrval != DD_OK )
				return ddrval;
		}
		else if( ddrval != DDERR_WASSTILLDRAWING )
			return ddrval;
	}

	return ddrval;
}

/********************************************************
*  ������:  GetRect(...)
*  ����:    ��ȡһ�����νṹ
*********************************************************/
RECT YGEDDraw::GetRect(LONG left,LONG top,LONG right,LONG bottom)
{
	RECT rect = {left,top,right,bottom};
	return rect;
}

/**************************************************
*  ������:  Flip(...)
*  ����:  ��ת����==>��ʾ
***************************************************/
void YGEDDraw::Flip( LPRECT pRectWin )
{
	HRESULT   ddrval=1;

	if( lpDDSPrimary && lpDDSBack )
	{
		//�������Ƿ�ʧ,��ʧ����DDERR_SURFACELOST
		if (lpDDSPrimary->IsLost()==DDERR_SURFACELOST)
			lpDDSPrimary->Restore();
		if (lpDDSBack->IsLost()==DDERR_SURFACELOST)
			lpDDSBack->Restore();
		do{
			if(bFullScr==1)
				ddrval = lpDDSPrimary->Flip( NULL, DDFLIP_WAIT );
			else
				ddrval = lpDDSPrimary->Blt( pRectWin,lpDDSBack,NULL,DDBLT_WAIT,NULL);

			//��ת��������Ϣ���
			if( ddrval == DD_OK )
				break;
			else if( ddrval == DDERR_SURFACELOST ){
				if( FAILED(lpDDSBack->Restore()) )
					break;
				if( FAILED(lpDDSPrimary->Restore()) )
					break;
			}
			else if( ddrval != DDERR_WASSTILLDRAWING )
				break;
		}while( 1 );
	}
}