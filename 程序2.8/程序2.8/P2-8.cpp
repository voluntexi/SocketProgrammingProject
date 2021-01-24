//程序2.8 套接字错误处理完整代码

#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	WSADATA WsaDat;
	int nResult=WSAStartup(MAKEWORD(2,2),&WsaDat);
	if(nResult!=0)
	{
		std::cout<<"Winsock服务初始化失败，错误码: "<<nResult<<"\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		int nError=WSAGetLastError();
		std::cout<<"创建套接字失败，错误码: "<<nError<<"\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	SOCKADDR_IN serverInf;
	serverInf.sin_family=AF_INET;
	serverInf.sin_addr.s_addr=INADDR_ANY;
	serverInf.sin_port=htons(8888);

	if(bind(Socket,(SOCKADDR*)(&serverInf),sizeof(serverInf))==SOCKET_ERROR)
	{
		int nError=WSAGetLastError();
		std::cout<<"不能绑定地址信息到套接字，错误码: "<<nError<<"\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	if(listen(Socket,1)==SOCKET_ERROR)
	{
		int nError=WSAGetLastError();
		std::cout<<"不能启动套接字侦听功能，错误码: "<<nError<<"\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	SOCKET TempSock=SOCKET_ERROR;
	while(TempSock==SOCKET_ERROR)
	{
		std::cout<<"服务器：正在等待来自客户机的连接...\r\n";
		TempSock=accept(Socket,NULL,NULL);
	}
	Socket=TempSock;
	std::cout<<"服务器：有客户机连接到达!\r\n\r\n";

	char *szMessage="服务器说：有朋自远方来来，不亦乐乎\r\n";
	send(Socket,szMessage,strlen(szMessage),0);

	// 断开套接字连接
	if(shutdown(Socket,SD_SEND)==SOCKET_ERROR)
	{
		int nError=WSAGetLastError();
		std::cout<<"不能断开套接字连接，错误码: "<<nError<<"\r\n";
		closesocket(Socket);
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// 关闭套接字
	closesocket(Socket);

	// 关闭Winsock服务
	WSACleanup();
	system("PAUSE");
	return 0;
}
