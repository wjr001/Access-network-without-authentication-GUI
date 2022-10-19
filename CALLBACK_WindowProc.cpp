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
LPCWSTR CharToLPCWSTR(char* input);

bool ThreadStart = false;
bool stopThreadExe = false;
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
                        MessageBox(NULL, L"��������ɨ��", L"���Ժ�", MB_OK);
                        hThread = CreateThread(
                            NULL,                   // default security attributes
                            0,                      // use default stack size  
                            send_req,       // thread function name
                            NULL,          // argument to thread function 
                            0,                      // use default creation flags 
                            &dwThread);
                        Exit_Thread = false;
                        ThreadStart = true;
                        stopThreadExe = false;
                    }
                    else
                    {
                        MessageBox(hwnd, L"��ȴ�ɨ��ֹͣ", L"��ע��!", MB_OK);
                    }
                    return 0;
                }
                case BUT_STOP: 
                {                    
                    if (ThreadStart && !stopThreadExe)
                    {
                        Exit_Thread = true;
                        CloseHandle(hThread);
                    }
                    stopThreadExe = true;
                    return 0;
                }
                case BUT_HIDEWINDOW:
                {
                    ShowWindow(hwnd, SW_HIDE);
                    ModifyMenuA(hMenu, MEMU_HOD, MF_STRING, MEMU_HOD, LPCSTR("��ʾ"));
                    DrawMenuBar(hwnd);
                    hide = true;
                    return 0;
                }
                case MEMU_EXIT:
                {
                    if (ThreadStart && !stopThreadExe)
                    {
                        Exit_Thread = true;
                        CloseHandle(hThread);
                    }
                    PostQuitMessage(0);
                    return 0;
                }
                case MEMU_HOD:
                {
                    if (!hide)
                    {
                        ModifyMenuA(hMenu,MEMU_HOD, MF_STRING, MEMU_HOD , LPCSTR("��ʾ"));
                        ShowWindow(hwnd, SW_HIDE);
                        hide = true;
                    }
                    else
                    {
                        ModifyMenuA(hMenu, MEMU_HOD, MF_STRING, MEMU_HOD, LPCSTR("����"));
                        ShowWindow(hwnd, SW_SHOW);
                        hide = false;
                    }
                    DrawMenuBar(hwnd);
                    return 0;
                }
            }
        }
        case WM_DESTROY:
        {
            if (ThreadStart && !stopThreadExe)
            {
                Exit_Thread = true;
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
                    CONSOLE_CURSOR_INFO info = { 1, 0 };				//�����������Խṹ��
                    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ľ��
                    COORD coord = { 0, 0 };								//����xy����ṹ�壬�������ù��λ��
                    POINT pt = { 0, 0 };								//���������������
                    SetConsoleCursorInfo(hand, &info);				//���ù������
                    SetConsoleCursorPosition(hand, coord);		//�����������������ù��λ��
                    GetCursorPos(&pt);
                    TrackPopupMenu(hMenu,
                        TPM_RIGHTBUTTON,
                        pt.x,pt.y,
                        0,
                        hwnd,
                        nullptr
                        );
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