// FiveDlg.h : ͷ�ļ�
#pragma once
#include "Table.h"

// CFiveDlg �Ի���
class CFiveDlg : public CDialogEx
{
// ����
public:
	CDialog * m_pDlg;
	CTable m_Table;
	CFiveDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FIVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuPlayerfirst();
	afx_msg void OnMenuPcfirst();
	afx_msg void OnBnClickedBtnBack();
};
