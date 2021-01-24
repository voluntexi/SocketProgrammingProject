// ClientDlg.h : 头文件
#pragma once
#include "ClientSocket.h"
// CClientDlg 对话框
class CClientDlg : public CDialogEx
{
// 构造
public:
	CClientSocket m_sClientSocket;
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };

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
public:
	CString m_strServerName;
	CString m_strToServer;
	CListBox m_listReceived;
	CListBox m_listSent;
	int m_nServerPort;
	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonDisconnect();
	afx_msg void OnClickedButtonSend();

	void onConnect(void);
	void onReceived(void);
	void onClose(void);
};