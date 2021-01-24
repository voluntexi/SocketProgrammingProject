// ClientDlg.h : ͷ�ļ�
#pragma once
#include "ClientSocket.h"
// CClientDlg �Ի���
class CClientDlg : public CDialogEx
{
// ����
public:
	CClientSocket m_sClientSocket;
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

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
	CString m_strToServer;
	CListBox m_listReceived;
	CListBox m_listSent;
	int m_nServerPort;
	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonDisconnect();
	afx_msg void OnClickedButtonSend();

	void onConnect(void);
	void onReceived(void);
	void onClose(void);
};