#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
void space()
{
    keybd_event(VK_SPACE,0,0,0);
    keybd_event(VK_SPACE,0,KEYEVENTF_KEYUP,0);
}
void left()
{
    keybd_event(VK_LEFT,0,0,0);
    keybd_event(VK_LEFT,0,KEYEVENTF_KEYUP,0);
}
void right()
{
    keybd_event(VK_RIGHT,0,0,0);
    keybd_event(VK_RIGHT,0,KEYEVENTF_KEYUP,0);
}
void up()
{
    keybd_event(VK_UP,0,0,0);
    keybd_event(VK_UP,0,KEYEVENTF_KEYUP,0);
}
void down()
{
    keybd_event(VK_DOWN,0,0,0);
    keybd_event(VK_DOWN,0,KEYEVENTF_KEYUP,0);
}
void init()
{
    keybd_event(VK_CONTROL,0,0,0);
    keybd_event('T',0,0,0);
    keybd_event('T',0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
    keybd_event('E',0,0,0);
    keybd_event('E',0,KEYEVENTF_KEYUP,0);
    keybd_event('D',0,0,0);
    keybd_event('D',0,KEYEVENTF_KEYUP,0);
    keybd_event('G',0,0,0);
    keybd_event('G',0,KEYEVENTF_KEYUP,0);
    keybd_event('E',0,0,0);
    keybd_event('E',0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_SHIFT,0,0,0);
    keybd_event(186,0,0,0);
    keybd_event(186,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
    keybd_event(108,0,0,0);
    keybd_event(108,0,KEYEVENTF_KEYUP,0);
    keybd_event('S',0,0,0);
    keybd_event('S',0,KEYEVENTF_KEYUP,0);
    keybd_event('U',0,0,0);
    keybd_event('U',0,KEYEVENTF_KEYUP,0);
    keybd_event('R',0,0,0);
    keybd_event('R',0,KEYEVENTF_KEYUP,0);
    keybd_event('F',0,0,0);
    keybd_event('F',0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_RETURN,0,0,0);
    keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
}
int main()
{
    Sleep(5000);
    init();
    Sleep(500);
    space();
    Sleep(4600);
    right();
    right();
    Sleep(515);
    down();
    Sleep(1190);
    right();
    right();
    Sleep(780);
    down();
    Sleep(1600);
    left();
    left();
    Sleep(500);
    down();
    Sleep(500);
    right();
    right();
    Sleep(300);
    down();
    Sleep(800);
    left();
    left();
    Sleep(910);
    down();
    return 0;
}