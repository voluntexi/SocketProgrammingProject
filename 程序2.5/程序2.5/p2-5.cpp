//����2.5 ����ʽ��������������

#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
	{
		std::cout<<"Winsock�����ʼ��ʧ��!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		std::cout<<"�����׽���ʧ�ܣ�\r\n";
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
		std::cout<<"���ܰ󶨵�ַ��Ϣ���׽���!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	listen(Socket,1);

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

	// �Ͽ��׽������ӣ�������������
	shutdown(Socket,SD_SEND);

	// �ر��׽��֣��ͷ���Դ
	closesocket(Socket);

	//�ر�Winsock���������ڴ�
	WSACleanup();
	system("PAUSE");
	return 0;
}
