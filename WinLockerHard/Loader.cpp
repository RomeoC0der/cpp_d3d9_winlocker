#include "Loader.h"
#include "Resource.h"
#include <cassert>//crash?
LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);
int Loader::register_class() {
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = loader->gethInstance();
    wcex.hIcon = LoadIcon(loader->gethInstance(), MAKEINTRESOURCE(IDI_WINLOCKERHARD));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WINLOCKERHARD);
    wcex.lpszClassName = loader->getWindowClass().c_str();
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


   

    return RegisterClassEx(&wcex);
}
BOOL Loader::init_instance( int nCmdShow)
{
    this->hwnd = (CreateWindow(this->szWindowsClass.c_str(), this->szTitle.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr));
    if (!this->hwnd)
    {
        return FALSE;
    }
    ShowWindow(this->hwnd, nCmdShow);
    UpdateWindow(this->hwnd);
    return TRUE;
}
void Loader::initWindow(HINSTANCE hInstance, int nCmdShow, const std::string& title, const std::string& wndClass, bool bWindowed)
{
    this->hInstance = hInstance;
    this->szTitle = title;
    this->szWindowsClass = wndClass;
    register_class();
    bool result = init_instance(nCmdShow);
    if (!result)return;
    this->renderer->initRender(this->hwnd, bWindowed);
}
void Loader::release()
{
   // renderer->release();
    delete this->renderer;
    this->renderer = nullptr;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        break;
    }
     case WM_CLOSE:
    {
        if (MessageBox(hWnd, "Выблядок ебаный?", "Выблядок ебаный", MB_OKCANCEL) == IDOK)
        {
            // DestroyWindow(hwnd);
        }
        // Else: User canceled. Do nothing.
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
