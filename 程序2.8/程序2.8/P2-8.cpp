//����2.8 �׽��ִ�������������

#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	WSADATA WsaDat;
	int nResult=WSAStartup(MAKEWORD(2,2),&WsaDat);
	if(nResult!=0)
	{
		std::cout<<"Winsock�����ʼ��ʧ�ܣ�������: "<<nResult<<"\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		int nError=WSAGetLastError();
		std::cout<<"�����׽���ʧ�ܣ�������: "<<nError<<"\r\n";
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
		std::cout<<"���ܰ󶨵�ַ��Ϣ���׽��֣�������: "<<nError<<"\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	if(listen(Socket,1)==SOCKET_ERROR)
	{
		int nError=WSAGetLastError();
		std::cout<<"���������׽����������ܣ�������: "<<nError<<"\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	SOCKET TempSock=SOCKET_ERROR;
	while(TempSock==SOCKET_ERROR)
	{
		std::cout<<"�����������ڵȴ����Կͻ���������...\r\n";
		TempSock=accept(Socket,NULL,NULL);
	}
	Socket=TempSock;
	std::cout<<"���������пͻ������ӵ���!\r\n\r\n";

	char *szMessage="������˵��������Զ�������������ֺ�\r\n";
	send(Socket,szMessage,strlen(szMessage),0);

	// �Ͽ��׽�������
	if(shutdown(Socket,SD_SEND)==SOCKET_ERROR)
	{
		int nError=WSAGetLastError();
		std::cout<<"���ܶϿ��׽������ӣ�������: "<<nError<<"\r\n";
		closesocket(Socket);
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// �ر��׽���
	closesocket(Socket);

	// �ر�Winsock����
	WSACleanup();
	system("PAUSE");
	return 0;
}
