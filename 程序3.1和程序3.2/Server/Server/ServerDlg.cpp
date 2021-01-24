// ServerDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

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
{}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CServerDlg �Ի���

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strServerName = _T("");
	m_nServerPort = 0;
	m_strToClient = _T("");
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_nServerPort);
	DDV_MinMaxInt(pDX, m_nServerPort, 1024, 49151);
	DDX_Text(pDX, IDC_EDIT_TOCLIENT, m_strToClient);
	DDX_Control(pDX, IDC_LIST_RECEIVED, m_listReceived);
	DDX_Control(pDX, IDC_LIST_SENT, m_listSent);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLOSELISTEN, &CServerDlg::OnClickedButtonCloselisten)
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CServerDlg::OnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CServerDlg::OnClickedButtonSend)
END_MESSAGE_MAP()


// CServerDlg ��Ϣ�������
BOOL CServerDlg::OnInitDialog()
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
	m_strServerName="localhost";
	m_nServerPort=1024;
	UpdateData(FALSE);
	m_sServerSocket.setParentDlg(this);
	m_sClientSocket.setParentDlg(this);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServerDlg::OnClickedButtonCloselisten()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//onClose();
	m_sClientSocket.Close();
	m_sServerSocket.Close();
	m_listReceived.AddString(CString("�������Ͽ�������"));

}

void CServerDlg::OnClickedButtonListen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	m_sServerSocket.Create(m_nServerPort);
	m_sServerSocket.Listen();

	GetDlgItem(IDC_EDIT_TOCLIENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSELISTEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	
}

void CServerDlg::OnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nMsgLen;
	int nSentLen;
	int flag=0;
	UpdateData(TRUE);
	
	if(!m_strToClient.IsEmpty())
	{
		for (POSITION pos=m_ClientsList.GetHeadPosition();pos!=NULL;)
	{
		CServerSocket* pSocket=(CServerSocket*)m_ClientsList.GetNext(pos);


		nMsgLen=m_strToClient.GetLength()*sizeof(m_strToClient);
		nSentLen=pSocket->Send(m_strToClient,nMsgLen);
		if (nSentLen!=SOCKET_ERROR) { //���ͳɹ�
			if ( flag==0)
			{
			m_listSent.AddString(m_strToClient);
			flag=1;
			} 
			
		} else {
			AfxMessageBox(LPCTSTR("��������ͻ���������Ϣ���ִ���"),MB_OK|MB_ICONSTOP);
		}
		}//end for
		UpdateData(FALSE);
		m_strToClient.Empty();
		UpdateData(FALSE);
	}//end if
}
//���׽��ֵ�OnClose�¼�������ת���˴�ִ��
void CServerDlg::onClose(void)
{
	m_listReceived.AddString(CString("�������յ���OnClose��Ϣ"));
	m_sClientSocket.Close();
	m_sServerSocket.Close();
	GetDlgItem(IDC_EDIT_TOCLIENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSELISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
}
//���׽��ֵ�OnAccept�¼�������ת���˴�ִ��
void CServerDlg::onAccept(void)
{
	m_listReceived.AddString(CString("�������յ���OnAccept��Ϣ"));
	CServerSocket * pClientSocket=new CServerSocket();
	m_sServerSocket.Accept(*pClientSocket);
	pClientSocket->setParentDlg(this);
	m_ClientsList.AddTail(pClientSocket);

	GetDlgItem(IDC_EDIT_TOCLIENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSELISTEN)->EnableWindow(TRUE);
}
//���׽��ֵ�OnReceive�¼�������ת���˴�ִ��
void CServerDlg::onReceive(CServerSocket* pSocket )
{
	TCHAR buff[4096];
	int nBufferSize=4096;
	int nReceivedLen;
	CString strReceived;
	m_listReceived.AddString(CString("�������յ���OnReceive��Ϣ"));
	//m_ClientsList
	/*for (POSITION pos=m_ClientsList.GetHeadPosition();pos!=NULL;)
	{
		CServerSocket* pSocket=(CServerSocket*)m_ClientsList.GetNext(pos);*/
		//pSocket->SendMessage(pMsg);
		nReceivedLen=pSocket->Receive(buff,nBufferSize);
	if(nReceivedLen!=SOCKET_ERROR)
	{
		buff[nReceivedLen]=_T('\0');
		CString szTemp(buff);
		strReceived=szTemp;
		m_listReceived.AddString(strReceived);
		UpdateData(FALSE);
	}else {
		AfxMessageBox(LPCTSTR("�������ӿͻ���������Ϣ���ִ���"),MB_OK|MB_ICONSTOP);
	}
	
//}
}