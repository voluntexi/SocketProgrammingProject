
// Pop3ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Pop3Client.h"
#include "Pop3ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CPop3ClientDlg 对话框




CPop3ClientDlg::CPop3ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPop3ClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strServerName = _T("");
	m_strMailBox = _T("");
	m_strPassword = _T("");
	//  m_mailInfo = _T("");
	m_mailInfo = _T("");
}

void CPop3ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_EDIT_MAILBOX, m_strMailBox);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Control(pDX, IDC_COMBO_TITLE, m_comboTitle);
	DDX_Control(pDX, IDC_RICHEDIT_MAILCONTENT, m_MailContent);
	DDX_Check(pDX, IDC_CHECK_DELMAIL, m_bDelMail);
	DDX_Text(pDX, IDC_RICHEDIT_MAILCONTENT, m_mailInfo);
}

BEGIN_MESSAGE_MAP(CPop3ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CPop3ClientDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CPop3ClientDlg::OnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_BROWSEMAIL, &CPop3ClientDlg::OnClickedButtonBrowsemail)
	ON_BN_CLICKED(IDC_BUTTON_SAVEMAIL, &CPop3ClientDlg::OnClickedButtonSavemail)
END_MESSAGE_MAP()


// CPop3ClientDlg 消息处理程序

BOOL CPop3ClientDlg::OnInitDialog()
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
	m_strServerName = _T("pop3.sohu.com");
	m_strMailBox = _T("yantaidxz@sohu.com");
	m_strPassword = _T("zzz2013");
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPop3ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPop3ClientDlg::OnPaint()
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
HCURSOR CPop3ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPop3ClientDlg::OnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	
	
	m_pop3ClientSocket.SetParentDlg(this); 
	UpdateData(TRUE);  
	m_pop3ClientSocket.Create();   //创建套接字对象的底层套接字
	m_pop3ClientSocket.Connect((LPCSTR)m_strServerName,110); //连接pop3服务器
	m_bDelMail=FALSE;
	m_mailInfo = "";                //多文本列表框清空
	m_MailContent.Clear();
	UpdateData(FALSE);          //更新用户界面
}


void CPop3ClientDlg::OnClickedButtonDisconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pop3ClientSocket.Close();
}


void CPop3ClientDlg::OnClickedButtonBrowsemail()
{
	// TODO: 在此添加控件通知处理程序代码
	int index;
	index = m_comboTitle.GetCurSel();  //获得用户在组合框中的选择
	//获得并显示指定信件的基本属性及信件内容
	m_mailInfo += m_pop3ClientSocket.GetMsgStuff(index);
	m_mailInfo += m_pop3ClientSocket.GetMsgBody(index);
//	CString s;
//	for(int i=0;i<m_pop3ClientSocket.retrMsg;i++)
//	{
//		s.Format("%c%c第 %d 封信 %c%c",13,10,i,13,10);
//		m_mailInfo +=s;
//		m_mailInfo += m_pop3ClientSocket.msgs[i].text;
//	}
	UpdateData(FALSE);
}


void CPop3ClientDlg::OnClickedButtonSavemail()
{
	// TODO: 在此添加控件通知处理程序代码
	int index;
	CString s;
	index = m_comboTitle.GetCurSel();
	//获得指定信件的基本属性及信件内容
	s = m_pop3ClientSocket.GetMsgStuff(index);
	s += m_pop3ClientSocket.GetMsgBody(index);
	
	CFileDialog dlg(FALSE);
	if(dlg.DoModal()==IDOK)
	{
		CFile file(dlg.GetPathName(),
			CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		file.Write((LPCSTR)s,s.GetLength());
		file.Close();
	}
}


void CPop3ClientDlg::DisplayInfo(LONG flag)
{
	CString s;
	switch(flag)
	{
	case S_CONNECT: //已连接到服务器，显示信息
		s = "已连接到"+m_strServerName+"...\r\n";
		m_mailInfo+=s;
		//禁用连接按钮
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
		//启用断开按钮
		GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(TRUE); 
		//禁用查看邮件按钮
		GetDlgItem(IDC_BUTTON_BROWSEMAIL)->EnableWindow(FALSE);
		break;
	case S_RECEIVE: //收到服务器发来的响应，显示它的内容
		m_mailInfo+=m_pop3ClientSocket.lastMsg;
		break; 
	case S_CLOSE: //显示关闭连接的信息
		m_mailInfo+=m_pop3ClientSocket.error;
		s = "连接已经关闭\r\n";
		m_mailInfo+=s;
		//启用连接按钮
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
		//禁用断开按钮
		GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(FALSE);
		break;
	case S_GETNUM: //已经知道了邮箱中信件的总数
		s.Format("邮箱中共有 %d 封信\r\n",m_pop3ClientSocket.numMsg);
		m_mailInfo+=s;
		break;
	case S_GETSIZE: //显示信件的大小
		s.Format("信箱中信件大小为：%d字节\r\n",m_pop3ClientSocket.sizeMsg);
		m_mailInfo+=s;
		break;
	case S_ENDRETR: //所有信件已下载完毕，显示信息
		s.Format("共下载了 %d 封信件\r\n",m_pop3ClientSocket.msgs.size());
		m_mailInfo+=s;
		//如果有信件下载，启用查看邮件按钮
		if((m_pop3ClientSocket.msgs.size())>0)
			GetDlgItem(IDC_BUTTON_BROWSEMAIL)->EnableWindow(TRUE);
		break;
	}
	UpdateData(FALSE);   //更新用户界面
}
