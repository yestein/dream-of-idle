/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGEDirectX.cpp
	created:	2010/3/23
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose:	DirectX的封装( DDraw & D3D )
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
		if(lpDDSBack!=NULL){      //翻转缓冲面
			lpDDSBack->Release();  
			lpDDSBack = NULL;
		}
		if(lpDDSPrimary!=NULL){   ////主表面
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
		//全屏模式
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
		//窗口模式
		ScreenW=ScrW;
		ScreenH=ScrH;
	}

	//初始化DirectDraw环境
	//HRESULT 是DirectDraw 函数返回的标准类型，如果成功返回DD_OK，失败返回错误常量
	HRESULT ddrval;  ////对象指针的地址
	//创建DirectDraw对象
	/*参数：
	第一：全局唯一标志符的地址，代表将要创建的驱动程序，NULL：代表当前的显示驱动程序
	第二：如果调用成功则返回有效的DirectDraw 对象指针的地址
	第三：为高级COM保留的参数，一般设置为NULL
	*/
	ddrval=DirectDrawCreateEx(NULL,(void**)&lpDD,IID_IDirectDraw7,NULL);
	if(FAILED(ddrval))
	{
		//设置显示模式出错
		return FALSE;
	}

	//全屏模式
	if(bFullScr)
	{
		//设置协作等级
		/*参数：
		第一个：窗口句柄。当在参数中指定DDSCL_NORMAL标志时，可以为NULL
		第二个：指定协作等级的标志DDSCL_FULLSCREEN:全屏模式标志 DDSCL_EXCLUSIVE：使用独占模式
		DDSCL_ALLOWREBOOT：允许组合键Ctrl+Alt+Del 在全屏模式下起作用
		*/
		ddrval = lpDD->SetCooperativeLevel( hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT );
		if(FAILED(ddrval))
		{
			//设置模式出错
			return FALSE;
		}

		//设置显示模式
		/*
		参数：
		第一个：要设置分辨率的宽度   第二个：要设置分辨率的高度  第三个：颜色的位深度
		第四个：要设置的刷新率的大小，可以是NULL，表示默认刷新率  第五个：设置特定模式的标志  自定义为NULL
		*/
		ddrval=lpDD->SetDisplayMode(ScreenW,ScreenH,ScreenC,NULL,DDSDM_STANDARDVGAMODE);
		if(FAILED(ddrval))
		{
			//设置显示模式失败
			return FALSE;
		}

		//创建主表面
		//DDSURFACEDUSC2:是DirectDraw 表面的数据结构，它的成员为：
		DDSURFACEDESC2 ddsd;
		/*
		参数：
		第一个：指向用0来填充的一块内存区域的首地址
		第二个：准备用0来填充的一块内存区域的大小，按字节来计算
		*/
		ZeroMemory(&ddsd,sizeof(ddsd));
		ddsd.dwSize=sizeof(ddsd);
		/*
		作用：确定哪些程序是有效数据
		DDSD_CAPS：表示结构中的ddsCaps 成员是有效的
		DDSD_BACKBUFFERCOUNT：表示要创建后台缓冲表面
		*/
		ddsd.dwFlags=DDSD_CAPS|DDSD_BACKBUFFERCOUNT;
		/*
		DDSCAPS_PRIMARYSURFACE：要创建的是主表面
		DDSCAPS_FLIP：要创建的表面是页面翻转链的一部分
		DDSCAPS_COMPLEX：复杂表面
		*/
		ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE|DDSCAPS_FLIP|DDSCAPS_COMPLEX;
		//要创建的翻转表面链中的后台表面的个数
		ddsd.dwBackBufferCount=1;
		/*
		参数：创建一个表面
		第一个：表面属性数据结构的地址
		第二个：要创建的表面指针地址
		第三个：提供与COM 的兼容，设置为NULL
		*/
		ddrval=lpDD->CreateSurface(&ddsd,&lpDDSPrimary,NULL);
		if(ddrval!=DD_OK)
		{
			MessageBoxA(NULL," ","",MB_ICONHAND);
			//创建主表面出错
			return FALSE;
		}

		//创建后台缓冲表面
		DDSCAPS2 ddscaps;
		ZeroMemory(&ddscaps,sizeof(ddscaps));
		ddscaps.dwCaps=DDSCAPS_BACKBUFFER;
		/*作用：获取后台缓冲表面
		第一个：数据结构的地址
		第二个：指向IDirectDrawSurface7接口的指针的地址
		*/
		ddrval=lpDDSPrimary->GetAttachedSurface(&ddscaps,&lpDDSBack);
		if(ddrval!=DD_OK)
		{
			MessageBoxA(NULL,"Failed"," ",MB_ICONHAND);
			//创建后台缓冲表面失败
			return FALSE;
		}
		return TRUE;
	}
	//窗口模式
	else
	{
		//设置协作等级
		//DDSCL_NORMAL:已标准Windows 应用程序运行
		ddrval=(HRESULT)lpDD->SetCooperativeLevel(hWnd,DDSCL_NORMAL);

		//创建主表面
		DDSURFACEDESC2 ddsd;
		ZeroMemory(&ddsd,sizeof(ddsd));
		ddsd.dwSize=sizeof(ddsd);
		ddsd.dwFlags=DDSD_CAPS;  //表示ddsCaps 成员是有效的
		ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE;  //表示要创建的是主表面

		ddrval=lpDD->CreateSurface(&ddsd,&lpDDSPrimary,NULL);
		if(FAILED(ddrval))
		{
			//创建失败
			return FALSE;
		}

		//使用裁剪器
		//		UseClipper();

		//创建后台缓冲表面
		//		DDSURFACEDESC2 ddsd;
		ZeroMemory(&ddsd,sizeof(ddsd));
		ddsd.dwSize=sizeof(ddsd);
		//DDSD_CAPS:表明ddsCaps成员是有效的。
		ddsd.dwFlags=DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
		//DDSCAPS_OFFSCREENPLAIN:创建屏外表面。就是不与主表面等翻转表面相关的表面，通常用于位图的缓冲
		ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;  //使用系统内存创建表面
		ddsd.dwWidth=ScreenW;  //宽分辨率
		ddsd.dwHeight=ScreenH;  //高分辨率

		//创建一后台缓冲表面
		ddrval=lpDD->CreateSurface(&ddsd,&lpDDSBack,NULL);
		if(ddrval!=DD_OK)
		{
			//创建后台缓冲表面失败
			return FALSE;
		}
	}
	return TRUE;
}

