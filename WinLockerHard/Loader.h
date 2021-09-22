#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include "renderManager.h"
class Loader : public IBaseInterface
{
public:
	Loader() {
		renderer = new RenderManager();
		hInstance = 0;
		hwnd = 0;
		szTitle.clear();
		szWindowsClass.clear();
	}
	virtual ~Loader() { this->release(); };
	void initWindow(HINSTANCE hInstance, int nCmdShow, const std::string& title, const std::string& wndClass, bool bWindowed);	
	void setHWND(HWND hWnd) { this->hwnd = hWnd; };	
	HINSTANCE& gethInstance() { return hInstance; };
	HWND& getHWND() { return hwnd; };
	std::string& getTitle() { return szTitle; };
	std::string& getWindowClass() { return szWindowsClass; };
	RenderManager* getRenderManager() { return this->renderer; };
	void release() override;
	bool unload{ false };
private:
	HINSTANCE hInstance;
	HWND hwnd;
	std::string szTitle;
	std::string szWindowsClass;
	RenderManager* renderer{};
	int register_class();
	BOOL init_instance( int nCmdShow);
};
inline std::unique_ptr<Loader>loader(new Loader());
