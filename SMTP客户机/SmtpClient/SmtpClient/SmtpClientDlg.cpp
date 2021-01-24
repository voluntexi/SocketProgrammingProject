// SmtpClientDlg.cpp : 实现文件
#include "stdafx.h"
#include "SmtpClient.h"
#include "SmtpClientDlg.h"
#include "afxdialogex.h"

#define SMTP_MAXLINE  76

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSmtpClientDlg 对话框




CSmtpClientDlg::CSmtpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmtpClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strAttach = _T("");
	m_strBcc = _T("");
	m_strBody = _T("");
	m_strCopyTo = _T("");
	m_strPassword = _T("");
	m_strReceiver = _T("");
	m_strSender = _T("");
	m_nServerPort = 0;
	m_strSmtpServer = _T("");
	m_strTitle = _T("");
	m_strUserName = _T("");
}

void CSmtpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ATTACH, m_strAttach);
	DDX_Text(pDX, IDC_EDIT_BCC, m_strBcc);
	DDX_Text(pDX, IDC_EDIT_BODY, m_strBody);
	DDX_Text(pDX, IDC_EDIT_COPYTO, m_strCopyTo);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_RECEIVER, m_strReceiver);
	DDX_Text(pDX, IDC_EDIT_SENDER, m_strSender);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_nServerPort);
	DDX_Text(pDX, IDC_EDIT_SMTPSERVER, m_strSmtpServer);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
}

BEGIN_MESSAGE_MAP(CSmtpClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ATTACH, &CSmtpClientDlg::OnClickedButtonAttach)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSmtpClientDlg::OnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CSmtpClientDlg::OnClickedButtonCancel)
END_MESSAGE_MAP()


// CSmtpClientDlg 消息处理程序

BOOL CSmtpClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_strAttach = _T("");
	m_strBcc = _T("");
	m_strBody = _T("");
	m_strCopyTo = _T("");
	m_strPassword = _T("");
	m_strReceiver = _T("");
	m_strSender = _T("upsunny2008@163.com");
	m_nServerPort = 25;
	m_strSmtpServer = _T("smtp.163.com");
	m_strTitle = _T("");
	m_strUserName = _T("");
	UpdateData(FALSE);                 //更新用户界面
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSmtpClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSmtpClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSmtpClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSmtpClientDlg::OnClickedButtonAttach()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("All Files (*.*)|*.*||"));
	if (dlg.DoModal() == IDOK) 
	{
		CString sNewFile = dlg.GetPathName();
		if (m_strAttach.GetLength())
		{
			m_strAttach += _T(", ");
			m_strAttach += sNewFile;
		}
		else
			m_strAttach = sNewFile;
		UpdateData(FALSE);
	}
	LPSTR pszBody = NULL;
	int nBodySize = 0;
	if (!GetBody(pszBody, nBodySize))
	{
		TRACE(_T("Failed in call to send body parts body, GetLastError returns: %d\n"), GetLastError());
	}
	CString s;
	s = pszBody;
//	m_Info += s;
	UpdateData(FALSE);
}


void CSmtpClientDlg::OnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	//设定smtp类的变量，使之指向本对话框，以便传递信息
	smtpSocket.setParentDlg(this); 
	UpdateData(TRUE);    //取来用户在对话框中输入的数据
	smtpSocket.Create(); //创建套接字对象的底层套接字
	smtpSocket.Connect((LPCTSTR)m_strSmtpServer,m_nServerPort); //连接pop3服务器
	UpdateData(FALSE);          //更新用户界面

}


void CSmtpClientDlg::OnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
}
//根据不同的情况，向用户显示不同的信息
void CSmtpClientDlg::Disp(LONG flag)
{
	CString s;
	switch(flag)
	{
	case S_CONNECT: //已连接到服务器，显示信息
		s =_T("已经连接到")+m_strSmtpServer+_T("服务器\r\n");
		//m_Info += s;
		//m_listInfo.AddString(s);
		break;
	case S_RECEIVE: //收到服务器发来的数据,显示该数据
		//m_Info += smtpSocket.lastMsg;
		//m_listInfo.AddString(smtpSocket.lastMsg);
		break; 
	case S_CLOSE: //显示关闭连接的信息
		//m_Info += smtpSocket.error;
//		m_listInfo.AddString(smtpSocket.error);
		s = "连接已经关闭\r\n";
		//m_Info += s;
		//m_listInfo.AddString(s); 
		break;
	}
	UpdateData(FALSE);   //更新用户界面
}

