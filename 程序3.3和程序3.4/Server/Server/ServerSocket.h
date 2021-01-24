// CServerSocket定义
#pragma once
class CServerDlg; //声明服务器对话框类
class CServerSocket : public CSocket
{
public:
	CServerSocket(CServerDlg* pDlg);//添加入口参数
	virtual ~CServerSocket();
	//回调函数，套接字收到连接请求时，自动调用此函数
	virtual void OnAccept(int nErrorCode);
	CServerDlg* m_pDlg; //指向服务器对话框类的指针
};


