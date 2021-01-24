// ClientSocket.cpp : 实现文件
#include "stdafx.h"
#include "Client.h"
#include "ClientSocket.h"
#include "ClientDlg.h"  //手动添加的包含语句

CClientSocket::CClientSocket(CClientDlg* pDlg)
{
	m_pDlg=pDlg;
}
CClientSocket::~CClientSocket()
{
	m_pDlg=NULL;
}

// CClientSocket 成员函数
//事件处理函数，当客户端套接字收到FD_READ消息时，执行此函数
void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CSocket::OnReceive(nErrorCode);
	//调用CClientDlg类的相应函数处理
	if (nErrorCode==0) m_pDlg->onReceive();
}
