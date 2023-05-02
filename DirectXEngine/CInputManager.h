#pragma once

// Global Header Files.
#define DIRECTINPUT_VERSION 0x0800
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

// Local Header Files.
#include "CGameEngine.h"
#include "CKeyboardState.h"

namespace DirectXEngine
{
	class CInputManager
	{
		private:
			// Constructor & Destructor.
			CInputManager(void);
			CInputManager(CInputManager const&) { }
			~CInputManager(void);

			static CInputManager* _instance;

			// DirectInput Devices.
			LPDIRECTINPUT8			_device;	// Core DirectInput Object
			LPDIRECTINPUTDEVICE8	_keyboard;	// Keyboard

			// Keyboard-related Variables.
			CKeyboardState* _preKeyboardState;
			CKeyboardState* _curKeyboardState;

			// Device Initialization.
			bool initKeyboard(void);

		public:
			// Singleton.
			static CInputManager* Instance(void) { return _instance; }

			// Public Functions.
			bool Init(void);
			void Update(void);

			// Keyboard Functions.
			bool IsKeyDown(int);
			bool IsKeyUp(int);
			bool WasKeyPressed(int);
			bool WasKeyReleased(int);

			// Accessors & Mutators.
			LPDIRECTINPUT8 GetDevice(void) { return this->_device; }
			CKeyboardState* GetCurKeyboardState(void) { return this->_curKeyboardState; }
			CKeyboardState* GetPreKeyboardState(void) { return this->_preKeyboardState; }
	};
};