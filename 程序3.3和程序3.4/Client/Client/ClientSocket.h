// CClientSocket定义
#pragma once
class CClientDlg;  //对话框类声明，手动添加
class CClientSocket : public CSocket
{
public:
	CClientSocket(CClientDlg* pDlg);//为构造函数添加入口参数，手动添加
	virtual ~CClientSocket();
	//下面两行由类向导生成
	CClientDlg* m_pDlg;//成员变量
	virtual void OnReceive(int nErrorCode);
};


