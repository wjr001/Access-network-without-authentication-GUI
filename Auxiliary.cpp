#include <atlstr.h>
#include <string>
#include <sstream>
using namespace std;

LPCWSTR CharToLPCWSTR(char* input)
{
    WCHAR wszClassName[128];
    memset(wszClassName, 0, sizeof(wszClassName));
    MultiByteToWideChar(CP_ACP, 0, input, strlen(input) + 1, wszClassName,
        sizeof(wszClassName) / sizeof(wszClassName[0]));
    return wszClassName;
}

bool AllisNum(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        int tmp = (int)str[i];
        if (tmp >= 48 && tmp <= 57)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}