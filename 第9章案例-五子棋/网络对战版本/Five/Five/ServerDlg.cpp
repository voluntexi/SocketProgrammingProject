// ServerDlg.cpp : 实现文件

#include "stdafx.h"
#include "Five.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "Table.h"  //手动添加
// CServerDlg 对话框

IMPLEMENT_DYNAMIC(CServerDlg, CDialog)

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
}

CServerDlg::~CServerDlg()
{
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_LISTEN, &CServerDlg::OnClickedBtnListen)
	ON_BN_CLICKED(IDC_BTN_LEAVE, &CServerDlg::OnClickedBtnLeave)
END_MESSAGE_MAP()


// CServerDlg 消息处理程序


void CServerDlg::OnClickedBtnListen()
{
	// TODO: 在此添加控件通知处理程序代码
	CTable *pTable = (CTable *)GetParent()->GetDlgItem( IDC_TABLE );
    SetDlgItemText( IDC_ST_STATUS, _T("状态：等待其他玩家加入...") );
    pTable->m_serverSocket.Create( 20000 );
    pTable->m_serverSocket.Listen();
    GetDlgItem( IDC_BTN_LISTEN )->EnableWindow( FALSE );
	GetDlgItem( IDC_BTN_LEAVE )->EnableWindow(TRUE);
}


void CServerDlg::OnClickedBtnLeave()
{
	// TODO: 在此添加控件通知处理程序代码
	CTable *pTable = (CTable *)GetParent()->GetDlgItem( IDC_TABLE );
    pTable->m_serverSocket.Close();
	GetDlgItem( IDC_BTN_LISTEN )->EnableWindow(TRUE );
	GetDlgItem( IDC_BTN_LEAVE )->EnableWindow(FALSE);
}


BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
    // 首先禁用主窗口达到模式对话框的目的
    GetParent()->EnableWindow( FALSE );
    // 获取主机名及IP地址
    CHAR szHost[100];
    CHAR *szIP;
    hostent *host;
    gethostname(szHost, 100);
    SetDlgItemText( IDC_EDIT_HOST, (LPCTSTR)szHost );
    host = gethostbyname( szHost );
    for ( int i = 0; host != NULL && host->h_addr_list[i] != NULL; i++ )
    {
        szIP = inet_ntoa( *( (in_addr *)host->h_addr_list[i] ) );
        break;
    }
    SetDlgItemText( IDC_EDIT_IP, (LPCTSTR)szIP );

    GetDlgItem( IDC_BTN_LISTEN )->SetFocus();
	return FALSE; // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
