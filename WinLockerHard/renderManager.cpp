#include "renderManager.h"
#include "Resource.h"
#include "Loader.h"
RenderManager::RenderManager(IDirect3DDevice9* pDevice)
{
	//this->pDevice = pDevice;
	//IDirect3DResource9* resourse
}
RenderManager::RenderManager()
{
	this->pDevice = nullptr;
	this->screenWidth = GetSystemMetrics(SM_CXSCREEN);
	this->screenHeight = GetSystemMetrics(SM_CYSCREEN);
	this->d3d9 = nullptr;
	this->bWindowed = false;
	this->pBackgroundTexture = nullptr;
}
void RenderManager::release()
{
	this->pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);
	this->pDevice->EndScene();
	this->pDevice->Release();
	this->pBackgroundTexture->Release();
	this->pDevice = nullptr;	
	this->d3d9->Release();
	this->d3d9 = nullptr;
}
void RenderManager::render_start()
{
	LPDIRECT3DSURFACE9 backbuffer = nullptr;
	LPDIRECT3DSURFACE9 surface = nullptr;
	pDevice->Clear(0l, nullptr, D3DCLEAR_TARGET, Color(0.0f, 0.f, 0.f).convert(), 1.0f, 0);
	pDevice->BeginScene();	
	pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	pBackgroundTexture->GetSurfaceLevel(0, &surface);
	D3DXLoadSurfaceFromSurface(
		backbuffer,
		NULL,
		NULL,
		surface,
		NULL,
		NULL,
		D3DX_DEFAULT,
		0
	);
	surface->Release();
}
void RenderManager::render_end()
{
	pDevice->EndScene();
	pDevice->Present(0, 0, 0, 0);
}
void RenderManager::initRender(HWND hwnd, bool bWindowed)
{
	this->d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dprmts;
	ZeroMemory(&d3dprmts, sizeof(D3DPRESENT_PARAMETERS));
	d3dprmts.BackBufferWidth = this->screenWidth;
	d3dprmts.BackBufferHeight = this->screenHeight;
	d3dprmts.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dprmts.Windowed = bWindowed;
	d3dprmts.BackBufferCount = 1;
	d3dprmts.EnableAutoDepthStencil = false;
	d3dprmts.FullScreen_RefreshRateInHz =bWindowed ?  0 : 60;
	d3dprmts.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dprmts.MultiSampleQuality = 0;
	d3dprmts.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dprmts.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dprmts.Flags = 0;
	d3dprmts.hDeviceWindow = hwnd;
	this->d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dprmts, &this->pDevice);
	assert(this->d3d9 && "can not create a d3d9 device");
	assert(this->pDevice && "can not create a Direct3DD9Device device");
//	auto resource = FindResource(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1), RT_RCDATA);
	//auto res = LoadResource(GetModuleHandle(0), resource);
	D3DXCreateTextureFromResource(this->pDevice, GetModuleHandle(0), MAKEINTRESOURCE(IDR_RCDATA1), &this->pBackgroundTexture);
	//D3DXCreateTextureFromFileEx(pDevice, "D:\\c++ workspace\\WinLockerHard\\WinLockerHard\\Resources\\bimba.jpg", this->screenWidth, this->screenHeight, D3DX_DEFAULT, 0, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &this->pBackgroundTexture);
	//D3DXCreateTextureFromFileEx(pDevice, MAKEINTRESOURCE(IDR_RCDATA1), this->screenWidth, this->screenHeight, D3DX_DEFAULT, 0, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &this->pBackgroundTexture);
	assert(this->pBackgroundTexture && "can not create a texture");
}
void RenderManager::ScreenShot(const std::string& path, int type)
{
	IDirect3DSurface9* pSurface;
	pDevice->CreateOffscreenPlainSurface(this->screenWidth, this->screenHeight, D3DFMT_X8R8G8B8, D3DPOOL_SCRATCH, &pSurface, NULL);
	pDevice->GetFrontBufferData(0, pSurface);
	//pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
	//pDevice->GetRenderTargetData(pSurface, )	
	D3DXSaveSurfaceToFile(path.c_str(), (D3DXIMAGE_FILEFORMAT)type, pSurface, NULL, NULL);
	pSurface->Release();
}
