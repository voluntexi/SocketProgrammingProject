//����2.4 ����ʽ�׽��ֿͻ�����������
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	// ��ʼ�� Winsock����
	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
	{
		std::cout<<"Winsock���� - Winsock�����ʼ��ʧ�ܣ�\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	// �����׽���
	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		std::cout<<"�׽��ִ��� -�����׽���ʧ��!\r\n";
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

	// ��ʼ���׽��ֵ�ַ�ṹ��Ϣ
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port=htons(8888);
	SockAddr.sin_family=AF_INET;
	SockAddr.sin_addr.s_addr=*((unsigned long*)host->h_addr);

	// ���ӷ�����
	if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr))!=0)
	{
		std::cout<<"�����������ʧ�ܣ�\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// �ӷ��������Ϣ����ʾ
	char buffer[1024];
	memset(buffer,0,1023);
	int inDataLength=recv(Socket,buffer,1024,0);
	std::cout<<buffer;

	// �Ͽ��׽������ӣ������������ݣ������Լ�����������
	shutdown(Socket,SD_SEND);

	// �ر��׽��֣��ͷ���Դ
	closesocket(Socket);

	// �ر�Winsock���������ڴ�
	WSACleanup();
	system("PAUSE");
	return 0;
}

