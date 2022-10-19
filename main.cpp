// WindowsProject1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsProject1.h"
#include "shellapi.h"
#include "commctrl.h"
#include <string>
#include <iostream>
#include <sstream>
#pragma comment(lib, "Comctl32.lib")
//#pragma comment(lib, "User32.lib")
//#pragma comment(lib, "Shell32.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool HttpGetReq();
bool Exit_Thread = true;
char* LoadSet(const char* SetName,int MaxLength);
bool AllisNum(std::string str);
long int SleepTime = 15000;
HMENU hMenu;
HWND hwnd;
bool hide;

//entry
int WINAPI wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //Load Setting
    char* SleepTimeChar = LoadSet("SleepTime", 17);
    if ((AllisNum(SleepTimeChar) == true))
    {
        std::stringstream chartoint;
        chartoint << SleepTimeChar;
        chartoint >> SleepTime;
    }
    else
    {
        MessageBox(NULL, L"参数 SleepTime 需要全部为数字", L"警告", MB_OK);
        exit(0);
    }
    //Registration Form
    WNDCLASS MyWindows = { };
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    MyWindows.lpfnWndProc = WindowProc;
    MyWindows.hInstance = hInstance;
    MyWindows.lpszClassName = CLASS_NAME;
    MyWindows.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    RegisterClass(&MyWindows);
    
    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"360杀毒中心全盘扫描程序",    // Window text
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |  WS_MINIMIZEBOX | WS_MAXIMIZEBOX,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 360, 120,

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
    HWND hwndButton_start = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"启动",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        10,         // y position 
        100,        // Button width
        50,        // Button height
        hwnd,     // Parent window
        (HMENU)BUT_START,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    if (hwndButton_start == NULL)
    {
        return 0;
    }


    HWND hwndButton_stop = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"停止",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        120,         // x position 
        10,         // y position 
        100,        // Button width
        50,        // Button height
        hwnd,     // Parent window
        (HMENU)BUT_STOP,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    if (hwndButton_stop == NULL)
    {
        return 0;
    }

    HWND hwndButton_hidewindow = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"隐藏",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        230,         // x position 
        10,         // y position 
        100,        // Button width
        50,        // Button height
        hwnd,     // Parent window
        (HMENU)BUT_HIDEWINDOW,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    if (hwndButton_hidewindow == NULL)
    {
        return 0;
    }

    //Create Menu
    hMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_STRING,MEMU_TITAL,L"360杀毒中心");
    EnableMenuItem(hMenu, MEMU_TITAL, MF_DISABLED);
    AppendMenu(hMenu, MF_STRING, MEMU_HOD, L"隐藏");
    AppendMenu(hMenu, MF_STRING, MEMU_EXIT, L"退出");
    hide = false;
    
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