void CSmtpClientDlg::GetHeader()
{
	UpdateData(TRUE);
	CString sepa;
	CString sReply;
	sReply = _T("");

	//创建 "Date:" 标题行内容
	CTime now(CTime::GetCurrentTime());
	CString sDate(now.Format(_T("%a, %d %b %Y %H:%M:%S ")));
	sDate +="+0800 (CST)";

	CString sBuf(sReply);
	if (m_strAttach.GetLength())
	{
		sReply.Format(_T("MIME-Version: 1.0\r\n"));
		sBuf += sReply;
	}

	//添加 From 和 to 字段
	//From: "=?GB2312?B?XXXXXXXXXX=?=" // 发信人，进行了编码
	//To: Li@163.com 

	coder.Encode(m_strSender);
	sReply.Format(_T("From: %s\r\n"), m_strSender);
//	sReply.Format(_T("From: =?gb2312?B?%s?=\r\n"), coder.EncodedMessage());
	sBuf += sReply;
	
	sReply.Format(_T("To: %s\r\n"),m_strReceiver);
	sBuf += sReply;

	//添加 Date字段
	//Date: Wed, 8 Apr 2004 16:16:16 +0800 // 发信的日期时间
	sReply.Format(_T("Date: %s\r\n"),sDate);
	sBuf += sReply;

	//添加 subject字段
	//Subject: =?GB2312?B?XXXXXX=?= // 主题，进行了编码
	coder.Encode(m_strTitle);
	sReply.Format(_T("Subject: %s\r\n"),m_strTitle);
//	sReply.Format(_T("Subject: =?gb2312?B?%s?=\r\n"),coder.EncodedMessage());
	sBuf += sReply;

	//如果有，添加 Cc 字段
	if (m_strCopyTo.GetLength())
	{
		sReply.Format(_T("Cc: %s\r\n"), m_strCopyTo);
		sBuf += sReply;
	}

	//如果有，添加Bcc 字段
	if (m_strBcc.GetLength())
	{
		sReply.Format(_T("Bcc: %s\r\n"), m_strBcc);
		sBuf += sReply;
	}

	//如果需要，添加 Mime 字段
	//MIME-Version: 1.0               // MIME版本
	//Content-type: multipart/mixed;  // 内容类型是多部分/混合型
	//boundary = "NextPart_000_00A"  // 指定一级边界特征字符串
	
	sepa= _T("Boundary-=_HfNFaIwtPvzJDUQrvChaEKIMklNx");
	if (m_strAttach.GetLength())
	{
//		sReply.Format(_T("MIME-Version: 1.0\r\n"));
//		sBuf += sReply;
		sReply.Format(_T("Content-Type:Multipart/mixed;boundary=%s\r\n"),sepa);
		sBuf += sReply;
		sBuf += _T("\r\n");
	} else {
		sBuf += _T("\r\n");
		sReply.Format(_T(" %s\r\n"), m_strBody);
		sBuf += sReply;
		sReply.Format(_T("%c%c.%c%c"),13,10,13,10);
		sBuf += sReply;
	}
	smtpSocket.Send((LPCTSTR)sBuf,sBuf.GetLength());
	//m_Info+=sBuf;

	if (m_strAttach.GetLength())
	{
		sReply.Format(_T("--%s\r\n"),sepa);
		sBuf = sReply;	
		
		sBuf += _T("Content-Type: text/plain; charset='gb2312'\r\n");
		sBuf += _T("Content-Transfer-Encoding: base64\r\n");
		sBuf += _T("\r\n");
		
		coder.Encode(m_strBody);
		sReply.Format(_T("%s\r\n"),coder.EncodedMessage());
		sBuf += sReply;
		
		sReply.Format(_T("--%s\r\n"), sepa);
		sBuf += sReply;

		sBuf += _T("Content-Type: text/plain; charset='gb2312'\r\n");
		sBuf += _T("Content-Transfer-Encoding: base64\r\n");
		sBuf += _T("\r\n");
		
		//add Letter	
		LPSTR pszBody = NULL;
		int nBodySize = 0;
		if (!GetBody(pszBody, nBodySize))
		{
			TRACE(_T("Failed in call to send body parts body, GetLastError returns: %d\n"), GetLastError());
		}
		sReply = pszBody;
		sBuf += sReply;
		sReply.Format(_T("--%s\r\n"), sepa);
		sBuf += sReply;
		
		sReply.Format(_T("%c%c.%c%c"),13,10,13,10);
		sBuf += sReply;
		smtpSocket.Send((LPCTSTR)sBuf,sBuf.GetLength());
		//m_Info+=sBuf;
	}
	UpdateData(FALSE);
}

BOOL CSmtpClientDlg::GetBody(LPSTR& pszBody, int& nBodySize)
{
	BOOL bSuccess = FALSE;

	//打开附件文件
	CFile infile;
	if (infile.Open(m_strAttach, CFile::modeRead | CFile::shareDenyWrite))
	{
		int fileSize = (int)infile.GetLength();
		if (fileSize)
		{
			//读入数据
			BYTE* pszIn = new BYTE[fileSize];
			try
			{
				infile.Read(pszIn, fileSize);
				bSuccess = TRUE;
			}
			catch(CFileException* pEx)
			{
				bSuccess = FALSE;
				pEx->Delete();
			}

			if (bSuccess)
			{
				coder.Encode(pszIn, fileSize); //编码
				delete [] pszIn;               //删除了输入缓冲区
				infile.Close();                //关闭输入文件

				//形成编码后的发送内容
				LPSTR pszEncoded = coder.EncodedMessage();
				int nEncodedSize = coder.EncodedMessageSize();
				nBodySize = nEncodedSize + (((nEncodedSize/76)+1)*2) + 1;
				pszBody = new char[nBodySize];
				--nBodySize; 

				int nInPos = 0;
				int nOutPos = 0;
				while (nInPos < nEncodedSize)
				{
					int nThisLineSize = min(nEncodedSize - nInPos, SMTP_MAXLINE);
					CopyMemory(&pszBody[nOutPos], &pszEncoded[nInPos], nThisLineSize);
					nOutPos += nThisLineSize;
					CopyMemory(&pszBody[nOutPos], "\r\n", 2);
					nOutPos += 2;
					nInPos += nThisLineSize;
				}
				pszBody[nOutPos] = '\0'; //以空字符串结束
			}
		}  else  {
			bSuccess = TRUE;
			pszBody = NULL;
			nBodySize = 0;
		}
	}  else
		TRACE(_T("No bodypart body text or filename specified!\n"));

	return bSuccess;
}