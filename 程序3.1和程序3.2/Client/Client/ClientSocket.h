// CClientSocket�ͻ����׽����ඨ��
#pragma once
class CClientDlg;
class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnConnect(int nErrorCode);//��ӦOnConnect�¼�
	virtual void OnReceive(int nErrorCode);//��ӦOnReceive�¼�
	virtual void OnClose(int nErrorCode);//��ӦOnClose�¼�
private:
	CClientDlg * m_pDlg;
public:
	void setParentDlg(CClientDlg* pDlg);
};