#ifndef UNICODE
BOOL  YGEDDraw::CreateBMPSurface(   //创建指定的表面，并将指定的位图格式图像载入刚刚创建的表面
							   LPDIRECTDRAWSURFACE7 &lpSurf,   //要载入位图的表面指针
							   LONG W,LONG H,    //创建的表面的宽和高
							   LPCSTR BitmapFile,   //图像的路径
							   DWORD MemoryFlag)   //图像的存储格式
#else
BOOL  YGEDDraw::CreateBMPSurface(   //创建指定的表面，并将指定的位图格式图像载入刚刚创建的表面
								 LPDIRECTDRAWSURFACE7 &lpSurf,   //要载入位图的表面指针
								 LONG W,LONG H,    //创建的表面的宽和高
								 LPCWSTR BitmapFile,   //图像的路径
								 DWORD MemoryFlag)   //图像的存储格式
#endif
{
	HBITMAP  hbm;   //设备相关位图的句柄，资源标识符,标志一个位图
	BITMAP   bm;    //实例，是一种位图格式
	BOOL     bResult;

	//将位图作为文件来读取
	/*参数：
	第一个：图像模块的实例，如是OEM图像，设置为NULL
	第二个：实例为NULL，指向的就是图像的文件名，否则指向的就是实例模块中的资源名
	第三个：指定被转载图像的类型
	第四，五个：指定图标或者光标的宽和高。当这两个参数为0事（1）当最后为LR_DEFAULTSIZE,表示采用系统默认
	（2）：否则表示载入资源的值
	第六个：装载类型：LR_LOADFROMFILE：根据第二个参数的指向的值装载图像LR_CREATEDIBSECTION：表示载入设备无关型文章
	*/
	hbm=(HBITMAP)LoadImage(NULL,BitmapFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	if(hbm==NULL)
	{
		//载入图像失败
		return FALSE;
	}

	//求出要创建的表面的宽和高

	GetObject(hbm,sizeof(bm),&bm);  ////提取hbm 这个位图信息到bm中
	W=(W==0 ? bm.bmWidth:W);
	H=(H==0 ? bm.bmHeight:H);

	//根据上面的宽和高创建一个屏外表面
	bResult=CreateNULLSurface(lpSurf,W,H,DDSCAPS_SYSTEMMEMORY);

	if(bResult!=TRUE)
	{
		//创建表面失败
		//在这里可以记录创建失败的信息
	}
	else if(BitmapFile!=NULL)
	{
		//将BitmapFile指向的图像文件载入到Surf表面
		bResult=LoadBMPSurface(lpSurf,BitmapFile);
	}

	DeleteObject(hbm);
	return bResult;
}

BOOL YGEDDraw::CreateNULLSurface(    //创建指定的表面，是空表面
							   LPDIRECTDRAWSURFACE7 &lpSurf,   //要创建的表面指针
							   LONG W,LONG H,   //要创建的表面的宽与高
							   DWORD MemoryFlag)   //表面图像的存储方式
{
	DDSURFACEDESC2 ddsd;
	HRESULT  ddrval;

	//定义屏外表面要求
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize=sizeof(ddsd);
	ddsd.dwFlags=DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
	//DDSCAPS_OFFSCREENPLAIN:创建屏外表面，通常用于位图的缓冲
	ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN|MemoryFlag;
	ddsd.dwWidth=W;
	ddsd.dwHeight=H;

	//创建一屏外表面
	/*参数：
	第一个：表面属性结构的地址 
	第二个：要创建的表面指针的地址
	第三个：提供与COM 的兼容 设置为NULL
	*/
	ddrval=lpDD->CreateSurface(&ddsd,&lpSurf,NULL);
	if(ddrval!=DD_OK)
	{
		//创建屏外表面失败
		return FALSE;
	}
	return TRUE;
}

#ifndef UNICODE
BOOL YGEDDraw::LoadBMPSurface(  //将BitmapFile 指定的位图格式图像载入到刚刚指定的表面
							LPDIRECTDRAWSURFACE7 &lpSurf,  //要载入的表面的指针
							LPCSTR BitmapFile )   //图像的路径
#else
BOOL YGEDDraw::LoadBMPSurface(  //将BitmapFile 指定的位图格式图像载入到刚刚指定的表面
							  LPDIRECTDRAWSURFACE7 &lpSurf,  //要载入的表面的指针
							  LPCWSTR BitmapFile )   //图像的路径
#endif
{
	HDC   hdcImage;
	HDC   hdc;
	HBITMAP  hbm;
	BITMAP   bm;
	HRESULT  ddrval;

	if(lpSurf==NULL)
		return FALSE;
	//将位图作为文件来读取
	/*参数：
	第一个：处理包含被装载图像模块的实例如是OEM图像，设置为NULL，
	第二个：处理图像装载如是OEM 图像，指向图像的文件名，否则指向实例模块的资源名
	第三个：装载图像的类型
	*/
	hbm=(HBITMAP)LoadImage(NULL,BitmapFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	if(hbm==NULL)
	{
		//载入图像失败
		return FALSE;
	}

	//函数功能：创建一个与指定设备兼容的内存设备上下文环境(Device Context)
	//NULL：创建一个与应用程序的当前显示器兼容的内存设备上下文环境
	hdcImage=CreateCompatibleDC(NULL);
	if(!hdcImage)
	{
		//创建设备上下文环境失败
		return FALSE;
	}

	//选择位图对象到刚刚创建的内存设备上下文环境（DC）
	SelectObject(hdcImage,hbm);

	//获取位图的宽和高
	GetObject(hbm,sizeof(bm),&bm);
	//获取表面的宽与高
	DDSURFACEDESC2  ddsd;
	ddsd.dwSize=sizeof(ddsd);
	lpSurf->GetSurfaceDesc(&ddsd);  //获得表面的描述信息
	if(BitmapFile!=NULL)
	{
		if(ddrval=lpSurf->GetDC(&hdc)==DD_OK)
		{
			//将源位图复制到表面，可以进行拉伸或收缩
			/*参数：
			第1-5个：目标设备和要复制到的目标设备的位置
			第6-10：源设备和要复制的原设备位置
			最后：指定操作方式
			*/
			StretchBlt( hdc,
				0, 0, ddsd.dwWidth, ddsd.dwHeight,
				hdcImage,
				0, 0, bm.bmWidth, bm.bmHeight,
				SRCCOPY);
			lpSurf->ReleaseDC(hdc);
		}
	}
	//删除创建了的设备上下文
	DeleteDC(hdcImage);

	if(ddrval!=DD_OK)
	{
		//复制矩形快失败
		return FALSE;
	}
	return TRUE;
}

HRESULT YGEDDraw::DDSetColorKey(  //设置由pdds参数指定的表面的关键色
							  LPDIRECTDRAWSURFACE7 pdds,
							  COLORREF rgb)  //如果rgb的值是CLR_INVALID，将使用表面的左上角的像素作为关键色
{
	DDCOLORKEY ddck;//颜色键的结构体
	ddck.dwColorSpaceLowValue=DDColorMatch(pdds,rgb);
	ddck.dwColorSpaceHighValue=ddck.dwColorSpaceLowValue;
	return pdds->SetColorKey(DDCKEY_SRCBLT,&ddck);  //设置颜色键
}

DWORD YGEDDraw::DDColorMatch(  //获得由rgb指定颜色值所对应的pdds表面的索引值
						   LPDIRECTDRAWSURFACE7 pdds,
						   COLORREF rgb) //如果rgb的值是CLR_INVALID，将使用表面左上角的像素作为关键色
{
	if( pdds == NULL )
		return 0x00000000;

	COLORREF rgbT;
	HDC hdc;
	DWORD dw = CLR_INVALID;
	DDSURFACEDESC2 ddsd;  //DirectDraw页面描述
	HRESULT hres;

	//---------将左上角点的颜色替换为要设置的颜色值
	if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
	{
		rgbT = GetPixel(hdc, 0, 0); //获取鼠标点击处的像素颜色
		SetPixel(hdc, 0, 0, rgb);   //选中的点上改变颜色
		pdds->ReleaseDC(hdc);
	}

	//---------锁定表面直接对表面进行读操作
	ddsd.dwSize = sizeof(ddsd);
	/*Lock:允许我们直接修改页面
	第一个：指向摸个Rect的指针它将指定被锁定的页面区域，如设置NULL，表示整个页面
	第二个：表示一个DDSURFACEDESC的结构的地址，将被填充页面的相关信息
	第三个：dwFlag
	第四个：规定为NULL
	DDLOCK_WAIT:如果其它线程或进程正在进行位转换操作，不能锁定表面内存，
	则一直等到该表面可以锁定为止或返回错误信息。
	*/
	hres = pdds->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL); //锁定表面
	if (hres == DD_OK)
	{
		/*
		获取第一点,即左上角点的在表面数据缓冲区的索引值
		但是表面的颜色格式可能不是32位颜色深度,所以该索
		引值并不是要设置的颜色值的对应索引。
		*/
		dw  = *(DWORD *)ddsd.lpSurface;

		/*
		如果表面的颜色格式可能不是32位颜色深度,就只留下颜色
		格式对应的位数。如：如果16位深度的就只要保留dw的前16
		位的值,则方法是dw & 0xffff。如果是8位，则是dw & 0xff
		是32位颜色深度的格式,其值就代表颜色值,所以不用再求解
		*/
		if( ddsd.ddpfPixelFormat.dwRGBBitCount < 32 )
			dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1; 
		pdds->Unlock(NULL);
	}

	//---------恢复上面替换的左上角点的颜色值
	if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
	{
		SetPixel(hdc, 0, 0, rgbT);
		pdds->ReleaseDC(hdc);
	}

	return dw;
}

/************************************************************
* 函数名: Blit(...)
* 功能  : 将指定的源表面图片传送到后台表面
*               (c)  mochsh, 2003
*************************************************************/
HRESULT YGEDDraw::BlitBack( LONG x,LONG y,
						 LPDIRECTDRAWSURFACE7 lpSurfSrc,
						 RECT * pRtSrc,
						 DWORD dwTrans )
{
	return Blit( lpDDSBack,x,y,lpSurfSrc,pRtSrc,dwTrans );
}

HRESULT YGEDDraw::Blit(   //将pRtSrc指定的在源表面ss上的图片复制到lpSurfDest指定的目标表面
					 LPDIRECTDRAWSURFACE7 lpSurfDest,  //目标表面指针
					 LONG x,LONG y,  //复制到目标表面的位置
					 LPDIRECTDRAWSURFACE7 lpSurfSrc,  //源表面的指针
					 RECT * pRtSrc,  //要复制的源表面的图片位置。值为NULL表示整个表面
					 DWORD dwTrans )  //传送的方式
{
	HRESULT			ddrval;

	//------------------检查并修改源矩形的合理性
	DDSURFACEDESC2	ddsdSrc;
	ddsdSrc.dwSize=sizeof(ddsdSrc);
	ddrval=lpSurfSrc->GetSurfaceDesc(&ddsdSrc);  //获得源表面的信息
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

	//------------------源矩形按照目标表面大小调整
	DDSURFACEDESC2	ddsdDest;
	ddsdDest.dwSize=sizeof(ddsdDest);
	ddrval=lpSurfDest->GetSurfaceDesc(&ddsdDest);
	if( ddrval != DD_OK ) {
		//无法知道目标表面的宽与高
		return ddrval;
	}
	else if(pRtSrc != NULL){
		LONG destW = ddsdDest.dwWidth;
		LONG destH = ddsdDest.dwHeight;
		if(x<0){//超出目标表面的左边
			if((-x)>(pRtSrc->right-pRtSrc->left))
				return DD_FALSE;//完全超出目标表面的左边
			pRtSrc->left=pRtSrc->left-x;
			x=0;
		}
		if(x>(destW-(pRtSrc->right-pRtSrc->left)) ){
			//超出目标表面的右边
			if(x>destW)
				return DD_FALSE;//完全超出目标表面的右边
			else
				pRtSrc->right=destW+pRtSrc->left-x;
		}
		if(y<0){//超出目标表面的上边
			if((-y)>(pRtSrc->bottom-pRtSrc->top))
				return DD_FALSE;//完全超出目标表面的上边
			pRtSrc->top=pRtSrc->top-y;
			y=0;
		}
		if(y>(destH-(pRtSrc->bottom-pRtSrc->top)) ){
			//超出目标表面的底边
			if(y>destH)
				return DD_FALSE;//完全超出目标表面的底边
			else
				pRtSrc->bottom=destH+pRtSrc->top-y;
		}
	}

	//-----------------位块传送
	while( 1 )
	{
		if( pRtSrc != NULL )
			/*BltFase:位块传送：
			第一，二个：位块传送到目标表面的位置（位块的左上角）
			第三个：源表面指针
			第四个：源表面矩形结构的指针
			第五个：传送方式：DDBLTFAST_SRCCOLORKEY：有透明的位块传送，使用源表面的关键色
			DDBLTFAST_DESTCOLORKEY：有透明的位块传送，使用目标的关键色
			*/
			ddrval=lpSurfDest->BltFast(x,y,lpSurfSrc,pRtSrc,dwTrans);
		else {
			if(dwTrans == DDBLTFAST_SRCCOLORKEY || dwTrans == DDBLT_KEYSRC)
				/*Blt:传送位块
				第一个：要传送到的目标表面的矩形结构指针。设置为NULL 表示整个平面
				第二个：源表面指针
				第三个：源表面矩形结构的指针，设置为NULL 表示真个平面
				第四个：传送的方式
				第五个：DDBltFx结构的指针，该结构包含光栅操作及其他的效果
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
*  函数名:  GetRect(...)
*  功能:    获取一个矩形结构
*********************************************************/
RECT YGEDDraw::GetRect(LONG left,LONG top,LONG right,LONG bottom)
{
	RECT rect = {left,top,right,bottom};
	return rect;
}

/**************************************************
*  函数名:  Flip(...)
*  功能:  翻转表面==>显示
***************************************************/
void YGEDDraw::Flip( LPRECT pRectWin )
{
	HRESULT   ddrval=1;

	if( lpDDSPrimary && lpDDSBack )
	{
		//检查表面是否丢失,丢失返回DDERR_SURFACELOST
		if (lpDDSPrimary->IsLost()==DDERR_SURFACELOST)
			lpDDSPrimary->Restore();
		if (lpDDSBack->IsLost()==DDERR_SURFACELOST)
			lpDDSBack->Restore();
		do{
			if(bFullScr==1)
				ddrval = lpDDSPrimary->Flip( NULL, DDFLIP_WAIT );
			else
				ddrval = lpDDSPrimary->Blt( pRectWin,lpDDSBack,NULL,DDBLT_WAIT,NULL);

			//翻转表面后的信息检测
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