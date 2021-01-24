#pragma once

// CNameDlg 对话框

class CNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CNameDlg)
	TCHAR m_strName[15];
public:
	CNameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNameDlg();

// 对话框数据
	enum { IDD = IDD_DLG_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnUpdateEditName();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
};
