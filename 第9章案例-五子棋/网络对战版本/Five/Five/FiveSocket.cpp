// FiveSocket.cpp : 实现文件
#include "stdafx.h"
#include "Five.h"
#include "FiveSocket.h"
#include "Table.h"  //手动添加
#include "FiveDlg.h"   //手动添加

// CFiveSocket
CFiveSocket::CFiveSocket() {  }
CFiveSocket::~CFiveSocket() { }

#if 0
BEGIN_MESSAGE_MAP(CFiveSocket, CAsyncSocket)
END_MESSAGE_MAP()
#endif	// 0

// CFiveSocket 成员函数
void CFiveSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CFiveDlg *pDlg = (CFiveDlg *)AfxGetMainWnd();
    // 使本窗口生效
    pDlg->EnableWindow();
    delete []pDlg->m_pDlg;
    pDlg->m_pDlg = NULL;
    pDlg->m_Table.Accept( 2 );
    pDlg->GetDlgItem( IDC_BTN_QHQ )->EnableWindow( TRUE );
    pDlg->GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
    pDlg->GetDlgItem( IDC_CMB_CHAT )->EnableWindow( TRUE );
    pDlg->GetDlgItem( IDC_BTN_LOST )->EnableWindow( TRUE );
    pDlg->m_Table.SetMenuState( FALSE );
}

void CFiveSocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
    CTable *pTable = (CTable *)AfxGetMainWnd()->GetDlgItem( IDC_TABLE );
    pTable->m_bConnected = TRUE;
    pTable->Connect( 2 );
}

void CFiveSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
    CTable *pTable = (CTable *)AfxGetMainWnd()->GetDlgItem( IDC_TABLE );
    pTable->Receive();
}

void CFiveSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
    CFiveDlg *pDlg = (CFiveDlg *)AfxGetMainWnd();
    pDlg->MessageBox( _T("对方已经离开游戏，改日再较量不迟。"), _T("五子棋"), MB_ICONINFORMATION);
    // 禁用所有项目，并使菜单生效
    pDlg->GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    pDlg->GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
    pDlg->GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    pDlg->GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
    pDlg->m_Table.SetMenuState( TRUE );
    pDlg->GetMenu()->EnableMenuItem( ID_MENU_PLAYAGAIN, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED );
    pDlg->m_Table.SetWait( TRUE );
    // 重新设置对方姓名
    pDlg->SetDlgItemText( IDC_ST_ENEMY, _T("无玩家加入") );
}
