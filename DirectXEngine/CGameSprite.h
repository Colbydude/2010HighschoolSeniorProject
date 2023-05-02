#pragma once

// Global Header Files.
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

// Local Header Files.
#include "CSceneObject.h"
#include "CTexture.h"

namespace DirectXEngine
{
	class CGameSprite : public CSceneObject
	{
	private:
		// Texture Data.
		CTexture* _texture;
		bool _visible;
		D3DXMATRIX _matRotate, _matScale;

		// Animation Data.
		int animcolumns;
		int framewidth, frameheight;
		int framestart, frametimer;
		int curframe, totalframes, animdir;
		int animstartx, animstarty;

		// Function Declarations.
		void transform(void);

	public:
		// Constructor & Destructor.
		CGameSprite(void);
		~CGameSprite(void);

		// Function Declarations.
		bool Load(LPCWSTR);
		void Render(float);
		void Animate();

		// Accessors & Mutators.
		CTexture* GetTexture(void) { return this->_texture; }
		void SetTexture(CTexture* val) { this->_texture = val; }
		int GetColumns() { return animcolumns; }
		void SetColumns(int value) { animcolumns = value; }
		int GetFrameTimer() { return frametimer; }
		void SetFrameTimer(int value) { frametimer = value; }
		int GetFrameWidth() { return framewidth; }
		void SetFrameWidth(int value) { framewidth = value; }
		int GetFrameHeight() { return frameheight; }
		void SetFrameHeight(int value) { frameheight = value; }
		int GetCurrentFrame() { return curframe; }
		void SetCurrentFrame(int value) { curframe = value; }
		int GetTotalFrames() { return totalframes; }
		void SetTotalFrames(int value) { totalframes = value; }
		int GetAnimationDirection() { return animdir; }
		void SetAnimationDirection(int value) { animdir = value; }

		bool IsVisible(void) { return this->_visible; }
		void SetVisible(bool val) { this->_visible = val; }
	};
};