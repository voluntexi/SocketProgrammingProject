// ServerDlg.h : 头文件
#pragma once
#include "ServerSocket.h"

// CServerDlg 对话框
class CServerDlg : public CDialogEx
{
// 构造
public:
	CServerDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
//添加的成员变量和成员函数声明
public:
	CString m_strServerName;
	int m_nServerPort;
	CString m_strToClient;
	CListBox m_listReceived;
	CListBox m_listSent;
	afx_msg void OnClickedButtonCloselisten();
	afx_msg void OnClickedButtonListen();
	afx_msg void OnClickedButtonSend();
	CServerSocket m_sServerSocket;//服务器侦听套接字
	CServerSocket m_sClientSocket; //服务器用来与客户机连接的套接字
	CPtrList m_ClientsList;
	void onClose(void); //对应处理套接字的OnClose事件函数
	void onAccept(void); //对应处理套接字的OnAccept事件函数
	void onReceive(CServerSocket* pSocket); //对应处理套接字的OnReceive事件函数
};
