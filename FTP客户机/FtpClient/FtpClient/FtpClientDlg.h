// FtpClientDlg.h : ͷ�ļ�

#pragma once
#include "Afxinet.h"
// CFtpClientDlg �Ի���
class CFtpClientDlg : public CDialogEx
{
public:
	CFtpClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FTPCLIENT_DIALOG };

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
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonUpload();
	CString m_strPassword;
	CString m_strServerName;
	CString m_strUserName;
	afx_msg void OnBnClickedButtonRename();
	afx_msg void OnBnClickedButtonQuery();
	afx_msg void OnBnClickedButtonDownload();
	afx_msg void OnBnClickedButtonLogout();

	CInternetSession* m_pFTPSession;
	CFtpConnection* m_pConnection;
	CFtpFileFind* m_pFileFind;
	//����Ŀ¼
	void DisplayContent(LPCTSTR lpctstr,CString currentDir=_T("/"));
	CListCtrl m_listDirectory;
	void Download(void);//�����ļ�
	void Upload(void);//�ϴ��ļ�
	void Rename(void);//�ļ�����
	afx_msg void OnBnClickedButtonSubdir();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonParentdir();
	void DeleteFile(void);//ɾ���ļ�
	void DisplaySubDir(void);//��ʾ��Ŀ¼
	CString GetParentDirectory(CString str);//���ظ�Ŀ¼
	void DisplayParentDir(void);//��ʾ��Ŀ¼
	//���ӷ�����
	BOOL Connect(CString serverName, CString userName, CString password);
	
};
