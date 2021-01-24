
// Pop3ClientDlg.h : 头文件
//

#pragma once
#include "resource.h"//手动添加包含语句
#include "Pop3ClientSocket.h"

// CPop3ClientDlg 对话框
class CPop3ClientDlg : public CDialogEx
{
// 构造
public:
	CPop3ClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_POP3CLIENT_DIALOG };

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
	CString m_strMailBox;
	CString m_strPassword;
	CComboBox m_comboTitle;
	CRichEditCtrl m_MailContent;
	BOOL m_bDelMail;
//	CString m_mailInfo;
	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonDisconnect();
	afx_msg void OnClickedButtonBrowsemail();
	afx_msg void OnClickedButtonSavemail();
	void DisplayInfo(LONG flag);
	CPop3ClientSocket m_pop3ClientSocket;
	CString m_mailInfo;
};
