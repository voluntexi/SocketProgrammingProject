//程序2.4 阻塞式套接字客户机完整代码
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	// 初始化 Winsock服务
	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
	{
		std::cout<<"Winsock错误 - Winsock服务初始化失败！\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	// 创建套接字
	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		std::cout<<"套接字错误 -创建套接字失败!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// 主机名解析
	struct hostent *host;
	if((host=gethostbyname("localhost"))==NULL)
	{
		std::cout<<"主机名解析失败！\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// 初始化套接字地址结构信息
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port=htons(8888);
	SockAddr.sin_family=AF_INET;
	SockAddr.sin_addr.s_addr=*((unsigned long*)host->h_addr);

	// 连接服务器
	if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr))!=0)
	{
		std::cout<<"与服务器连接失败！\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// 从服务接收信息并显示
	char buffer[1024];
	memset(buffer,0,1023);
	int inDataLength=recv(Socket,buffer,1024,0);
	std::cout<<buffer;

	// 断开套接字连接，不允许发送数据，但可以继续接收数据
	shutdown(Socket,SD_SEND);

	// 关闭套接字，释放资源
	closesocket(Socket);

	// 关闭Winsock服务，清理内存
	WSACleanup();
	system("PAUSE");
	return 0;
}

