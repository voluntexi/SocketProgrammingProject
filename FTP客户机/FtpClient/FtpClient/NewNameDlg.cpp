// NewNameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FtpClient.h"
#include "NewNameDlg.h"
#include "afxdialogex.h"


// CNewNameDlg �Ի���

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


// CNewNameDlg ��Ϣ�������


void CNewNameDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
	UpdateData(TRUE);
}
