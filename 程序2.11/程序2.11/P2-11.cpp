//程序2.11 服务器响应多客户机并发连接完整代码
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib")

#define IDC_EDIT_IN		101
#define IDC_EDIT_OUT		102
#define IDC_MAIN_BUTTON		103
#define WM_SOCKET		104

int nPort=5555;

HWND hEditIn=NULL;
HWND hEditOut=NULL;
char szHistory[10000];
sockaddr sockAddrClient;

const int nMaxClients=3;
int nClient=0;
SOCKET Socket[nMaxClients-1];
SOCKET ServerSocket=NULL;

LRESULT CALLBACK WinProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass,sizeof(WNDCLASSEX));
	wClass.cbClsExtra=NULL;
	wClass.cbSize=sizeof(WNDCLASSEX);
	wClass.cbWndExtra=NULL;
	wClass.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wClass.hIcon=NULL;
	wClass.hIconSm=NULL;
	wClass.hInstance=hInst;
	wClass.lpfnWndProc=(WNDPROC)WinProc;
	wClass.lpszClassName="Window Class";
	wClass.lpszMenuName=NULL;
	wClass.style=CS_HREDRAW|CS_VREDRAW;

	if(!RegisterClassEx(&wClass))
	{
		int nResult=GetLastError();
		MessageBox(NULL,
			"窗体类注册失败\r\n错误码:",
			"窗体类错误",
			MB_ICONERROR);
	}

	HWND hWnd=CreateWindowEx(NULL,
			"Window Class",
			"异步套接字服务器（多客户机并发访问）",
			WS_OVERLAPPEDWINDOW,
			200,
			200,
			500,
			400,
			NULL,
			NULL,
			hInst,
			NULL);

	if(!hWnd)
	{
		int nResult=GetLastError();

		MessageBox(NULL,
			"创建窗体失败\r\n错误码:",
			"窗体错误",
			MB_ICONERROR);
	}

    ShowWindow(hWnd,nShowCmd);

	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
    {
		case WM_COMMAND:
			switch(LOWORD(wParam))
            {
				case IDC_MAIN_BUTTON:
				{
					char szBuffer[1024];
					ZeroMemory(szBuffer,sizeof(szBuffer));

					SendMessage(hEditOut,
						WM_GETTEXT,
						sizeof(szBuffer),
						reinterpret_cast<LPARAM>(szBuffer));
					for(int n=0;n<=nClient;n++)
					{
						send(Socket[n],szBuffer,strlen(szBuffer),0);
					}

					SendMessage(hEditOut,WM_SETTEXT,NULL,(LPARAM)"");
				}
				break;
			}
			break;
		case WM_CREATE: 
		{
			ZeroMemory(szHistory,sizeof(szHistory));

			// 创建接收消息框
			hEditIn=CreateWindowEx(WS_EX_CLIENTEDGE,
				"EDIT",
				"",
				WS_CHILD|WS_VISIBLE|ES_MULTILINE|
				ES_AUTOVSCROLL|ES_AUTOHSCROLL,
				50,
				100,
				400,
				200,
				hWnd,
				(HMENU)IDC_EDIT_IN,
				GetModuleHandle(NULL),
				NULL);
			if(!hEditIn)
			{
				MessageBox(hWnd,
					"创建接收消息框失败",
					"错误",
					MB_OK|MB_ICONERROR);
			}
			HGDIOBJ hfDefault=GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(hEditIn,
					WM_SETFONT,
					(WPARAM)hfDefault,
					MAKELPARAM(FALSE,0));
			SendMessage(hEditIn,
					WM_SETTEXT,
					NULL,
					(LPARAM)"正在等待客户机并发连接...");

			// 创建发送消息框
			hEditOut=CreateWindowEx(WS_EX_CLIENTEDGE,
						"EDIT",
						"",
						WS_CHILD|WS_VISIBLE|ES_MULTILINE|
						ES_AUTOVSCROLL|ES_AUTOHSCROLL,
						50,
						30,
						400,
						60,
						hWnd,
						(HMENU)IDC_EDIT_IN,
						GetModuleHandle(NULL),
						NULL);
			if(!hEditOut)
			{
				MessageBox(hWnd,
					"创建发送消息框失败",
					"错误",
					MB_OK|MB_ICONERROR);
			}

			SendMessage(hEditOut,
					WM_SETFONT,
					(WPARAM)hfDefault,
					MAKELPARAM(FALSE,0));
			SendMessage(hEditOut,
					WM_SETTEXT,
					NULL,
					(LPARAM)"输入要发送的消息...");

			// 创建发送按钮
			HWND hWndButton=CreateWindow( 
					    "BUTTON",
						"发送",
						WS_TABSTOP|WS_VISIBLE|
						WS_CHILD|BS_DEFPUSHBUTTON,
						50,
						330,
						75,
						23,
						hWnd,
						(HMENU)IDC_MAIN_BUTTON,
						GetModuleHandle(NULL),
						NULL);
			
			SendMessage(hWndButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

			WSADATA WsaDat;
			int nResult=WSAStartup(MAKEWORD(2,2),&WsaDat);
			if(nResult!=0)
			{
				MessageBox(hWnd,
					"Winsock服务初始化失败",
					"严重错误",
					MB_ICONERROR);
				SendMessage(hWnd,WM_DESTROY,NULL,NULL);
				break;
			}

			ServerSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
			if(ServerSocket==INVALID_SOCKET)
			{
				MessageBox(hWnd,
					"创建套接字失败",
					"严重错误",
					MB_ICONERROR);
				SendMessage(hWnd,WM_DESTROY,NULL,NULL);
				break;
			}

			SOCKADDR_IN SockAddr;
			SockAddr.sin_port=htons(nPort);
			SockAddr.sin_family=AF_INET;
			SockAddr.sin_addr.s_addr=htonl(INADDR_ANY);

			if(bind(ServerSocket,(LPSOCKADDR)&SockAddr,sizeof(SockAddr))==SOCKET_ERROR)
			{
				MessageBox(hWnd,"套接字绑定失败","错误",MB_OK);
				SendMessage(hWnd,WM_DESTROY,NULL,NULL);
				break;
			}

			nResult=WSAAsyncSelect(ServerSocket,
					hWnd,
					WM_SOCKET,
					(FD_CLOSE|FD_ACCEPT|FD_READ));
			if(nResult)
			{
				MessageBox(hWnd,
					"WSAAsyncSelect异步套件字事件模式失败",
					"严重错误",
					MB_ICONERROR);
				SendMessage(hWnd,WM_DESTROY,NULL,NULL);
				break;
			}

			if(listen(ServerSocket,SOMAXCONN)==SOCKET_ERROR)
			{
				MessageBox(hWnd,
					"服务器侦听失败",
					"错误",
					MB_OK);
				SendMessage(hWnd,WM_DESTROY,NULL,NULL);
				break;
			}
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			shutdown(ServerSocket,SD_BOTH);
			closesocket(ServerSocket);
			WSACleanup();
			return 0;
		}
		break;

		case WM_SOCKET:
		{
			switch(WSAGETSELECTEVENT(lParam))
			{
				case FD_READ:
				{
					for(int n=0;n<=nMaxClients;n++)
					{
						char szIncoming[1024];
						ZeroMemory(szIncoming,sizeof(szIncoming));

						int inDataLength=recv(Socket[n],
							(char*)szIncoming,
							sizeof(szIncoming)/sizeof(szIncoming[0]),
							0);

						if(inDataLength!=-1)
						{
							strncat(szHistory,szIncoming,inDataLength);
							strcat(szHistory,"\r\n");
	
							SendMessage(hEditIn,
								WM_SETTEXT,
								sizeof(szIncoming)-1,
								reinterpret_cast<LPARAM>(&szHistory));
						}
					}
				}
				break;

				case FD_CLOSE:
				{
					MessageBox(hWnd,
						"有一个客户机关闭了连接",
						"连接关闭",
						MB_ICONINFORMATION|MB_OK);
				}
				break;

				case FD_ACCEPT:
				{
					if(nClient<nMaxClients)
					{
						int size=sizeof(sockaddr);
						Socket[nClient]=accept(wParam,&sockAddrClient,&size);                
						if (Socket[nClient]==INVALID_SOCKET)
						{
							int nret = WSAGetLastError();
							WSACleanup();
						}
						SendMessage(hEditIn,
							WM_SETTEXT,
							NULL,
							(LPARAM)"有一新客户机连接到服务器!");
						}
						nClient++;
					}
				break;
    			}   
			}
		}
    
    return DefWindowProc(hWnd,msg,wParam,lParam);
}
