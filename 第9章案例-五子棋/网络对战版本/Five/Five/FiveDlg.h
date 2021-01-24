// FiveDlg.h : 头文件
#pragma once
#include "Table.h"
#include "FiveSocket.h" //手动添加

// CFiveDlg 对话框
class CFiveDlg : public CDialogEx
{
// 构造
public:
	CDialog * m_pDlg;
	CTable m_Table;
	CFiveDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FIVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuPlayerfirst();
	afx_msg void OnMenuPcfirst();
	afx_msg void OnBnClickedBtnBack();
	afx_msg void OnMenuServer();
	afx_msg void OnMenuClient();
	afx_msg void OnMenuPlayagain();
	afx_msg void OnMenuLeave();
	afx_msg void OnMenuName();
	afx_msg void OnMenuStat();
	afx_msg void OnClickedBtnQhq();
	afx_msg void OnClickedBtnLost();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_ChatList;
	HWND m_hChat;
	CString m_strChat;
};
