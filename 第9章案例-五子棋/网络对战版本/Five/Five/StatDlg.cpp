// StatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Five.h"
#include "StatDlg.h"
#include "afxdialogex.h"
#include "Table.h" //手动添加

// CStatDlg 对话框

IMPLEMENT_DYNAMIC(CStatDlg, CDialog)

CStatDlg::CStatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatDlg::IDD, pParent)
{

}

CStatDlg::~CStatDlg()
{
}

void CStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStatDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_RESET, &CStatDlg::OnClickedBtnReset)
END_MESSAGE_MAP()


// CStatDlg 消息处理程序


void CStatDlg::OnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	CFiveApp *pApp = (CFiveApp *)AfxGetApp();
    pApp->m_nWin = 0;
    pApp->m_nDraw = 0;
    pApp->m_nLost = 0;
    ShowStat();
}


void CStatDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	CFiveApp *pApp = (CFiveApp *)AfxGetApp();
    // 写入战绩统计
    TCHAR str[10];
    wsprintf( str, _T("%d"), pApp->m_nWin );
    ::WritePrivateProfileString( _T("Stats"), _T("Win"), str, pApp->m_szIni );
    wsprintf( str, _T("%d"), pApp->m_nDraw );
    ::WritePrivateProfileString( _T("Stats"), _T("Draw"), str, pApp->m_szIni );
    wsprintf( str, _T("%d"), pApp->m_nLost );
    ::WritePrivateProfileString( _T("Stats"), _T("Lost"), str, pApp->m_szIni );
	CDialog::OnOK();
}


BOOL CStatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	   // 读取姓名
    CTable *pTable = (CTable *)GetParent()->GetDlgItem( IDC_TABLE );
    SetDlgItemText( IDC_ST_NAME, pTable->m_strMe );
    ShowStat();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CStatDlg::ShowStat(void)
{
	    CFiveApp *pApp = (CFiveApp *)AfxGetApp();
    CString str;
    str.Format( _T("%d"), pApp->m_nWin );
    SetDlgItemText( IDC_ST_WIN, str );
    str.Format( _T("%d"), pApp->m_nDraw );
    SetDlgItemText( IDC_ST_DRAW, str );
    str.Format( _T("%d"), pApp->m_nLost );
    SetDlgItemText( IDC_ST_LOST, str );
    // 计算胜率
    if ( 0 == pApp->m_nWin )
    {
        str = _T("胜率：0%");
    }
    else
    {
        str.Format( _T("胜率：%d%%"), pApp->m_nWin * 100 / ( pApp->m_nWin + pApp->m_nDraw + pApp->m_nLost ) );
    }
    SetDlgItemText( IDC_ST_PERCENT, str );
}
