
// FtpClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FtpClient.h"
#include "FtpClientDlg.h"
#include "afxdialogex.h"
#include "NewNameDlg.h"

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

// CFtpClientDlg �Ի���

CFtpClientDlg::CFtpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFtpClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strServerName = _T("127.0.0.1");
	m_strUserName = _T("anonymous");
	m_strPassword = _T("");
	m_pFTPSession=NULL;
	m_pConnection = NULL;
	m_pFileFind = NULL;
}

void CFtpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Control(pDX, IDC_LIST_DIRECTORY, m_listDirectory);
}

BEGIN_MESSAGE_MAP(CFtpClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CFtpClientDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CFtpClientDlg::OnBnClickedButtonUpload)
	ON_BN_CLICKED(IDC_BUTTON_RENAME, &CFtpClientDlg::OnBnClickedButtonRename)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &CFtpClientDlg::OnBnClickedButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CFtpClientDlg::OnBnClickedButtonDownload)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CFtpClientDlg::OnBnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_SUBDIR, &CFtpClientDlg::OnBnClickedButtonSubdir)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CFtpClientDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_PARENTDIR, &CFtpClientDlg::OnBnClickedButtonParentdir)
END_MESSAGE_MAP()


// CFtpClientDlg ��Ϣ�������

BOOL CFtpClientDlg::OnInitDialog()
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
	m_listDirectory.InsertColumn(0,_T("�ļ���"),LVCFMT_CENTER,200);
	m_listDirectory.InsertColumn(1,_T("�޸�����"),LVCFMT_CENTER,100);
	m_listDirectory.InsertColumn(2,_T("��С"),LVCFMT_CENTER,200);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFtpClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFtpClientDlg::OnPaint()
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
HCURSOR CFtpClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFtpClientDlg::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (Connect(m_strServerName,m_strUserName,m_strPassword))
	{
		DisplayContent(_T("*"));
		GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(FALSE);
	}else //����ʧ��
	{
		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"),MB_OK|MB_ICONSTOP);
	}

}



void CFtpClientDlg::OnBnClickedButtonUpload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Upload();
}



void CFtpClientDlg::OnBnClickedButtonRename()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Rename();
}


void CFtpClientDlg::OnBnClickedButtonQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	DisplayContent(_T("*"));
}


void CFtpClientDlg::OnBnClickedButtonDownload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Download();
}
//�˳�
void CFtpClientDlg::OnBnClickedButtonLogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	delete m_pFTPSession;
	delete m_pConnection;
	delete m_pFileFind;
	m_pFTPSession=NULL;
	m_pConnection = NULL;
	m_pFileFind = NULL;
	DestroyWindow();
}

//��ʾ��������ǰĿ�µ������ļ�����Ŀ¼
void CFtpClientDlg::DisplayContent(LPCTSTR lpctstr,CString currentDir)
{
	UpdateData(TRUE);
	Connect(m_strServerName,m_strUserName,m_strPassword);
	m_pConnection->SetCurrentDirectory(currentDir);
	m_listDirectory.DeleteAllItems();
	m_pFileFind=new CFtpFileFind(m_pConnection);
	BOOL bFound;
	bFound=m_pFileFind->FindFile(lpctstr);
	if (!bFound)
	{
		m_pFileFind->Close();
		m_pFileFind=NULL;
		AfxMessageBox(_T("û���ҵ��ļ�!"),MB_OK | MB_ICONSTOP);
		return;
	}
	
	CString strFileName;
	CString strFileTime;
	CString strFileLength;
	
	while(bFound)
	{		
		bFound= m_pFileFind->FindNextFile();
		
		strFileName=m_pFileFind->GetFileName(); 
		FILETIME ft;
		m_pFileFind->GetLastWriteTime(&ft);   
		CTime FileTime(ft);
		strFileTime = FileTime.Format("%y-%m-%d");    
		if (m_pFileFind->IsDirectory())
		{
			//�����Ŀ¼��<��Ŀ¼>����
			strFileLength = "<��Ŀ¼>";
		}	
		else
		{
			//�õ��ļ���С
			ULONGLONG fileSize=m_pFileFind->GetLength();
			
			if (fileSize<1024)
			{
				strFileLength.Format(_T("%d Bytes"),fileSize);
			}
			else if (fileSize<(1024*1024))
			{
					strFileLength.Format(_T("%3.3f KB"),fileSize/1024.0); 
			}else if (fileSize<(1024*1024*1024)) 
			{
				strFileLength.Format(_T("%3.3f MB"),fileSize/(1024*1024.0));
			}else
			{
				strFileLength.Format(_T("%1.3f GB"),    
						fileSize/(1024.0*1024*1024));   
			}//end if fileSize
		}//end if
		int column=0;
        m_listDirectory.InsertItem(column,strFileName,0);
		m_listDirectory.SetItemText(column,1,strFileTime);
		m_listDirectory.SetItemText(column,2,strFileLength);
		column++;
	}//end while
	UpdateData(FALSE);
}



