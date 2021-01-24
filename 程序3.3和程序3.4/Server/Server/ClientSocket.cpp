// ClientSocket.cpp : 实现文件
#include "stdafx.h"
#include "Server.h"
#include "ClientSocket.h"
#include "ServerDlg.h" //手动添加包含语句
#include "Message.h"  //手动添加包含语句

// CClientSocket

CClientSocket::CClientSocket(CServerDlg* pDlg)//增加入口参数，手动添加
{	//初始化成员变量，手动添加
	m_pDlg=pDlg;
	m_pFile=NULL;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
}

CClientSocket::~CClientSocket()
{
	//置空或释放成员变量,手动添加
	m_pDlg=NULL;
	if (m_pFile!=NULL) delete m_pFile;
	if (m_pArchiveIn!=NULL) delete m_pArchiveIn;
	if (m_pArchiveOut!=NULL) delete m_pArchiveOut;
	m_pFile=NULL;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
}

// CClientSocket 成员函数
//套接字收到数据时，自动调用此函数
void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CSocket::OnReceive(nErrorCode);
	m_pDlg->onReceive(this);//调用主对话框中的处理函数，手动添加
}

void CClientSocket::Init(void)
{	//手动添加初始化代码
	m_pFile=new CSocketFile(this,TRUE);
	m_pArchiveIn=new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut=new CArchive(m_pFile,CArchive::store);
}
//发送消息
void CClientSocket::SendMessage(CMessage* pMsg)
{
	//手动添加
	if (m_pArchiveOut!=NULL)
	{
		pMsg->Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}
//接收消息
void CClientSocket::ReceiveMessage(CMessage* pMsg)
{
	pMsg->Serialize(*m_pArchiveIn);


}



