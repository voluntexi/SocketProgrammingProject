// ClientDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"//�ֶ���Ӱ������
#include "Message.h"

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// �Ի�������
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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

// CClientDlg �Ի���
CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//�����Զ���ӵĳ�ʼ������
	m_strServerName = _T("");
	m_nServerPort = 0;
	m_strSpeaking = _T("");
	m_strUserName = _T("");
	//�ֶ���ӵĳ�ʼ������
	m_pSocket=NULL;
	m_pFile=NULL;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_nServerPort);
	DDV_MinMaxInt(pDX, m_nServerPort, 1024, 49151);
	DDX_Text(pDX, IDC_EDIT_SPEAKING, m_strSpeaking);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Control(pDX, IDC_LIST_CROOM, m_listCRoom);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CClientDlg::OnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CClientDlg::OnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_SPEAK, &CClientDlg::OnClickedButtonSpeak)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CClientDlg ��Ϣ�������
BOOL CClientDlg::OnInitDialog()
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
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//�ֶ�������³�ʼ�����룺
	m_strUserName=_T("�ǻ���");
	m_strServerName=_T("localhost");
	m_nServerPort=10000;
	UpdateData(FALSE);//���¶�Ӧ�ؼ�����
	GetDlgItem(IDC_EDIT_SPEAKING)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOGOUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SPEAK)->EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CClientDlg::OnPaint()
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//�������к����Ŀ�����������ɣ���ʵ�ִ�����Ҫ�ֶ����
void CClientDlg::OnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pSocket=new CClientSocket(this);//�����׽���
	if (!m_pSocket->Create())
	{
		//������
		delete m_pSocket;
		m_pSocket=NULL;
		AfxMessageBox(_T("�������ӷ��������׽��ִ���,��¼ʧ�ܣ�"));
		return;
	}
	if (!m_pSocket->Connect(m_strServerName,m_nServerPort))
	{
		//������
		delete m_pSocket;
		m_pSocket=NULL;
		AfxMessageBox(_T("���ӷ���������,��¼ʧ�ܣ�"));
		return;
	}
	m_pFile=new CSocketFile(m_pSocket);
	m_pArchiveIn=new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut=new CArchive(m_pFile,CArchive::store);
	//�������������Ϣ�������¿ͻ�����������
	UpdateData(TRUE);//���¿ؼ���Ա����
	CString strTemp;
	strTemp=m_strUserName+_T("������ͦ�ؽ���������!!!");
	SendMyMessage(strTemp,FALSE);

	GetDlgItem(IDC_EDIT_SPEAKING)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOGOUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SPEAK)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(FALSE);
	
}
//�����˳���ť����Ӧ����
void CClientDlg::OnClickedButtonLogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTemp;
	strTemp=m_strUserName+_T("���������뿪������......");
	SendMyMessage(strTemp,TRUE);
	//ɾ�������ͷſռ�
	delete m_pArchiveIn;
	delete m_pArchiveOut;
	delete m_pFile;
	delete m_pSocket;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
	m_pFile=NULL;
	m_pSocket=NULL;

	//�������������
	while (m_listCRoom.GetCount()!=0) 
		m_listCRoom.DeleteString(0);
	GetDlgItem(IDC_EDIT_SPEAKING)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOGOUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SPEAK)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(TRUE);
}

//�������԰�ť����Ӧ����
void CClientDlg::OnClickedButtonSpeak()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//���¿ؼ���Ա������ȡ���û����������
	if (!m_strSpeaking.IsEmpty()) //��������򲻿�
	{
		SendMyMessage(m_strUserName+"����˵��"+m_strSpeaking,FALSE);
		m_strSpeaking=_T("");
		UpdateData(FALSE);//�����û����棬���Կ����
	}
}
//�رտͻ���ʱ���ƺ�����
void CClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
	if ((m_pSocket!=NULL) && (m_pFile!=NULL) && (m_pArchiveOut!=NULL))
	{
		CMessage msg;
		CString strTemp;
		strTemp=_T("�����֮��")+m_strUserName+_T("���ڿͻ����ѹر�");
		msg.m_strMessage=strTemp;
		msg.m_bClosed=TRUE;
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();

		//ɾ�������ͷſռ�
		delete m_pArchiveIn;
		delete m_pArchiveOut;
		delete m_pFile;
		m_pArchiveIn=NULL;
		m_pArchiveOut=NULL;
		m_pFile=NULL;

		if (m_pSocket!=NULL)
		{
			BYTE buffer[100];
			m_pSocket->ShutDown();
			while (m_pSocket->Receive(buffer,100)>0);
		}
		delete m_pSocket;
		m_pSocket=NULL;
	}
}

//���׽����յ�FD_READ��Ϣʱ������OnReceive�������ô˺���
void CClientDlg::onReceive(void)
{
	do {
		ReceiveMessage();//������Ϣ
		if (m_pSocket==NULL) return;
	}while(!m_pArchiveIn->IsBufferEmpty());

}

//������Ϣ������
void CClientDlg::ReceiveMessage(void)
{
	CMessage msg;
	TRY {
		msg.Serialize(*m_pArchiveIn);//����
		m_listCRoom.AddString(msg.m_strMessage);//��ʾ�ڴ���
	}CATCH(CFileException, e) { 
		//������
		CString strTemp;
		strTemp=_T("������������ѶϿ������ӹرգ�");
		m_listCRoom.AddString(strTemp);
		msg.m_bClosed=TRUE;
		m_pArchiveOut->Abort();
		//ɾ�������ͷſռ�
		delete m_pArchiveIn;
		delete m_pArchiveOut;
		delete m_pFile;
		delete m_pSocket;
		m_pArchiveIn=NULL;
		m_pArchiveOut=NULL;
		m_pFile=NULL;
		m_pSocket=NULL;
	}
	END_CATCH 

}

//������Ϣ�Ĵ�����
void CClientDlg::SendMyMessage(CString& strMessage,BOOL bClosed)
{
	if (m_pArchiveOut!=NULL) {
		CMessage msg;
		msg.m_strMessage=strMessage;
		msg.m_bClosed=bClosed;
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}
