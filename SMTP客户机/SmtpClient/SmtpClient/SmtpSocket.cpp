// SmtpSocket.cpp : 实现文件

#include "stdafx.h"
#include "SmtpClient.h"
#include "SmtpSocket.h"
#include  "SmtpClientDlg.h" //自己添加的包含语句
#include  "Base64.h"

#define MAX_BUFF 20000

CSmtpSocket::CSmtpSocket()
{
	m_pDlg = NULL;
	state=FIRST;
	error="连接不上服务器\r\n";
}
CSmtpSocket::~CSmtpSocket()
{
	m_pDlg = NULL;
}


// CSmtpSocket 成员函数
void CSmtpSocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnConnect(nErrorCode);
	if(nErrorCode==0)  m_pDlg->Disp(S_CONNECT);
}


void CSmtpSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnReceive(nErrorCode);
	if(nErrorCode==0) 
	{
		char buff[MAX_BUFF];             //接收缓冲区
		int rec=Receive(buff,MAX_BUFF);  //接收服务器发来的数据
		buff[rec]=NULL;                  //结尾置为NULL。
		lastMsg=buff;
		AnalyzeMsg();             //分析收到的数据，作不同的处理
	}  else  {
		error="接收期间发生了错误!\r\n";
		m_pDlg->Disp(S_CLOSE);   //显示信息
	}
}

void CSmtpSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnClose(nErrorCode);
	if(nErrorCode==0)  m_pDlg->Disp(S_CLOSE);
	
	CString str;
	str.Format("quit%c%c",13,10);
	Send((LPCSTR)str,str.GetLength());
	m_pDlg->Disp(S_CLOSE);
	state=FIRST;
	CAsyncSocket::Close();
	error="与服务器的连接已经断开\r\n";
	
}

void CSmtpSocket::setParentDlg(CSmtpClientDlg* p_Dlg)
{
	m_pDlg = p_Dlg;
}

//与服务器实现SMTP会话
void CSmtpSocket::AnalyzeMsg()
{
	CString s;
	strstream str;
	string check;
	str<<(LPCTSTR)lastMsg;
	str>>check;

	//根据smtp会话所处的状态做出不同的处理	
	switch(state)
	{
	case FIRST: //如果已经连接成功，类初始化的时候state为FIRST
		m_pDlg->Disp(S_RECEIVE); //发送消息到窗体
		if(!(check=="220")) {}
		s.Format(_T("EHLO %s%c%c"),m_pDlg->m_strUserName,13,10);
		Send((LPCTSTR)s,s.GetLength()); //发送EHLO命令
		state=EHLO;
		break;

	case EHLO:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
		s.Format(_T("AUTH LOGIN%c%c"),13,10); 
		Send((LPCTSTR)s,s.GetLength()); //发送AUTH LOGIN命令
		state=AUTH;
		break;

	case AUTH:
		m_pDlg->Disp(S_RECEIVE);
		//if(!(check=="334")) {}
		coder.Encode(m_pDlg->m_strUserName);
		s.Format(_T("%s%c%c"), coder.EncodedMessage(),13,10);
	AfxMessageBox(s);

//		s.Format("bXVfbA==%c%c",13,10);  ///mu_l
//		s.Format("bXVfbGxs%c%c",13,10);  //mu_lll
		Send((LPCTSTR)s,s.GetLength()); //发送用户名
		state=USER; 
		break;

	case USER:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="334")) {}
		
		coder.Encode(m_pDlg->m_strPassword);
		s.Format(_T("%s%c%c"), coder.EncodedMessage(),13,10);
//	AfxMessageBox(s);
//		s.Format("NDkxMDE1%c%c",13,10); //491015
		Send((LPCTSTR)s,s.GetLength()); //发送口令
		state=PASS;
		break;

	case PASS:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="235")) {}
		s.Format(_T("MAIL FROM:<%s>%c%c"),m_pDlg->m_strSender,13,10); 
//		s.Format("MAIL FROM:<mu_lm@sina.com>%c%c",13,10); 
		Send((LPCTSTR)s,s.GetLength()); //发送MAIL FROM命令
		state=MAIL;
		break;
	case MAIL:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
//		s.Format("RCPT TO: <mu_lm@sina.com>%c%c",13,10); 
		s.Format(_T("RCPT TO: <%s>%c%c"),m_pDlg->m_strReceiver,13,10); 
		Send((LPCTSTR)s,s.GetLength()); //发送RECP命令
		state=RCPT;
		break;
	case RCPT: 
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
		s.Format(_T("DATA%c%c"),13,10); 
		Send((LPCTSTR)s,s.GetLength()); //发送DATA命令
		state=DATA;
		break;
	case DATA: 
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="354")) {}
//		s.Format("From: %s%c%c",m_pDlg->m_Addr,13,10); 
//		Send((LPCSTR)s,s.GetLength()); //发送信件内容
	
//	s.Format("To: %s%c%c",m_pDlg->m_Receiver,13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("Date: Tue,04 Dec 2005 16:18:08 +800%c%c",13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("Subject: %s%c%c",m_pDlg->m_Title,13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("%c%c",13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("%s%c%c",m_pDlg->m_Letter,13,10); 
//	Send((LPCSTR)s,s.GetLength());

//		s.Format("%c%c.%c%c",13,10,13,10); 
//		Send((LPCSTR)s,s.GetLength());

		m_pDlg->GetHeader();
		state=QUIT;
		break;
	case QUIT: 
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
		s.Format(_T("QUIT%c%c"),13,10); 
		Send((LPCTSTR)s,s.GetLength()); //发送QUIT命令
		state=DATA;
		break;
	default:
		m_pDlg->Disp(S_RECEIVE);
		break;
	}
}
