// ServerDlg.h : ͷ�ļ�
#pragma once
#include "ServerSocket.h"
#include "ClientSocket.h"

class CMessage;

// CServerDlg �Ի���
class CServerDlg : public CDialogEx
{
public:
	CServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_SERVER_DIALOG };
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
//���´���ͨ�������ֶ����
public:
	int m_nServerPort;
	CListBox m_listSroom;
	CStatic m_staOnline;
	afx_msg void OnClickedButtonStart();
	afx_msg void OnClickedButtonStop();
	CServerSocket* m_pServerSocket;//�����׽���ָ�����
	CPtrList m_ClientsList; //���߿ͻ�������
	void onAccept(void);//����ͻ����������󣬴�CServerSocket���OnAccept����ת���˴�ִ��
	void onReceive(CClientSocket* pSocket);//��ȡ�ͻ������͵����ݣ���CClientSocket���OnReceive����ת���˴�ִ��
	void sendToClients(CMessage* pMsg);//�����������пͻ���ת����Ϣ
};
