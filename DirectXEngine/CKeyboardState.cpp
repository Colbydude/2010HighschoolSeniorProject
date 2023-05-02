#include "CKeyboardState.h"

namespace DirectXEngine
{
	CKeyboardState::CKeyboardState(void)
	{
	}

	CKeyboardState::~CKeyboardState(void)
	{
	}

	bool CKeyboardState::IsKeyDown(int keyCode)
	{
		if (this->_keyStates[keyCode] & 0x80)
			return true;
		else
			return false;
	}

	bool CKeyboardState::IsKeyUp(int keyCode)
	{
		return !this->IsKeyDown(keyCode);
	}

	void CKeyboardState::CopyKeyBuffer(char* buffer)
	{
		for (int i = 0; i < 256; i++)
			this->_keyStates[i] = buffer[i];
	}
};