//����
void CFtpClientDlg::Download(void)
{
	int index=m_listDirectory.GetNextItem(-1,LVNI_SELECTED); 
	if (index==-1)
	{
        AfxMessageBox(_T("������ѡ��Ҫ���ص��ļ�!"),MB_OK | MB_ICONQUESTION);
	}
	else
	{
        CString strType=m_listDirectory.GetItemText(index,2);   //�õ�ѡ���������
		if (strType!="<��Ŀ¼>")   //ѡ������ļ�
		{
			CString strDestName;
			CString strSourceName;
			strSourceName = m_listDirectory.GetItemText(index,0);//�õ���Ҫ���ص��ļ���
			
			CFileDialog dlg(FALSE,_T(""),strSourceName);		
			if (dlg.DoModal()==IDOK)
			{
				//��������ļ��ڱ��ػ��ϴ洢��·��������
				strDestName=dlg.GetPathName();		
				//����CFtpConnect���е�GetFile���������ļ�
				if (m_pConnection->GetFile(strSourceName,strDestName))
					AfxMessageBox(_T("���سɹ���"),MB_OK|MB_ICONINFORMATION);
				else
					AfxMessageBox(_T("����ʧ�ܣ�"),MB_OK|MB_ICONSTOP);
			}
		}
		else
		{
			//ѡ�����Ŀ¼
			AfxMessageBox(_T("��������Ŀ¼!\n����ѡ!"),MB_OK|MB_ICONSTOP);
		}
	}
}

//�ϴ�
void CFtpClientDlg::Upload(void)
{
	CString strSourceName;
	CString strDestName;
	CFileDialog dlg(TRUE,_T(""),_T("*.*"));
	if (dlg.DoModal()==IDOK)
	{
		//��ô��ϴ��ı����ļ�·�����ļ���
		strSourceName = dlg.GetPathName();
		strDestName = dlg.GetFileName();
		
		//����CFtpConnect���е�PutFile�����ϴ��ļ�
		if (m_pConnection->PutFile(strSourceName,strDestName))
			AfxMessageBox(_T("�ϴ��ɹ�"),MB_OK|MB_ICONINFORMATION);
		else
			AfxMessageBox(_T("�ϴ�ʧ��"),MB_OK|MB_ICONSTOP);
	}
    DisplayContent(_T("*"));
}


//�ļ�����
void CFtpClientDlg::Rename(void)
{
	CString strNewName;
	CString strOldName;
	
	int index=m_listDirectory.GetNextItem(-1,LVNI_SELECTED); //�õ�CListCtrl��ѡ�е���
	if (index==-1)
	{
        AfxMessageBox(_T("û��ѡ���ļ�!"),MB_OK | MB_ICONQUESTION);
	}
	else
	{
       	strOldName = m_listDirectory.GetItemText(index,0);//�õ���ѡ����ļ���
		CNewNameDlg dlg;		
		if (dlg.DoModal()==IDOK)
		{
			strNewName=dlg.m_NewFileName;
			if (m_pConnection->Rename(strOldName,strNewName))
				AfxMessageBox(_T("�������ɹ���"),MB_OK|MB_ICONINFORMATION);
			else
				AfxMessageBox(_T("�޷���������"),MB_OK|MB_ICONSTOP);
		}
	}	
	DisplayContent(_T("*"));//��ʾĿ¼
}


void CFtpClientDlg::OnBnClickedButtonSubdir()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DisplaySubDir();
}


