// FtpClientDlg.h : 头文件

#pragma once
#include "Afxinet.h"
// CFtpClientDlg 对话框
class CFtpClientDlg : public CDialogEx
{
public:
	CFtpClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FTPCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	//遍历目录
	void DisplayContent(LPCTSTR lpctstr,CString currentDir=_T("/"));
	CListCtrl m_listDirectory;
	void Download(void);//下载文件
	void Upload(void);//上传文件
	void Rename(void);//文件改名
	afx_msg void OnBnClickedButtonSubdir();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonParentdir();
	void DeleteFile(void);//删除文件
	void DisplaySubDir(void);//显示子目录
	CString GetParentDirectory(CString str);//返回父目录
	void DisplayParentDir(void);//显示父目录
	//连接服务器
	BOOL Connect(CString serverName, CString userName, CString password);
	
};
