// ServerSocket.cpp : 实现文件
#include "stdafx.h"
#include "Server.h"
#include "ServerSocket.h"
#include "ServerDlg.h"  //手动添加
CServerSocket::CServerSocket(CServerDlg* pDlg)
{
	m_pDlg=pDlg;//初始化成员变量
}

CServerSocket::~CServerSocket()
{
	m_pDlg=NULL;
}

// CServerSocket 成员函数
void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CSocket::OnAccept(nErrorCode);
	m_pDlg->onAccept();//调用主对话框中的处理函数
}
