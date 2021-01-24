//程序2.5 阻塞式服务器完整代码

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
		std::cout<<"不能绑定地址信息到套接字!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	listen(Socket,1);

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

	// 断开套接字连接，不允许发送数据
	shutdown(Socket,SD_SEND);

	// 关闭套接字，释放资源
	closesocket(Socket);

	//关闭Winsock服务，清理内存
	WSACleanup();
	system("PAUSE");
	return 0;
}
