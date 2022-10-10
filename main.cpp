// WindowsProject1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsProject1.h"
#include "shellapi.h"
#include "commctrl.h"
#include <iostream>
#pragma comment(lib, "Comctl32.lib")
//#pragma comment(lib, "User32.lib")
//#pragma comment(lib, "Shell32.lib")

#define BUT1 3000
#define ID_NID 2000
#define ID_NID_CALLBACK 2001

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool HttpGetReq();
bool Exit_Thread = true;



int WINAPI wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    WNDCLASS MyWindows = { };
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    MyWindows.lpfnWndProc = WindowProc;
    MyWindows.hInstance = hInstance;
    MyWindows.lpszClassName = CLASS_NAME;
    RegisterClass(&MyWindows);
    
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Windows",    // Window text
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |  WS_MINIMIZEBOX | WS_MAXIMIZEBOX,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 120,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
     );
    if (hwnd == NULL)
    {
        return 0;
    }

    //Create Button
    HWND hwndButton = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"启动",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        10,         // y position 
        100,        // Button width
        50,        // Button height
        hwnd,     // Parent window
        (HMENU)BUT1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    if (hwndButton == NULL)
    {
        return 0;
    }
    
    
    //Create icon at taskbar
    NOTIFYICONDATA nid = {};
    nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = ID_NID;
    nid.uFlags = NIF_MESSAGE | NIF_ICON;
    nid.uCallbackMessage = ID_NID_CALLBACK;
    /*
    LoadIconMetric(
        NULL,
        IDI_APPLICATION,
        LIM_LARGE,
        &nid.hIcon
    );
    */
    Shell_NotifyIcon(NIM_ADD, &nid);
    


    ShowWindow(hwnd, nCmdShow);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 1;
}

