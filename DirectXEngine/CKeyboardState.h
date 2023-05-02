#pragma once

#include <Windows.h>

namespace DirectXEngine
{
	class CKeyboardState
	{
		private:
			char _keyStates[256];

		public:
			// Constructor & Destructor.
			CKeyboardState(void);
			~CKeyboardState(void);

			// Public Methods.
			bool IsKeyDown(int);
			bool IsKeyUp(int);
			void CopyKeyBuffer(char*);

			// Accessors & Mutators.
			char* GetKeyStates(void) { return this->_keyStates; }
			LPVOID GetKeyBuffer(void) { return (LPVOID)&this->_keyStates; }
			DWORD GetBufferSize(void) { return sizeof(this->_keyStates); }
	};
};