#include "WinMain.h"
#include "CGameEngine.h"
#include "CInputManager.h"

#define GEInstance DirectXEngine::CGameEngine::Instance()
#define InputManager DirectXEngine::CInputManager::Instance()

using namespace DirectXEngine;

// Window Callback.
LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// Called when the game window is closed.
		case WM_QUIT:
		case WM_CLOSE:
		case WM_DESTROY:
		{
			GEInstance->SetGameRunning(false);
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// Application Entry Point.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	// Local Variables.
	MSG msg;		// Message Structure
	HWND hWnd;		// Window Handle
	WNDCLASSEX wc;	// Window Class Structure
	nCmdShow = 1;

	if (!GamePreLoad())
		return 0;

	// Fill the structure.
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"GameWindow";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Register the structure.
	RegisterClassEx(&wc);

	// Create the Program Window.
	hWnd = CreateWindowEx(NULL,										// dwExStyle
		L"GameWindow",												// Class Name - must match the lpszClassname of a registered window class
		GEInstance->GetWindowTitle(),								// Window Title
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,	// dwStyle
		0, 0,														// Screen Coordinates (X, Y)
		GEInstance->GetScreenWidth(), GEInstance->GetScreenHeight(),// Screen Size (Width, Height)
		NULL,														// Parent Window
		NULL,														// Menu
		hInstance,													// Instance Handle
		NULL);														// Extra Parameters

	// Ensure that there were no creation errors.
	if (!hWnd)
	{
		MessageBox(NULL, L"Error Creating Application Window", L"Fatal Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	// Display the window.
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Initialize the Game Engine.
	GEInstance->SetWindowHandle(hWnd);
	if (!GEInstance->Init(GEInstance->GetScreenWidth(), GEInstance->GetScreenHeight(), GEInstance->GetColorDepth()))
		return 0;

	if (!InputManager->Init())
		return 0;

	// Message Loop.
	while (GEInstance->GetGameRunning())
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		InputManager->Update();
		GEInstance->Update();
	}

	// End the Game.
	GEInstance->End();

	// Goodnight.
	return 0;
}