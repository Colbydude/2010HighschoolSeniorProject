#pragma once

// Global Header Files.
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

// Local Header Files.
#include "CGameSprite.h"
#include "CSceneObject.h"
#include "CTexture.h"
#include "CInputManager.h"

namespace DirectXEngine
{
	class Megaman : public CSceneObject
	{
		private:
			DirectXEngine::CGameSprite *megamanSprite;
			DirectXEngine::CTexture *megamanImages[5];
			bool _finished;

		public:
		// Constructor & Destructor.
		Megaman(void);
		~Megaman(void);

		// Function Declarations.
		bool Create(void);
		void Step(float);
		void Draw(float);
		void StopFalling();

		// Accessors & Mutators.
		bool GetFinished(void) { return this->_finished; }
		void SetFinished(bool value) { _finished = value; }
	};
};