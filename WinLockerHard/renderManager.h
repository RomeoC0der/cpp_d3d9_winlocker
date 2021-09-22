#pragma once
#include "baseInterface.hpp"
#include <cassert>//crash?
#include "Color.hpp"
#include <d3dx9.h>
#include <string>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
class RenderManager : public IBaseInterface
{
public:
	RenderManager(IDirect3DDevice9* pDevice);
	RenderManager();
//	RenderManager():  pBackgroundTexture(nullptr), pDevice(nullptr), d3d9(nullptr), screenHeight(0),screenWidth(0) {};
	virtual ~RenderManager() { this->release(); };
	void release() override;
	void render_start();
	void render_end();
	void initRender(HWND hwnd, bool bWindowed);
	void ScreenShot(const std::string& path, int type = 0);
private:
	IDirect3DDevice9* pDevice{ nullptr };
	IDirect3D9* d3d9{ nullptr };
	int screenWidth;
	int screenHeight;
	bool bWindowed{ false };
	IDirect3DTexture9* pBackgroundTexture = nullptr;
};

