#pragma once

// CServerDlg 对话框

class CServerDlg : public CDialog
{
	DECLARE_DYNAMIC(CServerDlg)

public:
	CServerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServerDlg();

// 对话框数据
	enum { IDD = IDD_DLG_SERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnClickedBtnListen();
	afx_msg void OnClickedBtnLeave();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
