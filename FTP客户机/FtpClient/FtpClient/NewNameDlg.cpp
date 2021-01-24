// NewNameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FtpClient.h"
#include "NewNameDlg.h"
#include "afxdialogex.h"


// CNewNameDlg 对话框

IMPLEMENT_DYNAMIC(CNewNameDlg, CDialog)

CNewNameDlg::CNewNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewNameDlg::IDD, pParent)
{

	m_NewFileName = _T("");
}

CNewNameDlg::~CNewNameDlg()
{
}

void CNewNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEWFILENAME, m_NewFileName);
}


BEGIN_MESSAGE_MAP(CNewNameDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CNewNameDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewNameDlg 消息处理程序


void CNewNameDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	UpdateData(TRUE);
}
