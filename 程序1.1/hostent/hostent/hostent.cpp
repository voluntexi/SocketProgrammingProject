
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

// 链接Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char **argv)
{

    //-----------------------------------------
    // 声明和初始化变量
    WSADATA wsaData;
    int iResult;

    DWORD dwError;
    int i = 0;

    struct hostent *remoteHost;
    char *host_name;
    struct in_addr addr;

    char **pAlias;

    // 校验命令行参数
    if (argc != 2) {
        printf("用法: %s ipv4address\n", argv[0]);
        printf(" or\n");
        printf("       %s hostname\n", argv[0]);
        printf(" 主机名称解析\n");
        printf("       %s 127.0.0.1\n", argv[0]);
        printf("  网络地址解析\n");
        printf("       %s www.163.com\n", argv[0]);
        return 1;
    }
    // 初始化Winsock服务
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("Winsock服务启动失败: %d\n", iResult);
        return 1;
    }

    host_name = argv[1];

// 如果输入的是主机名，使用gethostbyname()解析
// 否则，使用gethostbyaddr解析 (假定地址类型为IPv4)
    if (isalpha(host_name[0])) {        /* 主机名称解析 */
        printf("Calling gethostbyname with %s\n", host_name);
        remoteHost = gethostbyname(host_name);
    } else {
        printf("Calling gethostbyaddr with %s\n", host_name);
        addr.s_addr = inet_addr(host_name);
        if (addr.s_addr == INADDR_NONE) {
            printf("IPv4地址格式不正确！\n");
            return 1;
        } else
            remoteHost = gethostbyaddr((char *) &addr, 4, AF_INET);
    }

    if (remoteHost == NULL) {
        dwError = WSAGetLastError();
        if (dwError != 0) {
            if (dwError == WSAHOST_NOT_FOUND) {
                printf("主机没找到！\n");
                return 1;
            } else if (dwError == WSANO_DATA) {
                printf("无查询结果返回！\n");
                return 1;
            } else {
                printf("主机解析错误，错误码: %ld\n", dwError);
                return 1;
            }
        }
    } else {
        printf("解析结果:\n");
        printf("\t主机名称: %s\n", remoteHost->h_name);
        for (pAlias = remoteHost->h_aliases; *pAlias != 0; pAlias++) {
            printf("\t主机别名： #%d: %s\n", ++i, *pAlias);
        }
        printf("\t地址类型: ");
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
        printf("\t地址长度: %d\n", remoteHost->h_length);

        if (remoteHost->h_addrtype == AF_INET) {
			i=0;
            while (remoteHost->h_addr_list[i] != 0) {
                addr.s_addr = *(u_long *) remoteHost->h_addr_list[i++];
                printf("\tIPv4 地址 #%d: %s\n", i, inet_ntoa(addr));
            }
        } else if (remoteHost->h_addrtype == AF_INET6)
            printf("\t远程主机为 IPv6地址\n");
    }
    return 0;
}