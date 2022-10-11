#include "framework.h"
#include "WindowsProject1.h"
#include "shellapi.h"
#include "commctrl.h"
#pragma comment(lib, "Comctl32.lib")
//#pragma comment(lib, "User32.lib")
//#pragma comment(lib, "Shell32.lib")
#include <thread>
using namespace std;

DWORD WINAPI send_req(LPVOID lpParam);

bool ThreadStart = false;
DWORD dwThread;
HANDLE hThread;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case BUT_START:
                {
                    if (!ThreadStart)
                    {
                        CreateThread(
                            NULL,                   // default security attributes
                            0,                      // use default stack size  
                            send_req,       // thread function name
                            NULL,          // argument to thread function 
                            0,                      // use default creation flags 
                            &dwThread);
                        Exit_Thread = false;
                        ThreadStart = true;
                    }
                    else
                    {
                        MessageBox(hwnd, L"ɨ��������", L"��ע��!", MB_OK);
                    }
                    return 0;
                }
                case BUT_STOP: 
                {
                    if (ThreadStart)
                    {
                        Exit_Thread = true;
                        WaitForMultipleObjects(1, &hThread, TRUE, INFINITE);
                        CloseHandle(hThread);
                        ThreadStart = false;
                    }
                    return 0;
                }
                case BUT_HIDEWINDOW:
                {
                    ShowWindow(hwnd, SW_HIDE);
                    return 0;
                }
            }
        }
        case WM_DESTROY:
        {
            if (ThreadStart)
            {
                Exit_Thread = true;
                WaitForMultipleObjects(1, &hThread, TRUE, INFINITE);
                CloseHandle(hThread);
            }
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.m

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
            return 0;
        }
        case ID_NID_CALLBACK:
        {
            switch (LOWORD(lParam))
            {
                case WM_LBUTTONDOWN:
                {
                    ShowWindow(hwnd, SW_SHOW);
                    return 0;
                }
                case WM_RBUTTONDOWN:
                {
                    if (Exit_Thread)
                    {
                        MessageBox(hwnd, L"", L"Cation", IDOK);
                        return 0;
                    }
                }
            }
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}