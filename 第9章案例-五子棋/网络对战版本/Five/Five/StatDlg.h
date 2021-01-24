#pragma once
// CStatDlg 对话框

class CStatDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatDlg)
	void ShowStat(void);
public:
	CStatDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStatDlg();

// 对话框数据
	enum { IDD = IDD_DLG_STAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnClickedBtnReset();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
