#include<Windows.h>
#include<mmsystem.h>
#include"cleanwindow.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);  //������Ϣ������������Windows�ͽ���Windows��Ϣ
/*
   hInstance:ϵͳΪ���ڷ����ʵ���ţ�����ǰ���е�ʵ���ľ����Ψһ��ʶ�����е�ʵ��
   hPrevInstance:��ǰʵ����ǰһ��ʵ���ľ��,win32������ͨ��Ϊnull
   szCmdLine:һ���Կ���ֹ���ַ�����ָ�����ݸ�Ӧ�ó���������в���
   iCmdShow:ָ������Ĵ���Ӧ�������ʾ��������󻯡���С�������صȡ�
            ���������ֵ�ɸó���ĵ�������ָ�����ڵ���ShowWindow()ʱ����ʹ�õ���ֵ��
*/
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine,int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("�Ҵ����Ǵ�");   //������
	HWND hwnd;     //���
	MSG msg;       //��Ϣ��
	WNDCLASS wndclass;   //����һ��������ʵ��
	/*
	��ʼ���ô������
	*/
	wndclass.style = CS_HREDRAW | CS_VREDRAW;    //������ʽ
	wndclass.cbClsExtra = 0;     //����Ķ��⸽�ӿռ䣬�ø������ɵ����д��ڹ���ø��ӿռ䡣������C++���е�static����
	wndclass.cbWndExtra = 0;     //�Դ��ڵĸ��Ӷ���ռ䣬ÿʵ����һ�����ڶ���һ��������c++�еĳ�Ա����
	wndclass.hInstance = hInstance;    //����ʵ������Windows�Զ��ַ�
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);     //��ʾ�����ͼ��title
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);      //���ڹ��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   //����ˢ
	wndclass.lpszMenuName = NULL;    //ǰ���ڵ���Դ�˵���
	wndclass.lpfnWndProc = WndProc;    //���ô������Windows��Ϣ����
	wndclass.lpszClassName = szAppName; //��������
	/*
	ע�ᴰ����
	*/
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}
	/*
	����һ�����塣�ѷ����ڴ档����һ��������
	*/
	hwnd = CreateWindow(szAppName,    //��������
		TEXT("��ӭ1!"),//���ڱ���
		WS_OVERLAPPEDWINDOW,//��������
		CW_USEDEFAULT,//��ʼx��λ��
		CW_USEDEFAULT,//��ʼy��λ��
		CW_USEDEFAULT,//��ʼx����ߴ�
		CW_USEDEFAULT,//��ʼy����ߴ�
		NULL,//��������
		NULL,//���ڲ˵����
		hInstance,//����ʵ�����
		NULL,//��������
		);
	ShowWindow(hwnd, iCmdShow);//��ʾ����
	UpdateWindow(hwnd);  //���´���,�˺���ֱ�ӽ�WM_PAINT��Ϣ���͵�ָ�����ڵĴ��ڹ��̣��ƹ�Ӧ�ó������
	/*
	��Ϣѭ��,�̶�д��������û�д���   
	�������У�ֱ���յ�WM_QUIT��Ϣ
	*/
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//������Ϣ�����͵�Windows��Ϣ����
		DispatchMessage(&msg);  //����Ϣ��������ڹ���
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
		MessageBox(hwnd, TEXT("�����Ѵ�����"), TEXT("��ʾ��"), MB_OK);
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
		DrawText(hdc, TEXT("�Ҽ�����������"), -1, &rect, DT_VCENTER | DT_SINGLELINE);
		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, true);
		//UpdateWindow(hwnd);
		Sleep(1000);
		return 0;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("�������������"), -1, &rect, DT_CENTER | DT_SINGLELINE);
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
