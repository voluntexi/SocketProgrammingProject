// ClientSocket.cpp : ʵ���ļ�
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
// CClientSocket ��Ա����
void CClientSocket::OnConnect(int nErrorCode)
{
	//����CClientDlg���onConnect()����
	CAsyncSocket::OnConnect(nErrorCode);
	if (nErrorCode==0) m_pDlg->onConnect();
}

void CClientSocket::OnReceive(int nErrorCode)
{
	//����CClientDlg���onReceived()����
	CAsyncSocket::OnReceive(nErrorCode);
	if (nErrorCode==0) m_pDlg->onReceived();
}
void CClientSocket::OnClose(int nErrorCode)
{
	//����CClientDlg���onClose()����
	CAsyncSocket::OnClose(nErrorCode);
	if (nErrorCode==0) m_pDlg->onClose();
}
void CClientSocket::setParentDlg(CClientDlg* pDlg)
{
	m_pDlg=pDlg;
}
