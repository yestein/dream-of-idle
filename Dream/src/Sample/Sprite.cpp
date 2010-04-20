#include "Sprite.h"

Sprite::Sprite( )
{
	for( int i =0 ; i < 9; i++ )
	{
		seq[i] = i;
	}
	Initial(65,94,50,50,DOWN,seq,4);
}
Map::Map( )
{
	Initial( 640 , 480 );
}
void Sprite::Initial(int width,int height,int x,int y,int d,int *seq,int n)
{
	_X = x;_Y = y;
	Width = width;Height = height;
	dir = d;
	sequence = seq;
	seq_num = n;
	current_frame=0;
	next_frame=(current_frame+1)%seq_num;
	Visible = true;
	pick = false;
}
void Sprite::Play()
{
	/*
	Paint();
	currTime = timeGetTime();
	while((currTime - lastTime)<fps)
	{
	currTime = timeGetTime();
	}
	Clean();
	current_frame=next_frame;
	next_frame=(current_frame+1)%seq_num;
	lastTime = lastTime + fps;
	*/


}
void Sprite::Paint()
{

}
void Sprite::Clean()
{

}

void Sprite::Move(int dir,int pixel)
{
	switch(dir)
	{
	case UP:
		_Y -= pixel;
		break;
	case DOWN:
		_Y += pixel;
		break;
	case RIGHT:
		_X += pixel;
		break;
	case LEFT:
		_X -= pixel;
		break;
	}
}
bool Sprite::CheckForEdge(int dir,int pixel,int H,int W)
{
	switch(dir)
	{
	case UP:
		if(_Y-pixel>=0)
			return true;
		else
			return false;
	case DOWN:
		if(_Y+Height+pixel<=H)
			return true;
		else 
			return false;
	case LEFT:
		if(_X-pixel>=0)
			return true;
		else
			return false;
	case RIGHT:
		if(_X+Width+pixel<=W)
			return true;
		else 
			return false;
	}
	return false;
}
