#include "Megaman.h"
#include "CGameEngine.h"
#include "CInputManager.h"

#define GEInstance DirectXEngine::CGameEngine::Instance()
#define InputManager DirectXEngine::CInputManager::Instance()

namespace DirectXEngine
{
	Megaman::Megaman(void)
	{
		this->_finished = false;
	}

	Megaman::~Megaman(void)
	{
		//delete megamanSprite;
	}

	bool Megaman::Create()
	{
		// Load Megaman's Sprites.
		megamanImages[0] = new DirectXEngine::CTexture();
		megamanImages[0]->Load(L"Megaman0.png");			// Run Left
		megamanImages[1] = new DirectXEngine::CTexture();
		megamanImages[1]->Load(L"Megaman1.png");			// Run Right
		megamanImages[2] = new DirectXEngine::CTexture();
		megamanImages[2]->Load(L"Megaman2.png");			// Stand Left
		megamanImages[3] = new DirectXEngine::CTexture();
		megamanImages[3]->Load(L"Megaman3.png");			// Stand Right
		megamanImages[4] = new DirectXEngine::CTexture();
		megamanImages[4]->Load(L"Megaman4.png");			// Appear/Disappear
		megamanSprite = new DirectXEngine::CGameSprite();
		megamanSprite->SetTexture(megamanImages[3]);
		megamanSprite->SetFrameHeight(25);
		megamanSprite->SetFrameWidth(25);
		megamanSprite->SetColumns(4);
		megamanSprite->SetTotalFrames(4);

		megamanSprite->SetPositionX(32);
		megamanSprite->SetPositionY(32);
		megamanSprite->SetGravityY(-0.01);

		return true;
	}

