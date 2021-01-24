// NameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Five.h"
#include "NameDlg.h"
#include "afxdialogex.h"
#include "Table.h" //手动添加

// CNameDlg 对话框

IMPLEMENT_DYNAMIC(CNameDlg, CDialog)

CNameDlg::CNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNameDlg::IDD, pParent)
{

}

CNameDlg::~CNameDlg()
{
}

void CNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNameDlg, CDialog)
	ON_EN_UPDATE(IDC_EDIT_NAME, &CNameDlg::OnUpdateEditName)
END_MESSAGE_MAP()


// CNameDlg 消息处理程序


void CNameDlg::OnUpdateEditName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString str;
    GetDlgItemText( IDC_EDIT_NAME, str );
    GetDlgItem( IDOK )->EnableWindow( !str.IsEmpty() );
}


BOOL CNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CEdit *pEdit = (CEdit *)GetDlgItem( IDC_EDIT_NAME );
    // 读取玩家姓名
    CFiveApp *pApp = (CFiveApp *)AfxGetApp();
    ::GetPrivateProfileString( _T("Options"), _T("Name"), _T("Renjiu"), m_strName, 15, pApp->m_szIni );
    // 设置文本及其它杂项
    pEdit->LimitText( 15 );
    pEdit->SetWindowText( m_strName );
    pEdit->SetSel( 0, -1 );
    pEdit->SetFocus();
	return FALSE;   // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CNameDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	// 写入玩家姓名
    CFiveApp *pApp = (CFiveApp *)AfxGetApp();
    GetDlgItemText( IDC_EDIT_NAME, m_strName, 10 );
    ::WritePrivateProfileString( _T("Options"), _T("Name"), m_strName, pApp->m_szIni );
    // 设置玩家姓名
    CTable *pTable = (CTable *)GetParent()->GetDlgItem( IDC_TABLE );
    pTable->m_strMe = m_strName;
	CDialog::OnOK();
}
