// ClientSocket.cpp : ʵ���ļ�
#include "stdafx.h"
#include "Server.h"
#include "ClientSocket.h"
#include "ServerDlg.h" //�ֶ���Ӱ������
#include "Message.h"  //�ֶ���Ӱ������

// CClientSocket

CClientSocket::CClientSocket(CServerDlg* pDlg)//������ڲ������ֶ����
{	//��ʼ����Ա�������ֶ����
	m_pDlg=pDlg;
	m_pFile=NULL;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
}

CClientSocket::~CClientSocket()
{
	//�ÿջ��ͷų�Ա����,�ֶ����
	m_pDlg=NULL;
	if (m_pFile!=NULL) delete m_pFile;
	if (m_pArchiveIn!=NULL) delete m_pArchiveIn;
	if (m_pArchiveOut!=NULL) delete m_pArchiveOut;
	m_pFile=NULL;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
}

// CClientSocket ��Ա����
//�׽����յ�����ʱ���Զ����ô˺���
void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CSocket::OnReceive(nErrorCode);
	m_pDlg->onReceive(this);//�������Ի����еĴ��������ֶ����
}

void CClientSocket::Init(void)
{	//�ֶ���ӳ�ʼ������
	m_pFile=new CSocketFile(this,TRUE);
	m_pArchiveIn=new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut=new CArchive(m_pFile,CArchive::store);
}
//������Ϣ
void CClientSocket::SendMessage(CMessage* pMsg)
{
	//�ֶ����
	if (m_pArchiveOut!=NULL)
	{
		pMsg->Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}
//������Ϣ
void CClientSocket::ReceiveMessage(CMessage* pMsg)
{
	pMsg->Serialize(*m_pArchiveIn);


}



