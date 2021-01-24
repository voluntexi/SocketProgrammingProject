// CClientSocket客户机套接字类定义
#pragma once
class CClientDlg;
class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnConnect(int nErrorCode);//响应OnConnect事件
	virtual void OnReceive(int nErrorCode);//响应OnReceive事件
	virtual void OnClose(int nErrorCode);//响应OnClose事件
private:
	CClientDlg * m_pDlg;
public:
	void setParentDlg(CClientDlg* pDlg);
};

