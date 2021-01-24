#pragma once
#include "Table.h"  // 手动添加

// CClientDlg 对话框

class CClientDlg : public CDialog
{
	DECLARE_DYNAMIC(CClientDlg)

public:
	CClientDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClientDlg();

// 对话框数据
	enum { IDD = IDD_DLG_CLIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnClickedBtnConnect();
	afx_msg void OnClickedBtnOut();
	afx_msg void OnUpdateEditHost();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnOK();
private:
	int m_nTimer;
	CTable* m_pTable;
};
