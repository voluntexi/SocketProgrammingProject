#pragma once


// CNewNameDlg �Ի���

class CNewNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewNameDlg)

public:
	CNewNameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewNameDlg();

// �Ի�������
	enum { IDD = IDD_NEWNAMEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_NewFileName;
};
