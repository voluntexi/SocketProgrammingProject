// FiveDlg.cpp : 实现文件
#include "stdafx.h"
#include "Five.h"
#include "FiveDlg.h"
#include "afxdialogex.h"

#include "ServerDlg.h"
#include "ClientDlg.h"
#include "NameDlg.h"
#include "StatDlg.h"
#include "Table.h"

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
{ }

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CFiveDlg 对话框
CFiveDlg::CFiveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFiveDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strChat = _T("");
}

void CFiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_CHAT, m_ChatList);
	DDX_CBString(pDX, IDC_CMB_CHAT, m_strChat);
}

BEGIN_MESSAGE_MAP(CFiveDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_ABOUT, &CFiveDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_PlayerFirst, &CFiveDlg::OnMenuPlayerfirst)
	ON_COMMAND(ID_MENU_PCFirst, &CFiveDlg::OnMenuPcfirst)
	ON_BN_CLICKED(IDC_BTN_BACK, &CFiveDlg::OnBnClickedBtnBack)
	ON_COMMAND(ID_MENU_SERVER, &CFiveDlg::OnMenuServer)
	ON_COMMAND(ID_MENU_CLIENT, &CFiveDlg::OnMenuClient)
	ON_COMMAND(ID_MENU_PLAYAGAIN, &CFiveDlg::OnMenuPlayagain)
	ON_COMMAND(ID_MENU_LEAVE, &CFiveDlg::OnMenuLeave)
	ON_COMMAND(ID_MENU_NAME, &CFiveDlg::OnMenuName)
	ON_COMMAND(ID_MENU_STAT, &CFiveDlg::OnMenuStat)
	ON_BN_CLICKED(IDC_BTN_QHQ, &CFiveDlg::OnClickedBtnQhq)
	ON_BN_CLICKED(IDC_BTN_LOST, &CFiveDlg::OnClickedBtnLost)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CFiveDlg 消息处理程序
BOOL CFiveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_pDlg = NULL;
    CRect rect(0, 0, 200, 200);
    m_Table.CreateEx( WS_EX_CLIENTEDGE, _T("ChessTable"), NULL, WS_VISIBLE | WS_BORDER | WS_CHILD,
        CRect( 0, 0, 480, 509 ), this, IDC_TABLE );
    // 设置双方姓名
    SetDlgItemText( IDC_ST_ME, m_Table.m_strMe );
    SetDlgItemText( IDC_ST_ENEMY, _T("计算机") );
    // 禁用“再玩”和“离开”
    CMenu *pMenu = GetMenu();
    pMenu->EnableMenuItem( ID_MENU_PLAYAGAIN, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );
    pMenu->EnableMenuItem( ID_MENU_LEAVE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );

	m_Table.Clear( TRUE );
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );

	//下面五行为网络对战新增部分
	 // 捕获聊天输入框句柄，供处理回车使用
	m_hChat = (HWND)FindWindowEx( GetDlgItem( IDC_CMB_CHAT )->GetSafeHwnd(), NULL, _T("Edit"), NULL );
	 ::SendMessage( m_hChat, EM_LIMITTEXT, (WPARAM)128, 0);
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );  
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );

	GetDlgItem(IDC_TABLE)->SetFocus();
	return FALSE;  // 除非将焦点设置到控件，否则返回TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CFiveDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	if (IsIconic())
	{
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
HCURSOR CFiveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//关于对话框
void CFiveDlg::OnMenuAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
    dlg.DoModal();
}
//玩家先走
void CFiveDlg::OnMenuPlayerfirst()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
	// 与电脑对弈，不允许和棋、聊天与认输
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
	m_Table.Accept( 1 );
}

//计算机先走
void CFiveDlg::OnMenuPcfirst()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
	// 与电脑对弈，不允许和棋、聊天与认输
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
	m_Table.SetColor( 1 );
    m_Table.Clear( FALSE );
    m_Table.SetGameMode( 1 );
}
//悔棋
void CFiveDlg::OnBnClickedBtnBack()
{
	// TODO: 在此添加控件通知处理程序代码
	 m_Table.Back();
}


