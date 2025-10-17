#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int main()
{
    Sleep(5000);
    while(true)
    {
        for(int i=1;i<=10;++i)
        {
            keybd_event((BYTE)37, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event((BYTE)37, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
            Sleep(100);
            keybd_event((BYTE)38, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event((BYTE)38, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
            Sleep(100);
        }
        keybd_event((BYTE)39, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
        keybd_event((BYTE)39, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
        Sleep(1000);
    }
    return 0;
}