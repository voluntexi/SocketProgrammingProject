//程序2.7 非阻塞模式服务器完整代码

#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
					
int main()
{
	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
	{
		std::cout<<"Winsock服务初始化失败!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
					
	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		std::cout<<"创建套接字失败！\r\n";
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
		std::cout<<"套接字绑定失败!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
		
	listen(Socket,1);
					
	SOCKET TempSock=SOCKET_ERROR;
	while(TempSock==SOCKET_ERROR)
	{
		std::cout<<"服务器：正在等待客户机连接...\r\n";
		TempSock=accept(Socket,NULL,NULL);
	}
				
	//  iMode!=0表示阻塞模式
	u_long iMode=1;
	ioctlsocket(Socket,FIONBIO,&iMode);
					
	Socket=TempSock;
	std::cout<<"服务器说：有新客户机连接到达!\r\n\r\n";
					
	// 主循环
	for(;;)
	{
		char *szMessage="非阻塞服务器说：有朋自远方来来，不亦乐乎\r\n";
		send(Socket,szMessage,strlen(szMessage),0);
					
		int nError=WSAGetLastError();
		if(nError!=WSAEWOULDBLOCK&&nError!=0)
		{
			std::cout<<"Winsock错误码为: "<<nError<<"\r\n";
			std::cout<<"客户机断开连接!\r\n";

			// 断开套接字，不允许发送，可以接收
			shutdown(Socket,SD_SEND);

			// 关闭套接字
			closesocket(Socket);

			break;
		}
			
		Sleep(1000);
	}

	WSACleanup();
	system("PAUSE");
	return 0;
}
