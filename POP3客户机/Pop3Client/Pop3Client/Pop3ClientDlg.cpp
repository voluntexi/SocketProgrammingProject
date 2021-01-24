
// Pop3ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Pop3Client.h"
#include "Pop3ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPop3ClientDlg �Ի���




CPop3ClientDlg::CPop3ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPop3ClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strServerName = _T("");
	m_strMailBox = _T("");
	m_strPassword = _T("");
	//  m_mailInfo = _T("");
	m_mailInfo = _T("");
}

void CPop3ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_EDIT_MAILBOX, m_strMailBox);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Control(pDX, IDC_COMBO_TITLE, m_comboTitle);
	DDX_Control(pDX, IDC_RICHEDIT_MAILCONTENT, m_MailContent);
	DDX_Check(pDX, IDC_CHECK_DELMAIL, m_bDelMail);
	DDX_Text(pDX, IDC_RICHEDIT_MAILCONTENT, m_mailInfo);
}

BEGIN_MESSAGE_MAP(CPop3ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CPop3ClientDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CPop3ClientDlg::OnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_BROWSEMAIL, &CPop3ClientDlg::OnClickedButtonBrowsemail)
	ON_BN_CLICKED(IDC_BUTTON_SAVEMAIL, &CPop3ClientDlg::OnClickedButtonSavemail)
END_MESSAGE_MAP()


// CPop3ClientDlg ��Ϣ�������

BOOL CPop3ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_strServerName = _T("pop3.sohu.com");
	m_strMailBox = _T("yantaidxz@sohu.com");
	m_strPassword = _T("zzz2013");
	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPop3ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPop3ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPop3ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPop3ClientDlg::OnClickedButtonConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	
	m_pop3ClientSocket.SetParentDlg(this); 
	UpdateData(TRUE);  
	m_pop3ClientSocket.Create();   //�����׽��ֶ���ĵײ��׽���
	m_pop3ClientSocket.Connect((LPCSTR)m_strServerName,110); //����pop3������
	m_bDelMail=FALSE;
	m_mailInfo = "";                //���ı��б�����
	m_MailContent.Clear();
	UpdateData(FALSE);          //�����û�����
}


void CPop3ClientDlg::OnClickedButtonDisconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pop3ClientSocket.Close();
}


void CPop3ClientDlg::OnClickedButtonBrowsemail()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index;
	index = m_comboTitle.GetCurSel();  //����û�����Ͽ��е�ѡ��
	//��ò���ʾָ���ż��Ļ������Լ��ż�����
	m_mailInfo += m_pop3ClientSocket.GetMsgStuff(index);
	m_mailInfo += m_pop3ClientSocket.GetMsgBody(index);
//	CString s;
//	for(int i=0;i<m_pop3ClientSocket.retrMsg;i++)
//	{
//		s.Format("%c%c�� %d ���� %c%c",13,10,i,13,10);
//		m_mailInfo +=s;
//		m_mailInfo += m_pop3ClientSocket.msgs[i].text;
//	}
	UpdateData(FALSE);
}


void CPop3ClientDlg::OnClickedButtonSavemail()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index;
	CString s;
	index = m_comboTitle.GetCurSel();
	//���ָ���ż��Ļ������Լ��ż�����
	s = m_pop3ClientSocket.GetMsgStuff(index);
	s += m_pop3ClientSocket.GetMsgBody(index);
	
	CFileDialog dlg(FALSE);
	if(dlg.DoModal()==IDOK)
	{
		CFile file(dlg.GetPathName(),
			CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		file.Write((LPCSTR)s,s.GetLength());
		file.Close();
	}
}


void CPop3ClientDlg::DisplayInfo(LONG flag)
{
	CString s;
	switch(flag)
	{
	case S_CONNECT: //�����ӵ�����������ʾ��Ϣ
		s = "�����ӵ�"+m_strServerName+"...\r\n";
		m_mailInfo+=s;
		//�������Ӱ�ť
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
		//���öϿ���ť
		GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(TRUE); 
		//���ò鿴�ʼ���ť
		GetDlgItem(IDC_BUTTON_BROWSEMAIL)->EnableWindow(FALSE);
		break;
	case S_RECEIVE: //�յ���������������Ӧ����ʾ��������
		m_mailInfo+=m_pop3ClientSocket.lastMsg;
		break; 
	case S_CLOSE: //��ʾ�ر����ӵ���Ϣ
		m_mailInfo+=m_pop3ClientSocket.error;
		s = "�����Ѿ��ر�\r\n";
		m_mailInfo+=s;
		//�������Ӱ�ť
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
		//���öϿ���ť
		GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(FALSE);
		break;
	case S_GETNUM: //�Ѿ�֪�����������ż�������
		s.Format("�����й��� %d ����\r\n",m_pop3ClientSocket.numMsg);
		m_mailInfo+=s;
		break;
	case S_GETSIZE: //��ʾ�ż��Ĵ�С
		s.Format("�������ż���СΪ��%d�ֽ�\r\n",m_pop3ClientSocket.sizeMsg);
		m_mailInfo+=s;
		break;
	case S_ENDRETR: //�����ż���������ϣ���ʾ��Ϣ
		s.Format("�������� %d ���ż�\r\n",m_pop3ClientSocket.msgs.size());
		m_mailInfo+=s;
		//������ż����أ����ò鿴�ʼ���ť
		if((m_pop3ClientSocket.msgs.size())>0)
			GetDlgItem(IDC_BUTTON_BROWSEMAIL)->EnableWindow(TRUE);
		break;
	}
	UpdateData(FALSE);   //�����û�����
}
