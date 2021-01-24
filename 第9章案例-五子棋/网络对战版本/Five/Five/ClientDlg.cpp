// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Five.h"
#include "ClientDlg.h"
#include "afxdialogex.h"


// CClientDlg 对话框

IMPLEMENT_DYNAMIC(CClientDlg, CDialog)

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{

	m_nTimer = 0;
}

CClientDlg::~CClientDlg()
{
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CClientDlg::OnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_OUT, &CClientDlg::OnClickedBtnOut)
	ON_EN_UPDATE(IDC_EDIT_HOST, &CClientDlg::OnUpdateEditHost)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

void CClientDlg::OnClickedBtnConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	 CString strHost;

    // 获取主机名称
    GetDlgItemText( IDC_EDIT_HOST, strHost );
    // 设置超时时间
    m_nTimer = 5;
    // 初始化连接状态
    m_pTable->m_bConnected = FALSE;
    // 设置控件生效状态
    GetDlgItem( IDC_BTN_CONNECT )->EnableWindow( FALSE );
    GetDlgItem( IDC_EDIT_HOST )->EnableWindow( FALSE );
    // 创建套接字并连接
    m_pTable->m_clientSocket.Create();
    m_pTable->m_clientSocket.Connect( strHost, 20000 );
    // 开始计时
    SetTimer( 1, 1000, NULL );
}


void CClientDlg::OnClickedBtnOut()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer( 1 );
	OnCancel();
}


void CClientDlg::OnUpdateEditHost()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	    // 如果无主机名，则使“连接”按钮失效
	CString str;
    GetDlgItemText( IDC_EDIT_HOST, str );
    GetDlgItem( IDC_BTN_CONNECT )->EnableWindow( !str.IsEmpty() );
}


BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText( IDC_ST_TIMER, _T("") );
    m_pTable = (CTable *)GetParent()->GetDlgItem( IDC_TABLE );
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		if ( 1 == nIDEvent )
    {
        if ( m_pTable->m_bConnected )
        {
            KillTimer( 1 );
            EndDialog( IDOK );
        }
        else if ( 0 == m_nTimer )
        {
            KillTimer( 1 );
            MessageBox( _T("连接对方失败，请检查主机名或IP地址是否正确，以及网络连接是否正常。"),
                _T("连接失败"), MB_ICONERROR );
            SetDlgItemText( IDC_ST_TIMER, _T("") );
            GetDlgItem( IDC_EDIT_HOST )->EnableWindow();
            SetDlgItemText( IDC_EDIT_HOST, _T("") );
            GetDlgItem( IDC_EDIT_HOST )->SetFocus();
        }
        else
        {
            CString str;
            str.Format( _T("正在连接...(%d)"), m_nTimer-- );
            SetDlgItemText( IDC_ST_TIMER, str);
        }
    }
	CDialog::OnTimer(nIDEvent);
}


void CClientDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	// 屏蔽OnOK，使按回车的时候不退出
	CDialog::OnOK();
}