void CFtpClientDlg::OnBnClickedButtonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DeleteFile();
}


void CFtpClientDlg::OnBnClickedButtonParentdir()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DisplayParentDir();
}

//ɾ���ļ�
void CFtpClientDlg::DeleteFile(void)
{
	int index=m_listDirectory.GetNextItem(-1,LVNI_SELECTED); 
	if (index==-1)
	{
        AfxMessageBox(_T("û��ѡ���ļ�!"),MB_OK | MB_ICONQUESTION);
	}
	else
	{
		CString  strFileName;
		strFileName = m_listDirectory.GetItemText(index,0);
		if (_T("<��Ŀ¼>")==m_listDirectory.GetItemText(index,2))
		{
			AfxMessageBox(_T("����ɾ��Ŀ¼!"),MB_OK | MB_ICONSTOP);
		}
		else
		{
			if (m_pConnection->Remove(strFileName))
				AfxMessageBox(_T("ɾ���ɹ���"),MB_OK|MB_ICONINFORMATION);
			else
				AfxMessageBox(_T("�޷�ɾ����"),MB_OK|MB_ICONSTOP);
		}
	}
	DisplayContent(_T("*"));
}

//��ʾ�¼���Ŀ¼
void CFtpClientDlg::DisplaySubDir(void)
{
	static CString  strCurrentDirectory,strSub;
	
    m_pConnection->GetCurrentDirectory(strCurrentDirectory);
	strCurrentDirectory.Format(_T("%s/"),(strCurrentDirectory));
	
	//�õ���ѡ����ı�
	int index=m_listDirectory.GetNextItem(-1,LVNI_SELECTED); 
	strSub = m_listDirectory.GetItemText(index,0);

	if (index==-1)
	{
        AfxMessageBox(_T("û��ѡ��Ŀ¼!"),MB_OK | MB_ICONQUESTION);
	}
	else
	{   //�ж��ǲ���Ŀ¼
		if (_T("<��Ŀ¼>")!=m_listDirectory.GetItemText(index,2))
		{
			AfxMessageBox(_T("������Ŀ¼!"),MB_OK | MB_ICONSTOP);
		}
		else
		{
            //���õ�ǰĿ¼
			strCurrentDirectory.Format(_T("%s%s"),strCurrentDirectory,strSub);
			m_pConnection->SetCurrentDirectory(strCurrentDirectory);
			//�Ե�ǰĿ¼���в�ѯ
			DisplayContent(_T("*"),strCurrentDirectory);
		}
	}	
}

//������һ��Ŀ¼���ַ�����ʾ
CString CFtpClientDlg::GetParentDirectory(CString str)
{
	int LastIndex=0;
	for (int i=0; i<str.GetLength(); i++)
	{
		if (str.GetAt(i)=='/')
			LastIndex = i;
	}
	str = str.Left(LastIndex);
	if (LastIndex == 0)
		str="/";
	return str;
}

//��ʾ����Ŀ¼
void CFtpClientDlg::DisplayParentDir(void)
{
	static CString  strCurrentDirectory;
    m_pConnection->GetCurrentDirectory(strCurrentDirectory);
	if (strCurrentDirectory ==_T("/"))
	{
		AfxMessageBox(_T("�Ѿ��Ǹ�Ŀ¼��!"),MB_OK | MB_ICONSTOP);
	}
	else
	{
        strCurrentDirectory=GetParentDirectory(strCurrentDirectory);
        //���õ�ǰĿ¼
       	m_pConnection->SetCurrentDirectory(strCurrentDirectory);
		//�Ե�ǰĿ¼���в�ѯ
        DisplayContent(_T("*"),strCurrentDirectory);
	}
}


BOOL CFtpClientDlg::Connect(CString serverName, CString userName, CString password)
{
	m_pFTPSession=new CInternetSession(AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS);		
	try
	{
		//��ͼ����FTP����
		m_pConnection=m_pFTPSession->GetFtpConnection(serverName,userName,password);      
	}
	catch (CInternetException* e)
	{
		//������
		e->Delete();
		m_pFTPSession=NULL;
		m_pConnection=NULL;
		return FALSE;
	}
	return TRUE;
}
