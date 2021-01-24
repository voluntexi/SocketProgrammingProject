// Thread2.cpp :��ʾWin32 API���̱߳��

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;			// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];	 // �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];		// �������ı�

// ��������:
ATOM	MyRegisterClass(HINSTANCE hInstance);
BOOL	InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//������ں�������1���̺߳���
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_THREAD2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Ӧ�ó����ʼ����
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_THREAD2);

	// ����Ϣѭ����
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

//  MyRegisterClass() ��ע�ᴰ����
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

//InitInstance(HANDLE, int): ����ʵ�����������������
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ȫ�ֱ����洢ʵ�����
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

// �����1���̺߳���
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
		wsprintf(buff,"�߳�1��������� : %d",i+1);
		TextOut(hdc,50,50,(LPCTSTR)buff,strlen(buff));
		Sleep(50);
	}
	return 0;
}

// �����2���̺߳���
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
		wsprintf(buff,"�߳�2��������� :%d",i+1);
		TextOut(hdc,248,50,(LPCTSTR)buff,strlen(buff));
		Sleep(75);
	}

	return 0;
}

//WndProc(HWND, unsigned, WORD, LONG):�ص�����������������Ϣ
//  WM_COMMAND	- ����˵�������Ϣ
//  WM_PAINT	- �ؽ�������
//  WM_DESTROY	- �����˳�������Ϣ
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

			// ���е�1���߳�
			obj1.hwnd1 = hWnd;
			obj1.no1 = 140;
			 hThrd1 = CreateThread(NULL,  //�����ð�ȫ���� 
							 0,                //ʹ��Ĭ�ϵĶ�ջ��С 
							 (LPTHREAD_START_ROUTINE) ThreadProc1, 
							 (LPVOID)&obj1, // ָ���̺߳��� 
							 CREATE_SUSPENDED, // ����״̬��ʼ���߳� 
						 NULL);       
					 
			 ResumeThread(hThrd1);//�����̹߳���
			 SetThreadPriority(hThrd1,THREAD_PRIORITY_HIGHEST);

			 //���е�2���߳�
			obj2.hwnd2 = hWnd;
			obj2.no2 = 260;
			 hThrd2 = CreateThread(NULL,  // �����ð�ȫ����  
							 0,                //ʹ��Ĭ�ϵĶ�ջ��С 
							 (LPTHREAD_START_ROUTINE) ThreadProc2, 
							 (LPVOID)&obj2, //ָ���̺߳���  
							 CREATE_SUSPENDED, // ����״̬��ʼ���߳� 
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

// ���ڶԻ�����Ϣ����
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
