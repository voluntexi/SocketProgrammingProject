// SmtpClientDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "SmtpClient.h"
#include "SmtpClientDlg.h"
#include "afxdialogex.h"

#define SMTP_MAXLINE  76

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


// CSmtpClientDlg �Ի���




CSmtpClientDlg::CSmtpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmtpClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strAttach = _T("");
	m_strBcc = _T("");
	m_strBody = _T("");
	m_strCopyTo = _T("");
	m_strPassword = _T("");
	m_strReceiver = _T("");
	m_strSender = _T("");
	m_nServerPort = 0;
	m_strSmtpServer = _T("");
	m_strTitle = _T("");
	m_strUserName = _T("");
}

void CSmtpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ATTACH, m_strAttach);
	DDX_Text(pDX, IDC_EDIT_BCC, m_strBcc);
	DDX_Text(pDX, IDC_EDIT_BODY, m_strBody);
	DDX_Text(pDX, IDC_EDIT_COPYTO, m_strCopyTo);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_RECEIVER, m_strReceiver);
	DDX_Text(pDX, IDC_EDIT_SENDER, m_strSender);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_nServerPort);
	DDX_Text(pDX, IDC_EDIT_SMTPSERVER, m_strSmtpServer);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
}

BEGIN_MESSAGE_MAP(CSmtpClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ATTACH, &CSmtpClientDlg::OnClickedButtonAttach)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSmtpClientDlg::OnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CSmtpClientDlg::OnClickedButtonCancel)
END_MESSAGE_MAP()


// CSmtpClientDlg ��Ϣ�������

BOOL CSmtpClientDlg::OnInitDialog()
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
	m_strAttach = _T("");
	m_strBcc = _T("");
	m_strBody = _T("");
	m_strCopyTo = _T("");
	m_strPassword = _T("");
	m_strReceiver = _T("");
	m_strSender = _T("upsunny2008@163.com");
	m_nServerPort = 25;
	m_strSmtpServer = _T("smtp.163.com");
	m_strTitle = _T("");
	m_strUserName = _T("");
	UpdateData(FALSE);                 //�����û�����
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSmtpClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSmtpClientDlg::OnPaint()
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
HCURSOR CSmtpClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSmtpClientDlg::OnClickedButtonAttach()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("All Files (*.*)|*.*||"));
	if (dlg.DoModal() == IDOK) 
	{
		CString sNewFile = dlg.GetPathName();
		if (m_strAttach.GetLength())
		{
			m_strAttach += _T(", ");
			m_strAttach += sNewFile;
		}
		else
			m_strAttach = sNewFile;
		UpdateData(FALSE);
	}
	LPSTR pszBody = NULL;
	int nBodySize = 0;
	if (!GetBody(pszBody, nBodySize))
	{
		TRACE(_T("Failed in call to send body parts body, GetLastError returns: %d\n"), GetLastError());
	}
	CString s;
	s = pszBody;
//	m_Info += s;
	UpdateData(FALSE);
}


void CSmtpClientDlg::OnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�趨smtp��ı�����ʹָ֮�򱾶Ի����Ա㴫����Ϣ
	smtpSocket.setParentDlg(this); 
	UpdateData(TRUE);    //ȡ���û��ڶԻ��������������
	smtpSocket.Create(); //�����׽��ֶ���ĵײ��׽���
	smtpSocket.Connect((LPCTSTR)m_strSmtpServer,m_nServerPort); //����pop3������
	UpdateData(FALSE);          //�����û�����

}


void CSmtpClientDlg::OnClickedButtonCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
//���ݲ�ͬ����������û���ʾ��ͬ����Ϣ
void CSmtpClientDlg::Disp(LONG flag)
{
	CString s;
	switch(flag)
	{
	case S_CONNECT: //�����ӵ�����������ʾ��Ϣ
		s =_T("�Ѿ����ӵ�")+m_strSmtpServer+_T("������\r\n");
		//m_Info += s;
		//m_listInfo.AddString(s);
		break;
	case S_RECEIVE: //�յ�����������������,��ʾ������
		//m_Info += smtpSocket.lastMsg;
		//m_listInfo.AddString(smtpSocket.lastMsg);
		break; 
	case S_CLOSE: //��ʾ�ر����ӵ���Ϣ
		//m_Info += smtpSocket.error;
//		m_listInfo.AddString(smtpSocket.error);
		s = "�����Ѿ��ر�\r\n";
		//m_Info += s;
		//m_listInfo.AddString(s); 
		break;
	}
	UpdateData(FALSE);   //�����û�����
}

