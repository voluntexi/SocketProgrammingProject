// ServerDlg.h : 头文件
#pragma once
#include "ServerSocket.h"
#include "ClientSocket.h"

class CMessage;

// CServerDlg 对话框
class CServerDlg : public CDialogEx
{
public:
	CServerDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_SERVER_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
//以下代码通过类向导手动添加
public:
	int m_nServerPort;
	CListBox m_listSroom;
	CStatic m_staOnline;
	afx_msg void OnClickedButtonStart();
	afx_msg void OnClickedButtonStop();
	CServerSocket* m_pServerSocket;//侦听套接字指针变量
	CPtrList m_ClientsList; //在线客户机链表
	void onAccept(void);//处理客户机连接请求，从CServerSocket类的OnAccept函数转到此处执行
	void onReceive(CClientSocket* pSocket);//获取客户机发送的数据，从CClientSocket类的OnReceive函数转到此处执行
	void sendToClients(CMessage* pMsg);//服务器向所有客户机转发消息
};
