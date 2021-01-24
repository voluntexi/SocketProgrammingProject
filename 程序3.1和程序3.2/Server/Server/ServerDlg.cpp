// ServerDlg.cpp : 实现文件
#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

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
	m_strServerName = _T("");
	m_nServerPort = 0;
	m_strToClient = _T("");
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_nServerPort);
	DDV_MinMaxInt(pDX, m_nServerPort, 1024, 49151);
	DDX_Text(pDX, IDC_EDIT_TOCLIENT, m_strToClient);
	DDX_Control(pDX, IDC_LIST_RECEIVED, m_listReceived);
	DDX_Control(pDX, IDC_LIST_SENT, m_listSent);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLOSELISTEN, &CServerDlg::OnClickedButtonCloselisten)
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CServerDlg::OnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CServerDlg::OnClickedButtonSend)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_strServerName="localhost";
	m_nServerPort=1024;
	UpdateData(FALSE);
	m_sServerSocket.setParentDlg(this);
	m_sClientSocket.setParentDlg(this);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServerDlg::OnClickedButtonCloselisten()
{
	// TODO: 在此添加控件通知处理程序代码
	//onClose();
	m_sClientSocket.Close();
	m_sServerSocket.Close();
	m_listReceived.AddString(CString("服务器断开了侦听"));

}

void CServerDlg::OnClickedButtonListen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	m_sServerSocket.Create(m_nServerPort);
	m_sServerSocket.Listen();

	GetDlgItem(IDC_EDIT_TOCLIENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSELISTEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	
}

void CServerDlg::OnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	int nMsgLen;
	int nSentLen;
	int flag=0;
	UpdateData(TRUE);
	
	if(!m_strToClient.IsEmpty())
	{
		for (POSITION pos=m_ClientsList.GetHeadPosition();pos!=NULL;)
	{
		CServerSocket* pSocket=(CServerSocket*)m_ClientsList.GetNext(pos);


		nMsgLen=m_strToClient.GetLength()*sizeof(m_strToClient);
		nSentLen=pSocket->Send(m_strToClient,nMsgLen);
		if (nSentLen!=SOCKET_ERROR) { //发送成功
			if ( flag==0)
			{
			m_listSent.AddString(m_strToClient);
			flag=1;
			} 
			
		} else {
			AfxMessageBox(LPCTSTR("服务器向客户机发送信息出现错误！"),MB_OK|MB_ICONSTOP);
		}
		}//end for
		UpdateData(FALSE);
		m_strToClient.Empty();
		UpdateData(FALSE);
	}//end if
}
//从套接字的OnClose事件函数里转到此处执行
void CServerDlg::onClose(void)
{
	m_listReceived.AddString(CString("服务器收到了OnClose消息"));
	m_sClientSocket.Close();
	m_sServerSocket.Close();
	GetDlgItem(IDC_EDIT_TOCLIENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSELISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
}
//从套接字的OnAccept事件函数里转到此处执行
void CServerDlg::onAccept(void)
{
	m_listReceived.AddString(CString("服务器收到了OnAccept消息"));
	CServerSocket * pClientSocket=new CServerSocket();
	m_sServerSocket.Accept(*pClientSocket);
	pClientSocket->setParentDlg(this);
	m_ClientsList.AddTail(pClientSocket);

	GetDlgItem(IDC_EDIT_TOCLIENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSELISTEN)->EnableWindow(TRUE);
}
//从套接字的OnReceive事件函数里转到此处执行
void CServerDlg::onReceive(CServerSocket* pSocket )
{
	TCHAR buff[4096];
	int nBufferSize=4096;
	int nReceivedLen;
	CString strReceived;
	m_listReceived.AddString(CString("服务器收到了OnReceive消息"));
	//m_ClientsList
	/*for (POSITION pos=m_ClientsList.GetHeadPosition();pos!=NULL;)
	{
		CServerSocket* pSocket=(CServerSocket*)m_ClientsList.GetNext(pos);*/
		//pSocket->SendMessage(pMsg);
		nReceivedLen=pSocket->Receive(buff,nBufferSize);
	if(nReceivedLen!=SOCKET_ERROR)
	{
		buff[nReceivedLen]=_T('\0');
		CString szTemp(buff);
		strReceived=szTemp;
		m_listReceived.AddString(strReceived);
		UpdateData(FALSE);
	}else {
		AfxMessageBox(LPCTSTR("服务器从客户机接收信息出现错误！"),MB_OK|MB_ICONSTOP);
	}
	
//}
}