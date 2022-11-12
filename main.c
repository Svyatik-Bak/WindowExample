// Unicode form in C with a button
#include <windows.h>
#include <stdbool.h>
#define BUTTON 1

LRESULT CALLBACK WindowFunc(HWND window, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message) 
    {
        //Enable this if pictures are glitching
        //case WM_SIZE:
        //InvalidateRect(picture_hwnd, NULL, FALSE);
        //break;
        case WM_CREATE:
        //hide cmd
        HWND hiding = GetConsoleWindow();
        ShowWindow(hiding, SW_HIDE);
        // button
        HWND button1 = CreateWindowW(L"button", L"Press me!", WS_VISIBLE | WS_CHILD, 50, 50, 100, 100, window, (HMENU) BUTTON, NULL, NULL); 
        // changing ugly font to default
        case WM_SETFONT:
        NONCLIENTMETRICS metrics = {}; metrics.cbSize = sizeof(metrics);
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0); HFONT guiFont = CreateFontIndirect(&metrics.lfCaptionFont);
        SendMessageW(button1, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
        DeleteObject(guiFont);
        //Events for buttons and menu
        case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        	case BUTTON:
        	system("mspaint");
        	break;
        }
        break;
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(window, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR Args, int WinMode)
{
// classes
 WNDCLASSEX wc = { 0 }; 
 wc.cbSize = sizeof(WNDCLASSEX);
 wc.hInstance = hThisInst; 
 wc.lpszClassName = "windowclass";
 wc.lpfnWndProc = WindowFunc; 
 wc.style = 0;
 wc.hCursor = LoadCursor(NULL, IDC_ARROW);
 wc.lpszMenuName = NULL; 
 wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
 wc.cbClsExtra = 0; 
 wc.cbWndExtra = 0;

// error
 if (!RegisterClassEx(&wc)) 
 {
    return 1;
 }

 // Main window
 HWND window = CreateWindowW(L"windowclass", L"Window", WS_OVERLAPPEDWINDOW, 800, 360, 320, 240, NULL, NULL, hThisInst, NULL);
 // use WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX if u want to disable resizing

 ShowWindow(window, WinMode);
 UpdateWindow(window);
 MSG Message;

 while (GetMessage(&Message, NULL, 0, 0) > 0)
 {
    TranslateMessage(&Message);
    DispatchMessage(&Message);
 }
 return Message.wParam;
}
