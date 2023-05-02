#pragma once

// Global Header Files.
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// Local Header Files.
#include "CGameTimer.h"
#include "CSceneObject.h"
#include "CGameSprite.h"
#include "Game.h"
#include "Megaman.h"

namespace DirectXEngine
{
	class CGameEngine
	{
	private:
		// Constructors & Destructor.
		CGameEngine(void);
		CGameEngine(CGameEngine const&) { };
		virtual ~CGameEngine(void);

		static CGameEngine* _instance;

		HWND	_windowHandle;

		LPDIRECT3D9			_d3d;
		LPDIRECT3DDEVICE9	_device;
		LPD3DXSPRITE 		_spriteHandler;

		LPCWSTR	_windowTitle;
		int		_screenWidth, _screenHeight, _colorDepth;

		const static D3DCOLOR _ambientColor;

		CGameTimer*	_gameTimer;
		bool		_gameRunning;

	public:
		static CGameEngine* Instance(void) { return _instance; }

		bool Init(int, int, int);
		void End(void);
		void Update(void);
		void BeginRender(void);
		void EndRender(void);

		LPDIRECT3DDEVICE9 GetDevice(void) { return this->_device; }
		LPD3DXSPRITE GetSpriteHandler(void) { return this->_spriteHandler; }
		HWND GetWindowHandle(void) { return this->_windowHandle; }
		LPCWSTR GetWindowTitle(void) { return this->_windowTitle; }
		int GetScreenWidth(void) { return this->_screenWidth; }
		int GetScreenHeight(void) { return this->_screenHeight; }
		int GetColorDepth(void) { return this->_colorDepth; }
		bool GetGameRunning(void) { return this->_gameRunning; }
		CGameTimer* GetGameTimer(void) { return this->_gameTimer; }

		void SetWindowHandle(HWND val) { this->_windowHandle = val; }
		void SetWindowTitle(LPCWSTR);
		void SetScreenWidth(int val) { this->_screenWidth = val; }
		void SetScreenHeight(int val) { this->_screenHeight = val; }
		void SetColorDepth(int val) { this->_colorDepth = val; }
		void SetGameRunning(bool val) { this->_gameRunning = val; }
	};
};