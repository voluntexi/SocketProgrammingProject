
// Pop3ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"//�ֶ���Ӱ������
#include "Pop3ClientSocket.h"

// CPop3ClientDlg �Ի���
class CPop3ClientDlg : public CDialogEx
{
// ����
public:
	CPop3ClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_POP3CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
