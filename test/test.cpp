#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
const int M=200,L=150;
const double pi=acos(-1.0);
int a(double x)
{
    return (x>0.0)?floor(x+0.5):ceil(x-0.5);
}
int main()
{
    Sleep(1000);
    POINT p;
    GetCursorPos(&p);
    SetCursorPos(p.x+a(cos(0)*L),p.y+a(sin(0)*L));
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
    for(double i=0;i<=M*2;++i)
    {
        SetCursorPos(p.x+a(cos(pi/M*i)*L),p.y+a(sin(pi/M*i)*L));
        Sleep(10);
    }
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
    return 0;
} 