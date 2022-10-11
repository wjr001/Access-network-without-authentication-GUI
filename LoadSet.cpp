#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <atlstr.h>
using namespace std;
#pragma warning(disable : 6387)

LPCWSTR CharToLPCWSTR(char* input);


char* LoadSet(const char* SetName , int MaxLength)
{
    char* value = (char*)malloc(MaxLength);
    ifstream setfile;
    char* output = (char*)malloc(128);
    setfile.open("conf.ini", ios::in);
    if (!setfile.is_open())
    {
        setfile.close();
        MessageBox(NULL,L"�����ļ�����ʧ��",L"����",MB_OK);
        exit(0);
    }
    string nowsettemp;
    char* nowset = (char*)malloc(1024);
    setfile >> nowset;
    while (strcmp(SetName, nowset) != 0)
    {
        if (setfile.eof())
        {
            break;
        }
        setfile >> nowset;
    }
    if (setfile.eof())
    {
        setfile.close();
        sprintf_s(output, 128, "�Ҳ������� %s", SetName);
        MessageBox(NULL, CharToLPCWSTR(output), L"����", MB_OK);
        exit(0);
    }
    else
    {
        setfile >> nowset;
        setfile >> nowset;
        if (strlen(nowset) > MaxLength-1)
        {
            sprintf_s(output, 128, "���� %s ���������ֵΪ %d", SetName,MaxLength-1);
            MessageBox(NULL, CharToLPCWSTR(output), L"����", MB_OK);
            exit(0);
        }
        else
        {
            sprintf_s(value, MaxLength, "%s", nowset);
            setfile.close();
            return value;
        }
    }
}