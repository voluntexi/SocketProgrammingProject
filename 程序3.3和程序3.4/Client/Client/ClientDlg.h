// ClientDlg.h : ͷ�ļ�

#pragma once
#include "ClientSocket.h" //�ֶ���Ӱ������

// CClientDlg �Ի���
class CClientDlg : public CDialogEx
{
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//���´���ͨ���������
	CString m_strServerName;
	int m_nServerPort;
	CString m_strSpeaking;
	CString m_strUserName;
	CListBox m_listCRoom;
	afx_msg void OnClickedButtonLogin();
	afx_msg void OnClickedButtonLogout();
	afx_msg void OnClickedButtonSpeak();
	afx_msg void OnDestroy();
	CClientSocket* m_pSocket;
	CSocketFile* m_pFile;
	CArchive* m_pArchiveIn;
	CArchive* m_pArchiveOut;
	void onReceive(void);
	void ReceiveMessage(void);
	void SendMyMessage(CString& strMessage,BOOL bClosed);
};
