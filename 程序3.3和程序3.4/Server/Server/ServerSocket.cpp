// ServerSocket.cpp : ʵ���ļ�
#include "stdafx.h"
#include "Server.h"
#include "ServerSocket.h"
#include "ServerDlg.h"  //�ֶ����
CServerSocket::CServerSocket(CServerDlg* pDlg)
{
	m_pDlg=pDlg;//��ʼ����Ա����
}

CServerSocket::~CServerSocket()
{
	m_pDlg=NULL;
}

// CServerSocket ��Ա����
void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CSocket::OnAccept(nErrorCode);
	m_pDlg->onAccept();//�������Ի����еĴ�����
}
