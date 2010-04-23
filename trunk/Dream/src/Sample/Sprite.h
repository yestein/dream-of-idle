/************************************************************************
	filename: 	Sprite.h
	created:	2010/3/21
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)
	
	purpose:	Sprite API
************************************************************************/
#ifndef YGE_SPRITE_H
#define YGE_SPRITE_H
//---------------------------------------------------------------
#include "YGEDirectX.h"
#include "YGEWin32.h"

#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3

class Map
{
	HWND hWindow;
	int Width;
	int Height;
public:
	LPDIRECTDRAWSURFACE7 lpSMap;
	Map( );
	~Map(void)
	{
		if(lpSMap)
			lpSMap->Release();
	}
	void Initial(int W,int H)
	{
		Width = W;
		Height = H;
	}
	const int GetWidth()
	{
		return Width;
	}
	const int GetHeight()
	{
		return Height;
	}
};


class Sprite
{
	int Width;
	int Height;
	int dir;
	int _X;
	int _Y;
	int click_x;
	int click_y;
	HWND hWindow;
	bool Visible;
	bool pick;
	int *sequence;
	int seq_num;
	void Paint();
	void Clean();
	int current_frame;
	int next_frame;
	int seq[9];
public:
	LPDIRECTDRAWSURFACE7 lpSSprite;
	Sprite( );
	~Sprite(void){ }
	void Initial(int width,int height,int x,int y,int dir,int *sequence,int seq_num);
	void Play();
	void setPick(bool p)
	{
		pick = p;
	}
	void setVisible(bool v)
	{
		if(Visible!=v)
			Visible = v;
	}
	void setDir(int d)
	{
		if(dir!=d)
		{
			dir = d;
			current_frame = 0;
			next_frame=(current_frame+1)%seq_num;
		}
		else
		{
			current_frame=next_frame;
			next_frame=(current_frame+1)%seq_num;
		}
	}
	void setClick(int x,int y)
	{
		click_x = x-_X;click_y = y-_Y;
	}
	void setXY(int x,int y)
	{
		_X=x;_Y=y;
	}
	void Move(int dir,int pixel);
	bool CheckForEdge(int dir,int pixel,int H,int W);
	//	friend bool CheckForCollison(Sprite s1,Sprite s2);
	bool IsPick()
	{
		return pick;
	}
	bool IsVisible()
	{
		return Visible;
	}
	const int GetDir()
	{
		return dir;
	}
	const int GetX()
	{
		return _X;
	}
	const int GetY()
	{
		return _Y;
	}
	const int GetHeight()
	{
		return Height;
	}
	const int GetWidth()
	{
		return Width;
	}
	const int GetCurFram()
	{
		return sequence[current_frame];
	}
	const int GetClickX()
	{
		return click_x;
	}
	const int GetClickY()
	{
		return click_y;
	}
};
//--YGE_SPRITE_H-------------------------------------------------
#endif