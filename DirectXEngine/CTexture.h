#pragma once

// Global Header Files.
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

namespace DirectXEngine
{
	class CTexture
	{
	private:
		LPDIRECT3DTEXTURE9 _texture;
		D3DXIMAGE_INFO _imageInfo;

	public:
		CTexture(void);
		~CTexture(void);

		// Function Declarations.
		bool Load(LPCWSTR);
		
		// Accessors.
		LPDIRECT3DTEXTURE9 GetTexture(void) { return this->_texture; }
		float GetWidth(void) { return (float)this->_imageInfo.Width; }
		float GetHeight(void) { return (float)this->_imageInfo.Height; }
	};
};