#include "CGameEngine.h"
#include "WinMain.h"

namespace DirectXEngine
{
	const D3DCOLOR CGameEngine::_ambientColor = D3DCOLOR_RGBA(255, 255, 255, 0);
	CGameEngine* CGameEngine::_instance = new CGameEngine();

	CGameEngine::CGameEngine(void)
		: _windowHandle(NULL), _windowTitle(L"D3DPong"), 
		_screenWidth(640), _screenHeight(480), _colorDepth(32),
		_gameRunning(true)
	{
	}

	CGameEngine::~CGameEngine(void)
	{
		if (this->_gameRunning)
			this->_gameRunning = false;

		if (this->_spriteHandler)
			this->_spriteHandler->Release();

		if (this->_device)
			this->_device->Release();

		if (this->_d3d)
			this->_d3d->Release();
	
		delete this->_spriteHandler;
		delete this->_device;
		delete this->_d3d;
	}

	bool CGameEngine::Init(int width, int height, int depth)
	{
		// Set up Engine Variables.
		this->_screenWidth = width;
		this->_screenHeight = height;
		this->_colorDepth = depth;
		// Initialize Direct3D.
		this->_d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (!this->_d3d)
			return false;

		// Get the Display Mode (to ensure maximum compatibility).
		D3DDISPLAYMODE disp;
		this->_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &disp);

		// Presentation Parameters.
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
		d3dpp.Windowed = true;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.BackBufferFormat = disp.Format;
		d3dpp.BackBufferWidth = this->_screenWidth;
		d3dpp.BackBufferHeight = this->_screenHeight;
		d3dpp.hDeviceWindow = this->_windowHandle;

		// Create the Direct3D Device.
		this->_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->_windowHandle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &this->_device);

		if (!this->_device)
			return false;

		// Enable Z-buffering, set the fill mode, and set the ambient color (white).
		this->_device->SetRenderState(D3DRS_ZENABLE, true);
		this->_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		this->_device->SetRenderState(D3DRS_AMBIENT, this->_ambientColor);

		// Initialize the Sprite handler.
		if (FAILED(D3DXCreateSprite(this->_device, &this->_spriteHandler)))
			return false;

		// Game Initialization.
		if (!GameInit())
			return false;

		return true;
	}

	void CGameEngine::End(void)
	{
		GameEnd();
	}

	void CGameEngine::Update(void)
	{
		static float lastFrame = 0.0f;
		static bool firstFrame = true;

		float delta = ((float)((int)this->_gameTimer->GetTime())) - lastFrame;
		lastFrame = ((float)((int)this->_gameTimer->GetTime()));

		if (firstFrame)
		{
			delta = 0;
			firstFrame = false;
		}

		GameUpdate(delta);

		this->BeginRender();

		GameRender(delta);

		this->EndRender();
	}

	void CGameEngine::BeginRender(void)
	{
		if (!this->_device)
			return;

		this->_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);

		if (FAILED(this->_device->BeginScene()))
			return;

		if (FAILED(this->_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND)))
			return;
	}

	void CGameEngine::EndRender(void)
	{
		if (!this->_device)
			return;

		this->_spriteHandler->End();
		
		if (FAILED(this->_device->EndScene()))
			return;

		if (FAILED(this->_device->Present(NULL, NULL, NULL, NULL)))
			return;
	}

	void CGameEngine::SetWindowTitle(LPCWSTR val)
	{
		this->_windowTitle = val;

		if (this->_windowHandle)
			SetWindowText(this->_windowHandle, this->_windowTitle);
	}
};