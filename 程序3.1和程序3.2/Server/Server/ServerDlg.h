// ServerDlg.h : ͷ�ļ�
#pragma once
#include "ServerSocket.h"

// CServerDlg �Ի���
class CServerDlg : public CDialogEx
{
// ����
public:
	CServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_SERVER_DIALOG };

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
//��ӵĳ�Ա�����ͳ�Ա��������
public:
	CString m_strServerName;
	int m_nServerPort;
	CString m_strToClient;
	CListBox m_listReceived;
	CListBox m_listSent;
	afx_msg void OnClickedButtonCloselisten();
	afx_msg void OnClickedButtonListen();
	afx_msg void OnClickedButtonSend();
	CServerSocket m_sServerSocket;//�����������׽���
	CServerSocket m_sClientSocket; //������������ͻ������ӵ��׽���
	CPtrList m_ClientsList;
	void onClose(void); //��Ӧ�����׽��ֵ�OnClose�¼�����
	void onAccept(void); //��Ӧ�����׽��ֵ�OnAccept�¼�����
	void onReceive(CServerSocket* pSocket); //��Ӧ�����׽��ֵ�OnReceive�¼�����
};
