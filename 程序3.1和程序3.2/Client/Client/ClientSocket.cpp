// ClientSocket.cpp : 实现文件
#include "stdafx.h"
#include "Client.h"
#include "ClientSocket.h"
#include "ClientDlg.h"
// CClientSocket
CClientSocket::CClientSocket()
{
	m_pDlg=NULL;
}
CClientSocket::~CClientSocket()
{
	m_pDlg=NULL;
}
// CClientSocket 成员函数
void CClientSocket::OnConnect(int nErrorCode)
{
	//调用CClientDlg类的onConnect()函数
	CAsyncSocket::OnConnect(nErrorCode);
	if (nErrorCode==0) m_pDlg->onConnect();
}

void CClientSocket::OnReceive(int nErrorCode)
{
	//调用CClientDlg类的onReceived()函数
	CAsyncSocket::OnReceive(nErrorCode);
	if (nErrorCode==0) m_pDlg->onReceived();
}
void CClientSocket::OnClose(int nErrorCode)
{
	//调用CClientDlg类的onClose()函数
	CAsyncSocket::OnClose(nErrorCode);
	if (nErrorCode==0) m_pDlg->onClose();
}
void CClientSocket::setParentDlg(CClientDlg* pDlg)
{
	m_pDlg=pDlg;
}
