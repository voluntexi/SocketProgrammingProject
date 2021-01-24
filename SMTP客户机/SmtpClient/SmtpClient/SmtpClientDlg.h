// SmtpClientDlg.h : ͷ�ļ�
#pragma once
#include "SmtpSocket.h"
#include "Base64.h"
// CSmtpClientDlg �Ի���
class CSmtpClientDlg : public CDialogEx
{
// ����
public:
	void Disp(LONG flag);//��ʾ��Ϣ
	void GetHeader();   //���������ʼ���ͷ��


	CSmtpSocket smtpSocket;    //�׽��������
	CSmtpClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SMTPCLIENT_DIALOG };

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
	CString m_strAttach;
	CString m_strBcc;
	CString m_strBody;
	CString m_strCopyTo;
	CString m_strPassword;
	CString m_strReceiver;
	CString m_strSender;
	int m_nServerPort;
	CString m_strSmtpServer;
	CString m_strTitle;
	CString m_strUserName;
	afx_msg void OnClickedButtonAttach();
	afx_msg void OnClickedButtonSend();
	afx_msg void OnClickedButtonCancel();
private:
	CBase64 coder;   //����Base64����ı���
	BOOL GetBody(LPSTR& pszBody, int& nBodySize);//�����ʼ���

};