	void Megaman::Step(float delta)
	{
		megamanSprite->Update(delta);
		megamanSprite->Animate();

		// Horizontal Movement.
		if (this->GetFinished() == false)
		{
			if (InputManager->IsKeyDown(DIK_RIGHT))
			{
				megamanSprite->SetVelocityX(20);
				megamanSprite->SetTexture(megamanImages[1]);
			}
			else if (InputManager->IsKeyDown(DIK_LEFT))
			{
				megamanSprite->SetVelocityX(-20);
				megamanSprite->SetTexture(megamanImages[0]);
			}
			else
			{
				if (megamanSprite->GetTexture() == megamanImages[0])
					megamanSprite->SetTexture(megamanImages[2]);
				else if (megamanSprite->GetTexture() == megamanImages[1])
					megamanSprite->SetTexture(megamanImages[3]);
				megamanSprite->SetVelocityX(0);
			}

			// Teleporting
			if (InputManager->WasKeyPressed(DIK_DOWN))
			{
				// Red
				if (megamanSprite->GetLeft() >= 64 && megamanSprite->GetRight() <= 112 && megamanSprite->GetTop() == 87)
				{
					megamanSprite->SetPositionX(156);
					megamanSprite->SetPositionY(151);
				}
				else if (megamanSprite->GetLeft() >= 144 && megamanSprite->GetRight() <= 192 && megamanSprite->GetTop() == 151)
				{
					megamanSprite->SetPositionX(76);
					megamanSprite->SetPositionY(87);
				}
				// Purple
				else if (megamanSprite->GetLeft() >= 496 && megamanSprite->GetRight() <= 544 && megamanSprite->GetTop() == 87)
				{
					megamanSprite->SetPositionX(362);
					megamanSprite->SetPositionY(151);
				}
				else if (megamanSprite->GetLeft() >= 352 && megamanSprite->GetRight() <= 400 && megamanSprite->GetTop() == 151)
				{
					megamanSprite->SetPositionX(508);
					megamanSprite->SetPositionY(87);
				}
				// Orange
				else if (megamanSprite->GetLeft() >= 544 && megamanSprite->GetRight() <= 592 && megamanSprite->GetTop() == 151)
				{
					megamanSprite->SetPositionX(156);
					megamanSprite->SetPositionY(327);
				}
				else if (megamanSprite->GetLeft() >= 144 && megamanSprite->GetRight() <= 192 && megamanSprite->GetTop() == 327)
				{
					megamanSprite->SetPositionX(556);
					megamanSprite->SetPositionY(151);
				}
				// Blue
				else if (megamanSprite->GetLeft() >= 368 && megamanSprite->GetRight() <= 416 && megamanSprite->GetTop() == 327)
				{
					megamanSprite->SetPositionX(252);
					megamanSprite->SetPositionY(375);
				}
				else if (megamanSprite->GetLeft() >= 240 && megamanSprite->GetRight() <= 288 && megamanSprite->GetTop() == 375)
				{
					megamanSprite->SetPositionX(380);
					megamanSprite->SetPositionY(327);
				}
				// Yellow
				else if (megamanSprite->GetLeft() >= 48 && megamanSprite->GetRight() <= 96 && megamanSprite->GetTop() == 375)
				{
					megamanSprite->SetPositionX(28);
					megamanSprite->SetPositionY(279);
				}
				else if (megamanSprite->GetLeft() >= 16 && megamanSprite->GetRight() <= 64 && megamanSprite->GetTop() == 279)
				{
					megamanSprite->SetPositionX(60);
					megamanSprite->SetPositionY(375);
				}
				// Green
				else if (megamanSprite->GetLeft() >= 576 && megamanSprite->GetRight() <= 624 && megamanSprite->GetTop() == 279)
				{
					megamanSprite->SetPositionX(364);
					megamanSprite->SetPositionY(215);
				}
				else if (megamanSprite->GetLeft() >= 352 && megamanSprite->GetRight() <= 400 && megamanSprite->GetTop() == 215)
				{
					megamanSprite->SetPositionX(588);
					megamanSprite->SetPositionY(279);
				}
				// Pink
				else if (megamanSprite->GetLeft() >= 144 && megamanSprite->GetRight() <= 192 && megamanSprite->GetTop() == 215)
				{
					megamanSprite->SetPositionX(76);
					megamanSprite->SetPositionY(439);
				}
				else if (megamanSprite->GetLeft() >= 64 && megamanSprite->GetRight() <= 112 && megamanSprite->GetTop() == 439)
				{
					megamanSprite->SetPositionX(156);
					megamanSprite->SetPositionY(215);
				}
				// Finish
				else if (megamanSprite->GetLeft() >= 592 && megamanSprite->GetRight() <= 640 && megamanSprite->GetTop() == 439)
				{
					this->SetFinished(true);
				}
			}

			// Somewhat collision detection.
			if (megamanSprite->GetRight() >= -64 && megamanSprite->GetLeft() <= 704)
			{
				if (megamanSprite->GetTop() >= 439)
				{
					megamanSprite->SetPositionY(439);
					StopFalling();
				}
				else if (megamanSprite->GetTop() >= 375)
				{
					megamanSprite->SetPositionY(375);
					StopFalling();
				}
				else if (megamanSprite->GetTop() >= 327)
				{
					megamanSprite->SetPositionY(327);
					StopFalling();
				}
				else if (megamanSprite->GetTop() >= 279)
				{
					megamanSprite->SetPositionY(279);
					StopFalling();
				}
				else if (megamanSprite->GetTop() >= 215)
				{
					megamanSprite->SetPositionY(215);
					StopFalling();
				}
				else if (megamanSprite->GetTop() >= 151)
				{
					megamanSprite->SetPositionY(151);
					StopFalling();
				}
				else if (megamanSprite->GetTop() >= 87)
				{
					megamanSprite->SetPositionY(87);
					StopFalling();
				}
			}
			else
			{
				megamanSprite->SetPositionX(32);
				megamanSprite->SetPositionY(32);
				megamanSprite->SetGravityY(-0.01);
			}
		}
		else
		{
			megamanSprite->SetTexture(megamanImages[4]);
			megamanSprite->SetVelocityY(-30);
		}
	}

	void Megaman::Draw(float delta)
	{
		megamanSprite->Render(delta);
	}

	void Megaman::StopFalling()
	{
		megamanSprite->SetGravityY(0);
		megamanSprite->SetVelocityY(0);
		megamanSprite->SetAccelerationY(0);
	}
};