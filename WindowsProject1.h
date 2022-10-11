#pragma once



#define ID_NID 2000
#define ID_NID_CALLBACK 2001
#define BUT_START 3000
#define BUT_STOP 3001
#define BUT_HIDEWINDOW 3002
#define MEMU_TITAL 4001
#define MEMU_EXIT 4002
#define MEMU_HOD 4003


#include "resource.h"
#ifndef WindowsProject1
#define WindowsProject1
extern bool Exit_Thread;
extern long int SleepTime;
extern HMENU hMenu;
extern HWND hwnd;
extern bool hide;
#endif