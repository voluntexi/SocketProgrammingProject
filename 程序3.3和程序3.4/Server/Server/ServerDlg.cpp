// ServerDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "Message.h"  //�ֶ���Ӱ������

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

// CServerDlg �Ի���
CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nServerPort = 0;//������ӵĳ�Ա������ʼ������
	m_pServerSocket=NULL;//�ֶ����
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_nServerPort);
	DDV_MinMaxInt(pDX, m_nServerPort, 1024, 49151);
	DDX_Control(pDX, IDC_LIST_SROOM, m_listSroom);
	DDX_Control(pDX, IDC_STATIC_ONLINE, m_staOnline);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CServerDlg::OnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CServerDlg::OnClickedButtonStop)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_nServerPort=10000;
	UpdateData(FALSE);//�ó�Ա����ֵ���½���
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻�TRUE
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//����������������ť���¼�������
void CServerDlg::OnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//����û��������Ա����
	//�����������׽��ֶ���������ָ���˿�����
	m_pServerSocket=new CServerSocket(this);
	if (!m_pServerSocket->Create(m_nServerPort))
	{
		//������
		delete m_pServerSocket;
		m_pServerSocket=NULL;
		AfxMessageBox(LPCTSTR("���������������׽��ֳ��ִ���"));
		return;
	}
	//���������������׽��֣�������ʱ�������Կͻ���������
	if (!m_pServerSocket->Listen())
	{
		//������
		delete m_pServerSocket;
		m_pServerSocket=NULL;
		AfxMessageBox(LPCTSTR("���������������׽��ֳ��ִ���"));
		return;
	}
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
}

//����ֹͣ��������ť���¼�������
void CServerDlg::OnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMessage msg;
	msg.m_strMessage="��������ֹͣ��������!";
	delete m_pServerSocket;//�ͷŷ����������׽���
	m_pServerSocket=NULL;
	//����ͻ��������б�
	while(!m_ClientsList.IsEmpty())
	{
		//��ÿһ���ͻ�������"��������ֹͣ��������!"�����Ϣ�����б���ɾ�����ӣ��ͷ���Դ
		CClientSocket* pSocket=(CClientSocket*)m_ClientsList.RemoveHead();
		pSocket->SendMessage(&msg);
		delete pSocket;
	}
	//��������������Ҵ���
	while(m_listSroom.GetCount()!=0)
		m_listSroom.DeleteString(0);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
}

//�������������Կͻ��������������ڷ�������ά��һ�������б�
void CServerDlg::onAccept(void)
{
	//���������������ӿͻ������׽���
	CClientSocket* pSocket=new CClientSocket(this);
	if (m_pServerSocket->Accept(*pSocket))
	{
		//�����ͻ������ӣ�����ͻ��������б�
		pSocket->Init();
		m_ClientsList.AddTail(pSocket);
		//������������
		CString strTemp;
		strTemp.Format(_T("��ǰ����������%d"),m_ClientsList.GetCount());
		m_staOnline.SetWindowTextW(strTemp);
	}else
	{
		delete pSocket;
		pSocket=NULL;
	}
}

//�������������Կͻ�������Ϣ
void CServerDlg::onReceive(CClientSocket* pSocket)
{
	static CMessage msg;
	
	do {
		pSocket->ReceiveMessage(&msg);//������Ϣ
		m_listSroom.AddString(msg.m_strMessage);//����������б��
		sendToClients(&msg);//ת�������пͻ���
		//����ͻ����رգ��������б�ɾ������������֮�Ự�������׽���
		if (msg.m_bClosed)
		{
			//pSocket->Close();
			POSITION pos,temp;
			for(pos=m_ClientsList.GetHeadPosition();pos!=NULL;)
			{
				temp=pos;
				CClientSocket* pTempSocket=(CClientSocket*)m_ClientsList.GetNext(pos);
				if (pTempSocket==pSocket)
				{
					m_ClientsList.RemoveAt(temp);
					CString strTemp;
					//������������
					strTemp.Format(_T("��ǰ����������%d"),m_ClientsList.GetCount());
					m_staOnline.SetWindowTextW(strTemp);
					break;
				}//end if
			}//end for
			delete pSocket;
			pSocket=NULL;
			break;
		}//end if
	}while(!((pSocket->m_pArchiveIn)->IsBufferEmpty()));
}

//�����������пͻ���ת������ĳһ�ͻ�������Ϣ
void CServerDlg::sendToClients(CMessage* pMsg)
{
	for (POSITION pos=m_ClientsList.GetHeadPosition();pos!=NULL;)
	{
		CClientSocket* pSocket1=(CClientSocket*)m_ClientsList.GetNext(pos);
		pSocket1->SendMessage(pMsg);
	}
}
