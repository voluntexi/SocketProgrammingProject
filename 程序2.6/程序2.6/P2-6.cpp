//����2.6 ������ģʽ�ͻ�����������

#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main(void)
{
	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
	{
		std::cout<<"Winsock���� - Winsock��ʼ��ʧ��\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	// �����׽���

	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		std::cout<<"Winsock���� - �����׽���ʧ��!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	// ����������
	struct hostent *host;
	if((host=gethostbyname("localhost"))==NULL)
	{
		std::cout<<"����������ʧ�ܣ�\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	// �����׽��ֵ�ַ�ṹ��Ϣ
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port=htons(8888);
	SockAddr.sin_family=AF_INET;
	SockAddr.sin_addr.s_addr=*((unsigned long*)host->h_addr);
	
	// ���ӷ�����
	if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr))!=0)
	{
		std::cout<<"���ӷ�����ʧ�ܣ�\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	//  iMode!=0������ģʽ
	u_long iMode=1;
	ioctlsocket(Socket,FIONBIO,&iMode);
	
	// ��ѭ��
	for(;;)
	{
		// ���շ�������Ϣ
		char buffer[1024];
		memset(buffer,0,1023);
		int inDataLength=recv(Socket,buffer,1024,0);
		std::cout<<buffer;
		
		int nError=WSAGetLastError();
		if(nError!=WSAEWOULDBLOCK&&nError!=0)
		{
			std::cout<<"Winsock������Ϊ: "<<nError<<"\r\n";
			std::cout<<"�������Ͽ�����!\r\n";
			// �Ͽ��׽��֣�ֻ�ܽ��ղ��ܷ���
			shutdown(Socket,SD_SEND);

			// �ر��׽���
			closesocket(Socket);

			break;
		}
		Sleep(1000);
	}

	WSACleanup();
	system("PAUSE");
	return 0;
}
