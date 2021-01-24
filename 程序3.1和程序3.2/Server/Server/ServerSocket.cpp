// ServerSocket.cpp : 实现文件
#include "stdafx.h"
#include "Server.h"
#include "ServerSocket.h"
#include "ServerDlg.h"

CServerSocket::CServerSocket()
{
	m_pDlg=NULL;
}

CServerSocket::~CServerSocket()
{
	m_pDlg=NULL;
}
// CServerSocket 成员函数
void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CAsyncSocket::OnAccept(nErrorCode);
	if(nErrorCode==0) m_pDlg->onAccept();
}
void CServerSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CAsyncSocket::OnClose(nErrorCode);
	if(nErrorCode==0) m_pDlg->onClose();
}
void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CAsyncSocket::OnReceive(nErrorCode);
	if(nErrorCode==0) m_pDlg->onReceive(this);
}
void CServerSocket::setParentDlg(CServerDlg* pDlg)
{
	m_pDlg=pDlg;
}
