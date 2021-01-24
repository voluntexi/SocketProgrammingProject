// CClientSocket定义
#pragma once
class CServerDlg;
class CMessage;

class CClientSocket : public CSocket
{
public:
	CClientSocket(CServerDlg* pDlg);//为构造函数增加入口参数
	virtual ~CClientSocket();
	//重载回调函数，套接字收到数据时，自动调用此函数
	virtual void OnReceive(int nErrorCode);
	CServerDlg* m_pDlg;//定义指向主对话框类的指针
	CSocketFile* m_pFile; //定义指向CSocketFile对象的指针
	CArchive* m_pArchiveIn;//定义指向输入CArchive对象的指针
	CArchive* m_pArchiveOut;//定义指向输出CArchive对象的指针
	void SendMessage(CMessage* pMsg);//发送消息
	void ReceiveMessage(CMessage* pMsg);//接收消息
	void Init(void);//初始化
};


