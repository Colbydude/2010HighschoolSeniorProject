#include "Game.h"
#include "CGameEngine.h"
#include "CInputManager.h"

#define GEInstance DirectXEngine::CGameEngine::Instance()
#define InputManager DirectXEngine::CInputManager::Instance()

DirectXEngine::CGameSprite *background;
DirectXEngine::Megaman *megaman;
DirectXEngine::CGameSprite *complete;

bool GamePreLoad(void)
{
	GEInstance->SetScreenWidth(640);
	GEInstance->SetScreenHeight(480);
	GEInstance->SetWindowTitle(L"Direct X Engine");

	return true;
}

bool GameInit(void)
{
	// Background Image.
	background = new DirectXEngine::CGameSprite();
	if (!background->Load(L"Background.png"))
	{
		MessageBox(NULL, L"Failed to Load the background image!", L"Error!", MB_OK);
		return false;
	}
	background->SetPositionX(0);
	background->SetPositionY(0);
	background->SetFrameWidth(640);
	background->SetFrameHeight(480);

	// Create the Megaman Object.
	megaman = new DirectXEngine::Megaman();
	megaman->Create();

	// Completion Image, make invisible until completion
	complete= new DirectXEngine::CGameSprite();
	if (!complete->Load(L"Winner.png"))
	{
		MessageBox(NULL, L"Failed to Load the completion image!", L"Error!", MB_OK);
		return false;
	}
	complete->SetPositionX(215);
	complete->SetPositionY(227);
	complete->SetFrameWidth(210);
	complete->SetFrameHeight(26);
	complete->SetVisible(false);

	return true;
}

void GameUpdate(float delta)
{
	megaman->Step(delta);
	background->Update(delta);
	complete->Update(delta);

	if (megaman->GetFinished() == true)
		complete->SetVisible(true);
}

void GameRender(float delta)
{
	background->Render(delta);
	megaman->Draw(delta);
	complete->Render(delta);
}

void GameEnd(void)
{
	if (megaman != NULL)
		delete megaman;
	if (background != NULL)
		delete background;
}