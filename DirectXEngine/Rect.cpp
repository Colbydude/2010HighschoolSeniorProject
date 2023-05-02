#include "Rect.h"

namespace DirectXEngine
{

    Rect::Rect()
    {
        left = top = right = bottom = 0;
    }

	Rect::Rect(int left,int top,int right,int bottom)
	{
		this->left = (double)left;
		this->top = (double)top;
		this->right = (double)right;
		this->bottom = (double)bottom;
	}

	Rect::Rect(double left,double top,double right,double bottom)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}

	bool Rect::isInside(D3DXVECTOR2 point)
	{
		return this->isInside(point.x, point.y);
	}

	bool Rect::isInside(int x,int y)
	{
		return this->isInside((double)x, (double)y);
	}

	bool Rect::isInside(double x,double y)
	{
		return (x > left && x < right && y > top && y < bottom);
	}

};
