// ServerDlg.cpp : 实现文件
#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "Message.h"  //手动添加包含语句

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

// CServerDlg 对话框
CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nServerPort = 0;//类向导添加的成员变量初始化代码
	m_pServerSocket=NULL;//手动添加
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_nServerPort);
	DDV_MinMaxInt(pDX, m_nServerPort, 1024, 49151);
	DDX_Control(pDX, IDC_LIST_SROOM, m_listSroom);
	DDX_Control(pDX, IDC_STATIC_ONLINE, m_staOnline);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CServerDlg::OnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CServerDlg::OnClickedButtonStop)
END_MESSAGE_MAP()

// CServerDlg 消息处理程序
BOOL CServerDlg::OnInitDialog()
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
	m_nServerPort=10000;
	UpdateData(FALSE);//用成员变量值更新界面
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回TRUE
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//单击启动服务器按钮的事件处理函数
void CServerDlg::OnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//获得用户输入给成员变量
	//创建服务器套接字对象，用于在指定端口侦听
	m_pServerSocket=new CServerSocket(this);
	if (!m_pServerSocket->Create(m_nServerPort))
	{
		//错误处理
		delete m_pServerSocket;
		m_pServerSocket=NULL;
		AfxMessageBox(LPCTSTR("创建服务器侦听套接字出现错误！"));
		return;
	}
	//启动服务器侦听套接字，可以随时接收来自客户机的请求
	if (!m_pServerSocket->Listen())
	{
		//错误处理
		delete m_pServerSocket;
		m_pServerSocket=NULL;
		AfxMessageBox(LPCTSTR("启动服务器侦听套接字出现错误！"));
		return;
	}
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
}

//单击停止服务器按钮的事件处理函数
void CServerDlg::OnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	CMessage msg;
	msg.m_strMessage="服务器已停止侦听服务!";
	delete m_pServerSocket;//释放服务器侦听套接字
	m_pServerSocket=NULL;
	//清除客户机链接列表
	while(!m_ClientsList.IsEmpty())
	{
		//向每一个客户机发送"服务器已停止侦听服务!"这个消息并从列表中删除链接，释放资源
		CClientSocket* pSocket=(CClientSocket*)m_ClientsList.RemoveHead();
		pSocket->SendMessage(&msg);
		delete pSocket;
	}
	//清除服务器聊天室大厅
	while(m_listSroom.GetCount()!=0)
		m_listSroom.DeleteString(0);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
}

//服务器处理来自客户机的连接请求并在服务器端维护一个链接列表
void CServerDlg::onAccept(void)
{
	//创建服务器端连接客户机的套接字
	CClientSocket* pSocket=new CClientSocket(this);
	if (m_pServerSocket->Accept(*pSocket))
	{
		//建立客户机连接，加入客户机链接列表
		pSocket->Init();
		m_ClientsList.AddTail(pSocket);
		//更新在线人数
		CString strTemp;
		strTemp.Format(_T("当前在线人数：%d"),m_ClientsList.GetCount());
		m_staOnline.SetWindowTextW(strTemp);
	}else
	{
		delete pSocket;
		pSocket=NULL;
	}
}

//服务器处理来自客户机的消息
void CServerDlg::onReceive(CClientSocket* pSocket)
{
	static CMessage msg;
	
	do {
		pSocket->ReceiveMessage(&msg);//接收消息
		m_listSroom.AddString(msg.m_strMessage);//加入服务器列表框
		sendToClients(&msg);//转发给所有客户机
		//如果客户机关闭，从链接列表删除服务器端与之会话的链接套接字
		if (msg.m_bClosed)
		{
			//pSocket->Close();
			POSITION pos,temp;
			for(pos=m_ClientsList.GetHeadPosition();pos!=NULL;)
			{
				temp=pos;
				CClientSocket* pTempSocket=(CClientSocket*)m_ClientsList.GetNext(pos);
				if (pTempSocket==pSocket)
				{
					m_ClientsList.RemoveAt(temp);
					CString strTemp;
					//更新在线人数
					strTemp.Format(_T("当前在线人数：%d"),m_ClientsList.GetCount());
					m_staOnline.SetWindowTextW(strTemp);
					break;
				}//end if
			}//end for
			delete pSocket;
			pSocket=NULL;
			break;
		}//end if
	}while(!((pSocket->m_pArchiveIn)->IsBufferEmpty()));
}

//服务器向所有客户机转发来自某一客户机的消息
void CServerDlg::sendToClients(CMessage* pMsg)
{
	for (POSITION pos=m_ClientsList.GetHeadPosition();pos!=NULL;)
	{
		CClientSocket* pSocket1=(CClientSocket*)m_ClientsList.GetNext(pos);
		pSocket1->SendMessage(pMsg);
	}
}