void CFiveDlg::OnMenuServer()
{
	// TODO: 在此添加命令处理程序代码
	m_pDlg = new CServerDlg;
    m_pDlg->Create( IDD_DLG_SERVER, this );
    m_pDlg->ShowWindow( SW_SHOW );
}


void CFiveDlg::OnMenuClient()
{
	// TODO: 在此添加命令处理程序代码
    CClientDlg dlg;
    if ( IDOK == dlg.DoModal() )
    {
        // 发送己方姓名
        MSGSTRUCT msg;
        msg.uMsg = MSG_OPPOSITE;
        lstrcpy( msg.szMsg, m_Table.m_strMe );

        m_Table.m_clientSocket.Send( (LPCVOID)&msg, sizeof( MSGSTRUCT ) );
        // 设置按钮状态
        GetDlgItem( IDC_BTN_QHQ )->EnableWindow( TRUE );
        GetDlgItem( IDC_CMB_CHAT )->EnableWindow( TRUE );
        GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
        GetDlgItem( IDC_BTN_LOST )->EnableWindow( TRUE );
        // 设置菜单状态
        m_Table.SetMenuState( FALSE );
    }
}


void CFiveDlg::OnMenuPlayagain()
{
	// TODO: 在此添加命令处理程序代码
    m_Table.PlayAgain();
}


void CFiveDlg::OnMenuLeave()
{
	// TODO: 在此添加命令处理程序代码
	m_Table.m_serverSocket.Close();
    GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    // 设置菜单状态
    m_Table.SetMenuState( TRUE );
    // 设置棋盘等待状态
    m_Table.SetWait( TRUE );
    // 设置网络连接状态
    m_Table.m_bConnected = FALSE;
    // 重新设置对方名称
    SetDlgItemText( IDC_ST_ENEMY, _T("无玩家加入") );
}


void CFiveDlg::OnMenuName()
{
	// TODO: 在此添加命令处理程序代码
	CNameDlg dlg;
    if ( IDOK == dlg.DoModal() )
    {
        SetDlgItemText( IDC_ST_ME, m_Table.m_strMe );
    }
}


void CFiveDlg::OnMenuStat()
{
	// TODO: 在此添加命令处理程序代码
	CStatDlg dlg;
    dlg.DoModal();
}


void CFiveDlg::OnClickedBtnQhq()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Table.DrawGame();
}


void CFiveDlg::OnClickedBtnLost()
{
	// TODO: 在此添加控件通知处理程序代码
		m_Table.GiveUp();
}


BOOL CFiveDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    if ( GetDlgItem( IDC_EDT_CHAT ) == pWnd )
    {
        // 处理聊天记录的鼠标指针
        SetCursor( LoadCursor( NULL, IDC_ARROW ) );
        return TRUE;
    }
    else
		return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CFiveDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	  // 处理聊天输入窗口的回车消息
	    UpdateData(TRUE);
        // 发送聊天内容
        m_Table.Chat( m_strChat );
        // 加入聊天记录
        CString strAdd;
        strAdd.Format( _T("你 说：%s\r\n"), m_strChat );
        m_ChatList.SetSel( -1, -1, TRUE );
        m_ChatList.ReplaceSel( strAdd );
        // 清空聊天输入窗口
        m_strChat="";
		UpdateData(FALSE);
}


BOOL CFiveDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ( WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam && m_hChat == pMsg->hwnd )
    {
        // 处理聊天输入窗口的回车消息
        TCHAR str[128];
        // 发送聊天内容
        ::GetWindowText( m_hChat, str, 128 );
        m_Table.Chat( str );
        // 加入聊天记录
        CString strAdd;
        strAdd.Format( _T("你 说：%s\r\n"), str );
        m_ChatList.SetSel( -1, -1, TRUE );
        m_ChatList.ReplaceSel( strAdd );
        // 清空聊天输入窗口
        ::SetWindowText( m_hChat, _T("") );
    }
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CFiveDlg::OnCancel() 
{
    if ( IDYES == MessageBox( _T("确定要退出吗？"), _T("五子棋"), MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2 ) )
        CDialog::OnCancel();
}