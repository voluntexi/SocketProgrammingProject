// ClientDlg.cpp : 实现文件
#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"//手动添加包含语句
#include "Message.h"

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 对话框数据
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CClientDlg 对话框
CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//类向导自动添加的初始化代码
	m_strServerName = _T("");
	m_nServerPort = 0;
	m_strSpeaking = _T("");
	m_strUserName = _T("");
	//手动添加的初始化代码
	m_pSocket=NULL;
	m_pFile=NULL;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_nServerPort);
	DDV_MinMaxInt(pDX, m_nServerPort, 1024, 49151);
	DDX_Text(pDX, IDC_EDIT_SPEAKING, m_strSpeaking);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Control(pDX, IDC_LIST_CROOM, m_listCRoom);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CClientDlg::OnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CClientDlg::OnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_SPEAK, &CClientDlg::OnClickedButtonSpeak)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CClientDlg 消息处理程序
BOOL CClientDlg::OnInitDialog()
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
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	//手动添加如下初始化代码：
	m_strUserName=_T("智慧树");
	m_strServerName=_T("localhost");
	m_nServerPort=10000;
	UpdateData(FALSE);//更新对应控件数据
	GetDlgItem(IDC_EDIT_SPEAKING)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOGOUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SPEAK)->EnableWindow(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CClientDlg::OnPaint()
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

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//以下所有函数的框架由类向导生成，其实现代码需要手动添加
void CClientDlg::OnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pSocket=new CClientSocket(this);//创建套接字
	if (!m_pSocket->Create())
	{
		//错误处理
		delete m_pSocket;
		m_pSocket=NULL;
		AfxMessageBox(_T("创建连接服务器的套接字错误,登录失败！"));
		return;
	}
	if (!m_pSocket->Connect(m_strServerName,m_nServerPort))
	{
		//错误处理
		delete m_pSocket;
		m_pSocket=NULL;
		AfxMessageBox(_T("连接服务器错误,登录失败！"));
		return;
	}
	m_pFile=new CSocketFile(m_pSocket);
	m_pArchiveIn=new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut=new CArchive(m_pFile,CArchive::store);
	//向服务器发送消息，表明新客户进入聊天室
	UpdateData(TRUE);//更新控件成员变量
	CString strTemp;
	strTemp=m_strUserName+_T("：昂首挺胸进入聊天室!!!");
	SendMyMessage(strTemp,FALSE);

	GetDlgItem(IDC_EDIT_SPEAKING)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOGOUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SPEAK)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(FALSE);
	
}
//单击退出按钮的响应函数
void CClientDlg::OnClickedButtonLogout()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp;
	strTemp=m_strUserName+_T("：大步流星离开聊天室......");
	SendMyMessage(strTemp,TRUE);
	//删除对象，释放空间
	delete m_pArchiveIn;
	delete m_pArchiveOut;
	delete m_pFile;
	delete m_pSocket;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
	m_pFile=NULL;
	m_pSocket=NULL;

	//清除聊天室内容
	while (m_listCRoom.GetCount()!=0) 
		m_listCRoom.DeleteString(0);
	GetDlgItem(IDC_EDIT_SPEAKING)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOGOUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SPEAK)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(TRUE);
}

//单击发言按钮的响应函数
void CClientDlg::OnClickedButtonSpeak()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//更新控件成员变量，取回用户输入的数据
	if (!m_strSpeaking.IsEmpty()) //发言输入框不空
	{
		SendMyMessage(m_strUserName+"大声说："+m_strSpeaking,FALSE);
		m_strSpeaking=_T("");
		UpdateData(FALSE);//更新用户界面，发言框清空
	}
}
//关闭客户机时的善后处理函数
void CClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
	if ((m_pSocket!=NULL) && (m_pFile!=NULL) && (m_pArchiveOut!=NULL))
	{
		CMessage msg;
		CString strTemp;
		strTemp=_T("广而告之：")+m_strUserName+_T("所在客户机已关闭");
		msg.m_strMessage=strTemp;
		msg.m_bClosed=TRUE;
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();

		//删除对象，释放空间
		delete m_pArchiveIn;
		delete m_pArchiveOut;
		delete m_pFile;
		m_pArchiveIn=NULL;
		m_pArchiveOut=NULL;
		m_pFile=NULL;

		if (m_pSocket!=NULL)
		{
			BYTE buffer[100];
			m_pSocket->ShutDown();
			while (m_pSocket->Receive(buffer,100)>0);
		}
		delete m_pSocket;
		m_pSocket=NULL;
	}
}

//当套接字收到FD_READ消息时，它的OnReceive函数调用此函数
void CClientDlg::onReceive(void)
{
	do {
		ReceiveMessage();//接收消息
		if (m_pSocket==NULL) return;
	}while(!m_pArchiveIn->IsBufferEmpty());

}

//接收消息处理函数
void CClientDlg::ReceiveMessage(void)
{
	CMessage msg;
	TRY {
		msg.Serialize(*m_pArchiveIn);//接收
		m_listCRoom.AddString(msg.m_strMessage);//显示在大厅
	}CATCH(CFileException, e) { 
		//错误处理
		CString strTemp;
		strTemp=_T("与服务器连接已断开，连接关闭！");
		m_listCRoom.AddString(strTemp);
		msg.m_bClosed=TRUE;
		m_pArchiveOut->Abort();
		//删除对象，释放空间
		delete m_pArchiveIn;
		delete m_pArchiveOut;
		delete m_pFile;
		delete m_pSocket;
		m_pArchiveIn=NULL;
		m_pArchiveOut=NULL;
		m_pFile=NULL;
		m_pSocket=NULL;
	}
	END_CATCH 

}

//发送消息的处理函数
void CClientDlg::SendMyMessage(CString& strMessage,BOOL bClosed)
{
	if (m_pArchiveOut!=NULL) {
		CMessage msg;
		msg.m_strMessage=strMessage;
		msg.m_bClosed=bClosed;
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}
