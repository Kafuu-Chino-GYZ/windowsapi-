#include<Windows.h>
#include"cleanwindow.h"
void CleanWindow(HWND hwnd,RECT rect)
{
	InvalidateRect(hwnd,&rect, true);
}