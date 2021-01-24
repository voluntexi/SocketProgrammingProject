// ClientSocket.cpp : ʵ���ļ�
#include "stdafx.h"
#include "Client.h"
#include "ClientSocket.h"
#include "ClientDlg.h"  //�ֶ���ӵİ������

CClientSocket::CClientSocket(CClientDlg* pDlg)
{
	m_pDlg=pDlg;
}
CClientSocket::~CClientSocket()
{
	m_pDlg=NULL;
}

// CClientSocket ��Ա����
//�¼������������ͻ����׽����յ�FD_READ��Ϣʱ��ִ�д˺���
void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CSocket::OnReceive(nErrorCode);
	//����CClientDlg�����Ӧ��������
	if (nErrorCode==0) m_pDlg->onReceive();
}
