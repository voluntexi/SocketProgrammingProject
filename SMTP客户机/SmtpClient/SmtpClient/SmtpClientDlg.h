// SmtpClientDlg.h : 头文件
#pragma once
#include "SmtpSocket.h"
#include "Base64.h"
// CSmtpClientDlg 对话框
class CSmtpClientDlg : public CDialogEx
{
// 构造
public:
	void Disp(LONG flag);//显示信息
	void GetHeader();   //创建电子邮件的头部


	CSmtpSocket smtpSocket;    //套接字类对象
	CSmtpClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SMTPCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	CBase64 coder;   //进行Base64编码的变量
	BOOL GetBody(LPSTR& pszBody, int& nBodySize);//构造邮件体

};
