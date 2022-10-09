#include "framework.h"
#include "WindowsProject1.h"
#include "shellapi.h"
#include "commctrl.h"
#pragma comment(lib, "Comctl32.lib")
//#pragma comment(lib, "User32.lib")
//#pragma comment(lib, "Shell32.lib")

#define BUT1 3000
#define ID_NID 2000
#define ID_NID_CALLBACK 2001

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case BUT1:
        {
            MessageBox(hwnd, L"Are you sure?", L"Cation", IDOK);
            ShowWindow(hwnd, SW_HIDE);
        }
        }
        return 0;
    }
    case WM_DESTROY:
    {
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
            MessageBox(hwnd, L"Are you sure?", L"Cation", IDOK);
            return 0;
        }
        }
    };
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}