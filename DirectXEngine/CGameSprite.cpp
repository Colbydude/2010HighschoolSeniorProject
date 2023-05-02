#include "CGameSprite.h"
#include "CGameEngine.h"

namespace DirectXEngine
{
	CGameSprite::CGameSprite(void)
		: _texture(NULL), _visible(true)
	{
		this->framewidth = 0;
		this->frameheight = 0;
		this->totalframes = 1;
		this->curframe = 0;
		this->animdir = 1;
		this->animcolumns = 1;
		this->framestart = 0;
		this->frametimer = 160;
		this->animstartx = 0;
		this->animstarty = 0;
	}

	CGameSprite::~CGameSprite(void)
	{
		if (this->_texture != NULL)
			delete this->_texture;
	}

	void CGameSprite::transform(void)
	{
		D3DXMATRIX mat;

		D3DXMatrixTransformation2D(&mat, NULL, 0,
			&this->GetScale(), &this->GetCenter(), this->GetRotation(), &this->GetPosition());

		CGameEngine::Instance()->GetSpriteHandler()->SetTransform(&mat);
	}

	bool CGameSprite::Load(LPCWSTR fileName)
	{
		if (this->_texture != NULL)
			delete this->_texture;

		this->_texture = new CTexture();
		if (this->_texture->Load(fileName))
		{
			this->SetSize(D3DXVECTOR2(this->_texture->GetWidth(), this->_texture->GetHeight()));
			return true;
		}
		else
			return false;
	}

	void CGameSprite::Render(float)
	{
		// Calculate source frame location.
		int fx = (this->curframe % this->animcolumns) * this->framewidth;
		int fy = (this->curframe / this->animcolumns) * this->frameheight;
		RECT srcRect = { fx, fy, fx + this->framewidth, fy + this->frameheight };
		this->transform();
		if (this->_texture != NULL && this->_visible)
			CGameEngine::Instance()->GetSpriteHandler()->Draw(this->_texture->GetTexture(), &srcRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}

	void CGameSprite::Animate()
	{
		// Update frame based on animdir.
		if (frametimer > 0)
		{
			if (timeGetTime() > (DWORD)(framestart + frametimer))
			{
				// Reset animation timer.
				framestart = timeGetTime();
				curframe += animdir;
				// Keep frame within bounds.
				if (curframe < 0)
					curframe = totalframes-1;
				if (curframe > totalframes-1)
					curframe = 0;
			}
		}
		else
		{
			// No animation timer- -update at cpu clock speed.
			curframe += animdir;
			if (curframe < 0)
				curframe = totalframes - 1;
			if (curframe > totalframes-1)
				curframe = 0;
		}
	}
};