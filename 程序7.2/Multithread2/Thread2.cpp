// Thread2.cpp :演示Win32 API多线程编程

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;			// 当前实例
TCHAR szTitle[MAX_LOADSTRING];	 // 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];		// 标题栏文本

// 函数声明:
ATOM	MyRegisterClass(HINSTANCE hInstance);
BOOL	InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//程序入口函数，第1个线程函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_THREAD2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 应用程序初始化：
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_THREAD2);

	// 主消息循环：
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

//  MyRegisterClass() ：注册窗口类
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_THREAD2);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_THREAD2;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//InitInstance(HANDLE, int): 保存实例句柄并创建主窗口
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 用全局变量存储实例句柄
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// 定义第1个线程函数
struct thread1
{
	HWND hwnd1;
	int no1;
};
thread1 obj1;
UINT ThreadProc1(LPVOID lpvoid);
UINT ThreadProc1(LPVOID lpvoid)
{
	thread1 *temp = (thread1*)lpvoid;
	HWND hwnd= temp->hwnd1;
	int no = temp->no1;
	char buff[200];
	HDC hdc= GetDC(hwnd);
	for(int i=0;i<no;i++)
	{
		wsprintf(buff,"线程1函数的输出 : %d",i+1);
		TextOut(hdc,50,50,(LPCTSTR)buff,strlen(buff));
		Sleep(50);
	}
	return 0;
}

// 定义第2个线程函数
struct thread2
{
	HWND hwnd2;
	int no2;
};
thread2 obj2;
UINT ThreadProc2(LPVOID lpvoid);
UINT ThreadProc2(LPVOID lpvoid)
{
	thread2 *temp = (thread2*)lpvoid;
	HWND hwnd= temp->hwnd2;
	int no = temp->no2;
	char buff[200];
	HDC hdc= GetDC(hwnd);

	for(int i=0;i<no;i++)
	{
		wsprintf(buff,"线程2函数的输出 :%d",i+1);
		TextOut(hdc,248,50,(LPCTSTR)buff,strlen(buff));
		Sleep(75);
	}

	return 0;
}

//WndProc(HWND, unsigned, WORD, LONG):回调函数处理主窗口消息
//  WM_COMMAND	- 处理菜单命令消息
//  WM_PAINT	- 重建主窗口
//  WM_DESTROY	- 处理退出窗口消息
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	char string[] = "Hello World!";
	HANDLE hThrd1,hThrd2;

	int i = 0;
	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			// 运行第1个线程
			obj1.hwnd1 = hWnd;
			obj1.no1 = 140;
			 hThrd1 = CreateThread(NULL,  //不设置安全属性 
							 0,                //使用默认的堆栈大小 
							 (LPTHREAD_START_ROUTINE) ThreadProc1, 
							 (LPVOID)&obj1, // 指向线程函数 
							 CREATE_SUSPENDED, // 挂起状态初始化线程 
						 NULL);       
					 
			 ResumeThread(hThrd1);//唤醒线程工作
			 SetThreadPriority(hThrd1,THREAD_PRIORITY_HIGHEST);

			 //运行第2个线程
			obj2.hwnd2 = hWnd;
			obj2.no2 = 260;
			 hThrd2 = CreateThread(NULL,  // 不设置安全属性  
							 0,                //使用默认的堆栈大小 
							 (LPTHREAD_START_ROUTINE) ThreadProc2, 
							 (LPVOID)&obj2, //指向线程函数  
							 CREATE_SUSPENDED, // 挂起状态初始化线程 
						 NULL);       
			 ResumeThread(hThrd2);			 
			 SetThreadPriority(hThrd1,THREAD_PRIORITY_LOWEST);
		 EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// 关于对话框消息处理
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
