#pragma once


// CNewNameDlg 对话框

class CNewNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewNameDlg)

public:
	CNewNameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewNameDlg();

// 对话框数据
	enum { IDD = IDD_NEWNAMEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_NewFileName;
};
