// ClientDlg.h : 头文件

#pragma once
#include "ClientSocket.h" //手动添加包含语句

// CClientDlg 对话框
class CClientDlg : public CDialogEx
{
public:
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };
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
public:
	//以下代码通过类向导添加
	CString m_strServerName;
	int m_nServerPort;
	CString m_strSpeaking;
	CString m_strUserName;
	CListBox m_listCRoom;
	afx_msg void OnClickedButtonLogin();
	afx_msg void OnClickedButtonLogout();
	afx_msg void OnClickedButtonSpeak();
	afx_msg void OnDestroy();
	CClientSocket* m_pSocket;
	CSocketFile* m_pFile;
	CArchive* m_pArchiveIn;
	CArchive* m_pArchiveOut;
	void onReceive(void);
	void ReceiveMessage(void);
	void SendMyMessage(CString& strMessage,BOOL bClosed);
};
