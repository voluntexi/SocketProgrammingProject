
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

// ����Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char **argv)
{

    //-----------------------------------------
    // �����ͳ�ʼ������
    WSADATA wsaData;
    int iResult;

    DWORD dwError;
    int i = 0;

    struct hostent *remoteHost;
    char *host_name;
    struct in_addr addr;

    char **pAlias;

    // У�������в���
    if (argc != 2) {
        printf("�÷�: %s ipv4address\n", argv[0]);
        printf(" or\n");
        printf("       %s hostname\n", argv[0]);
        printf(" �������ƽ���\n");
        printf("       %s 127.0.0.1\n", argv[0]);
        printf("  �����ַ����\n");
        printf("       %s www.163.com\n", argv[0]);
        return 1;
    }
    // ��ʼ��Winsock����
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("Winsock��������ʧ��: %d\n", iResult);
        return 1;
    }

    host_name = argv[1];

// ������������������ʹ��gethostbyname()����
// ����ʹ��gethostbyaddr���� (�ٶ���ַ����ΪIPv4)
    if (isalpha(host_name[0])) {        /* �������ƽ��� */
        printf("Calling gethostbyname with %s\n", host_name);
        remoteHost = gethostbyname(host_name);
    } else {
        printf("Calling gethostbyaddr with %s\n", host_name);
        addr.s_addr = inet_addr(host_name);
        if (addr.s_addr == INADDR_NONE) {
            printf("IPv4��ַ��ʽ����ȷ��\n");
            return 1;
        } else
            remoteHost = gethostbyaddr((char *) &addr, 4, AF_INET);
    }

    if (remoteHost == NULL) {
        dwError = WSAGetLastError();
        if (dwError != 0) {
            if (dwError == WSAHOST_NOT_FOUND) {
                printf("����û�ҵ���\n");
                return 1;
            } else if (dwError == WSANO_DATA) {
                printf("�޲�ѯ������أ�\n");
                return 1;
            } else {
                printf("�����������󣬴�����: %ld\n", dwError);
                return 1;
            }
        }
    } else {
        printf("�������:\n");
        printf("\t��������: %s\n", remoteHost->h_name);
        for (pAlias = remoteHost->h_aliases; *pAlias != 0; pAlias++) {
            printf("\t���������� #%d: %s\n", ++i, *pAlias);
        }
        printf("\t��ַ����: ");
        switch (remoteHost->h_addrtype) {
        case AF_INET:
            printf("AF_INET\n");
            break;
        case AF_INET6:
            printf("AF_INET6\n");
            break;
        case AF_NETBIOS:
            printf("AF_NETBIOS\n");
            break;
        default:
            printf(" %d\n", remoteHost->h_addrtype);
            break;
        }
        printf("\t��ַ����: %d\n", remoteHost->h_length);

        if (remoteHost->h_addrtype == AF_INET) {
			i=0;
            while (remoteHost->h_addr_list[i] != 0) {
                addr.s_addr = *(u_long *) remoteHost->h_addr_list[i++];
                printf("\tIPv4 ��ַ #%d: %s\n", i, inet_ntoa(addr));
            }
        } else if (remoteHost->h_addrtype == AF_INET6)
            printf("\tԶ������Ϊ IPv6��ַ\n");
    }
    return 0;
}