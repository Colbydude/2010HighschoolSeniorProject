#include "CTexture.h"
#include "CGameEngine.h"

namespace DirectXEngine
{
	CTexture::CTexture(void)
		: _texture(NULL)
	{
	}

	CTexture::~CTexture(void)
	{
		if(this->_texture != NULL)
			this->_texture->Release();
	}

	bool CTexture::Load(LPCWSTR fileName)
	{
		if (FAILED(D3DXGetImageInfoFromFile(fileName, &_imageInfo)))
		{
			this->_texture = NULL;
			return false;
		}

		if (FAILED(D3DXCreateTextureFromFileEx(CGameEngine::Instance()->GetDevice(),
			fileName, 											// File Name
			this->_imageInfo.Width, this->_imageInfo.Height, 1,	// Width, Height, and MIP Level Count
			D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,	// Usage method, Format, and Pool
			D3DX_DEFAULT, D3DX_DEFAULT,							// Image and MIP Filters
			D3DCOLOR_XRGB(255, 0, 255),							// Transparency Key (Magenta)
			&this->_imageInfo, NULL, &this->_texture			// Image information structure, color pallete, and destination texture
			)))
		{
			this->_texture = NULL;
			return false;
		}

		return true;
	}
};