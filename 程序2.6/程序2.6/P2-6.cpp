//程序2.6 非阻塞模式客户机完整代码

#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main(void)
{
	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
	{
		std::cout<<"Winsock错误 - Winsock初始化失败\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	// 创建套接字

	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		std::cout<<"Winsock错误 - 创建套接字失败!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	// 解析主机名
	struct hostent *host;
	if((host=gethostbyname("localhost"))==NULL)
	{
		std::cout<<"解析主机名失败！\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	// 配置套接字地址结构信息
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port=htons(8888);
	SockAddr.sin_family=AF_INET;
	SockAddr.sin_addr.s_addr=*((unsigned long*)host->h_addr);
	
	// 连接服务器
	if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr))!=0)
	{
		std::cout<<"连接服务器失败！\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	//  iMode!=0是阻塞模式
	u_long iMode=1;
	ioctlsocket(Socket,FIONBIO,&iMode);
	
	// 主循环
	for(;;)
	{
		// 接收服务器信息
		char buffer[1024];
		memset(buffer,0,1023);
		int inDataLength=recv(Socket,buffer,1024,0);
		std::cout<<buffer;
		
		int nError=WSAGetLastError();
		if(nError!=WSAEWOULDBLOCK&&nError!=0)
		{
			std::cout<<"Winsock错误码为: "<<nError<<"\r\n";
			std::cout<<"服务器断开连接!\r\n";
			// 断开套接字，只能接收不能发送
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