void CSmtpClientDlg::GetHeader()
{
	UpdateData(TRUE);
	CString sepa;
	CString sReply;
	sReply = _T("");

	//���� "Date:" ����������
	CTime now(CTime::GetCurrentTime());
	CString sDate(now.Format(_T("%a, %d %b %Y %H:%M:%S ")));
	sDate +="+0800 (CST)";

	CString sBuf(sReply);
	if (m_strAttach.GetLength())
	{
		sReply.Format(_T("MIME-Version: 1.0\r\n"));
		sBuf += sReply;
	}

	//��� From �� to �ֶ�
	//From: "=?GB2312?B?XXXXXXXXXX=?=" // �����ˣ������˱���
	//To: Li@163.com 

	coder.Encode(m_strSender);
	sReply.Format(_T("From: %s\r\n"), m_strSender);
//	sReply.Format(_T("From: =?gb2312?B?%s?=\r\n"), coder.EncodedMessage());
	sBuf += sReply;
	
	sReply.Format(_T("To: %s\r\n"),m_strReceiver);
	sBuf += sReply;

	//��� Date�ֶ�
	//Date: Wed, 8 Apr 2004 16:16:16 +0800 // ���ŵ�����ʱ��
	sReply.Format(_T("Date: %s\r\n"),sDate);
	sBuf += sReply;

	//��� subject�ֶ�
	//Subject: =?GB2312?B?XXXXXX=?= // ���⣬�����˱���
	coder.Encode(m_strTitle);
	sReply.Format(_T("Subject: %s\r\n"),m_strTitle);
//	sReply.Format(_T("Subject: =?gb2312?B?%s?=\r\n"),coder.EncodedMessage());
	sBuf += sReply;

	//����У���� Cc �ֶ�
	if (m_strCopyTo.GetLength())
	{
		sReply.Format(_T("Cc: %s\r\n"), m_strCopyTo);
		sBuf += sReply;
	}

	//����У����Bcc �ֶ�
	if (m_strBcc.GetLength())
	{
		sReply.Format(_T("Bcc: %s\r\n"), m_strBcc);
		sBuf += sReply;
	}

	//�����Ҫ����� Mime �ֶ�
	//MIME-Version: 1.0               // MIME�汾
	//Content-type: multipart/mixed;  // ���������Ƕಿ��/�����
	//boundary = "NextPart_000_00A"  // ָ��һ���߽������ַ���
	
	sepa= _T("Boundary-=_HfNFaIwtPvzJDUQrvChaEKIMklNx");
	if (m_strAttach.GetLength())
	{
//		sReply.Format(_T("MIME-Version: 1.0\r\n"));
//		sBuf += sReply;
		sReply.Format(_T("Content-Type:Multipart/mixed;boundary=%s\r\n"),sepa);
		sBuf += sReply;
		sBuf += _T("\r\n");
	} else {
		sBuf += _T("\r\n");
		sReply.Format(_T(" %s\r\n"), m_strBody);
		sBuf += sReply;
		sReply.Format(_T("%c%c.%c%c"),13,10,13,10);
		sBuf += sReply;
	}
	smtpSocket.Send((LPCTSTR)sBuf,sBuf.GetLength());
	//m_Info+=sBuf;

	if (m_strAttach.GetLength())
	{
		sReply.Format(_T("--%s\r\n"),sepa);
		sBuf = sReply;	
		
		sBuf += _T("Content-Type: text/plain; charset='gb2312'\r\n");
		sBuf += _T("Content-Transfer-Encoding: base64\r\n");
		sBuf += _T("\r\n");
		
		coder.Encode(m_strBody);
		sReply.Format(_T("%s\r\n"),coder.EncodedMessage());
		sBuf += sReply;
		
		sReply.Format(_T("--%s\r\n"), sepa);
		sBuf += sReply;

		sBuf += _T("Content-Type: text/plain; charset='gb2312'\r\n");
		sBuf += _T("Content-Transfer-Encoding: base64\r\n");
		sBuf += _T("\r\n");
		
		//add Letter	
		LPSTR pszBody = NULL;
		int nBodySize = 0;
		if (!GetBody(pszBody, nBodySize))
		{
			TRACE(_T("Failed in call to send body parts body, GetLastError returns: %d\n"), GetLastError());
		}
		sReply = pszBody;
		sBuf += sReply;
		sReply.Format(_T("--%s\r\n"), sepa);
		sBuf += sReply;
		
		sReply.Format(_T("%c%c.%c%c"),13,10,13,10);
		sBuf += sReply;
		smtpSocket.Send((LPCTSTR)sBuf,sBuf.GetLength());
		//m_Info+=sBuf;
	}
	UpdateData(FALSE);
}

BOOL CSmtpClientDlg::GetBody(LPSTR& pszBody, int& nBodySize)
{
	BOOL bSuccess = FALSE;

	//�򿪸����ļ�
	CFile infile;
	if (infile.Open(m_strAttach, CFile::modeRead | CFile::shareDenyWrite))
	{
		int fileSize = (int)infile.GetLength();
		if (fileSize)
		{
			//��������
			BYTE* pszIn = new BYTE[fileSize];
			try
			{
				infile.Read(pszIn, fileSize);
				bSuccess = TRUE;
			}
			catch(CFileException* pEx)
			{
				bSuccess = FALSE;
				pEx->Delete();
			}

			if (bSuccess)
			{
				coder.Encode(pszIn, fileSize); //����
				delete [] pszIn;               //ɾ�������뻺����
				infile.Close();                //�ر������ļ�

				//�γɱ����ķ�������
				LPSTR pszEncoded = coder.EncodedMessage();
				int nEncodedSize = coder.EncodedMessageSize();
				nBodySize = nEncodedSize + (((nEncodedSize/76)+1)*2) + 1;
				pszBody = new char[nBodySize];
				--nBodySize; 

				int nInPos = 0;
				int nOutPos = 0;
				while (nInPos < nEncodedSize)
				{
					int nThisLineSize = min(nEncodedSize - nInPos, SMTP_MAXLINE);
					CopyMemory(&pszBody[nOutPos], &pszEncoded[nInPos], nThisLineSize);
					nOutPos += nThisLineSize;
					CopyMemory(&pszBody[nOutPos], "\r\n", 2);
					nOutPos += 2;
					nInPos += nThisLineSize;
				}
				pszBody[nOutPos] = '\0'; //�Կ��ַ�������
			}
		}  else  {
			bSuccess = TRUE;
			pszBody = NULL;
			nBodySize = 0;
		}
	}  else
		TRACE(_T("No bodypart body text or filename specified!\n"));

	return bSuccess;
}