#include "CInputManager.h"
#include "CKeyboardState.h"

namespace DirectXEngine
{
	CInputManager* CInputManager::_instance = new CInputManager();

	CInputManager::CInputManager(void)
		: _device(NULL), _keyboard(NULL),
		_curKeyboardState(NULL), _preKeyboardState(NULL)
	{
	}

	CInputManager::~CInputManager(void)
	{
		if (this->_keyboard != NULL)
		{
			this->_keyboard->Unacquire();
			this->_keyboard->Release();
			this->_keyboard = NULL;
		}

		if (this->_device != NULL)
		{
			this->_device->Release();
			this->_device = NULL;
		}
	}

	bool CInputManager::Init(void)
	{
		// Initialize the DirectInput Device.
		if (FAILED(DirectInput8Create(GetModuleHandle(NULL),// Instance Handle
			DIRECTINPUT_VERSION,							// DirectInput Version
			IID_IDirectInput8,								// Device Type
			(LPVOID*)&this->_device,						// Point to device storage
			NULL)))
		{
			MessageBox(NULL, L"Error initializing Input Manager", L"Error", MB_OK);
			return false;
		}

		// Initialize the Keyboard.
		if (!this->initKeyboard())
			return false;

		// Call update once to populate the input states.
		this->Update();

		return true;
	}

	bool CInputManager::initKeyboard(void)
	{
		if (FAILED(this->_device->CreateDevice(GUID_SysKeyboard,
			&this->_keyboard,
			NULL)))
		{
			MessageBox(NULL, L"Error initializing Keyboard", L"Error", MB_OK);
			return false;
		}

		if (FAILED(this->_keyboard->SetDataFormat(&c_dfDIKeyboard)))
		{
			MessageBox(NULL, L"Error setting keyboard data format", L"Error", MB_OK);
			return false;
		}

		if (FAILED(this->_keyboard->SetCooperativeLevel(CGameEngine::Instance()->GetWindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		{
			MessageBox(NULL, L"Error setting keyboard cooperative level", L"Error", MB_OK);
			return false;
		}

		if (FAILED(this->_keyboard->Acquire()))
		{
			MessageBox(NULL, L"Error acquiring keyboard device", L"Error", MB_OK);
			return false;
		}

		// Create the keyboard states.
		this->_curKeyboardState = new CKeyboardState();
		this->_preKeyboardState = new CKeyboardState();

		return true;
	}

	void CInputManager::Update(void)
	{
		// Update the keyboard.
		this->_preKeyboardState->CopyKeyBuffer(this->_curKeyboardState->GetKeyStates());

		// Make sure we reacquire the keyboard if the device was lost.
		if (this->_keyboard->GetDeviceState(this->_curKeyboardState->GetBufferSize(), this->_curKeyboardState->GetKeyBuffer()) == DIERR_INPUTLOST)
			_keyboard->Acquire();
	}

	bool CInputManager::IsKeyDown(int keyCode)
	{
		return this->_curKeyboardState->IsKeyDown(keyCode);
	}

	bool CInputManager::IsKeyUp(int keyCode)
	{
		return this->_curKeyboardState->IsKeyUp(keyCode);
	}

	bool CInputManager::WasKeyPressed(int keyCode)
	{
		if (this->_curKeyboardState->IsKeyDown(keyCode) && this->_preKeyboardState->IsKeyUp(keyCode))
			return true;
		else
			return false;
	}
	
	bool CInputManager::WasKeyReleased(int keyCode)
	{
		if (this->_curKeyboardState->IsKeyUp(keyCode) && this->_preKeyboardState->IsKeyDown(keyCode))
			return true;
		else
			return false;
	}
};