#include<Windows.h>
#include<mmsystem.h>
#include"cleanwindow.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);  //声明消息处理函数（处理Windows和接收Windows消息
/*
   hInstance:系统为窗口分配的实例号（程序当前运行的实例的句柄，唯一标识运行中的实例
   hPrevInstance:当前实例的前一个实例的句柄,win32环境下通常为null
   szCmdLine:一个以空终止的字符串，指定传递给应用程序的命令行参数
   iCmdShow:指定程序的窗口应该如何显示，例如最大化、最小化、隐藏等。
            这个参数的值由该程序的调用者所指定，在调用ShowWindow()时可以使用到该值。
*/
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine,int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("我带你们打！");   //窗体名
	HWND hwnd;     //句柄
	MSG msg;       //消息体
	WNDCLASS wndclass;   //定义一个窗体类实例
	/*
	开始设置窗体参数
	*/
	wndclass.style = CS_HREDRAW | CS_VREDRAW;    //窗体样式
	wndclass.cbClsExtra = 0;     //对类的额外附加空间，用该类生成的所有窗口共享该附加空间。类似于C++类中的static变量
	wndclass.cbWndExtra = 0;     //对窗口的附加额外空间，每实例化一个窗口都有一个。类似c++中的成员变量
	wndclass.hInstance = hInstance;    //窗体实例名，Windows自动分发
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);     //显示上面的图标title
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);      //窗口光标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   //背景刷
	wndclass.lpszMenuName = NULL;    //前窗口的资源菜单名
	wndclass.lpfnWndProc = WndProc;    //设置窗体接收Windows消息函数
	wndclass.lpszClassName = szAppName; //窗体类名
	/*
	注册窗体类
	*/
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}
	/*
	创建一个窗体。已分配内存。返回一个窗体句柄
	*/
	hwnd = CreateWindow(szAppName,    //窗体类名
		TEXT("欢迎1!"),//窗口标题
		WS_OVERLAPPEDWINDOW,//窗口类型
		CW_USEDEFAULT,//初始x轴位置
		CW_USEDEFAULT,//初始y轴位置
		CW_USEDEFAULT,//初始x方向尺寸
		CW_USEDEFAULT,//初始y方向尺寸
		NULL,//父窗体句柄
		NULL,//窗口菜单句柄
		hInstance,//程序实例句柄
		NULL,//创建参数
		);
	ShowWindow(hwnd, iCmdShow);//显示窗口
	UpdateWindow(hwnd);  //更新窗体,此函数直接将WM_PAINT消息发送到指定窗口的窗口过程，绕过应用程序队列
	/*
	消息循环,固定写法，基本没有创新   
	持续运行，直到收到WM_QUIT消息
	*/
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//翻译消息并发送到Windows消息队列
		DispatchMessage(&msg);  //将消息分配给窗口过程
	}
	return msg.wParam;
}	
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; 
	PAINTSTRUCT ps;
	tagRECT rect = { 15,15,60,60 };
	switch (message)
	{
	case WM_CREATE:
		MessageBox(hwnd, TEXT("窗口已创建！"), TEXT("提示！"), MB_OK);
		hdc = BeginPaint(hwnd, &ps);
		TextOutA(hdc, 0, 0, "Hello2", strlen("Hello3"));
		EndPaint(hwnd, &ps);
		break;
	case WM_PAINT:

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_RBUTTONDOWN:

		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("右键被单机咯！"), -1, &rect, DT_VCENTER | DT_SINGLELINE);
		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, true);
		//UpdateWindow(hwnd);
		Sleep(1000);
		return 0;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("左键被单机咯！"), -1, &rect, DT_CENTER | DT_SINGLELINE);
		ReleaseDC(hwnd, hdc);
		return 0;
	case WM_MOVE:
		hdc = BeginPaint(hwnd, &ps);
		TextOutA(hdc, 15, 15, "WDNMD", strlen("WDNMD"));
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
