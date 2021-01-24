
// FtpClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FtpClient.h"
#include "FtpClientDlg.h"
#include "afxdialogex.h"
#include "NewNameDlg.h"

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// CFtpClientDlg 对话框

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


// CFtpClientDlg 消息处理程序

BOOL CFtpClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_listDirectory.InsertColumn(0,_T("文件名"),LVCFMT_CENTER,200);
	m_listDirectory.InsertColumn(1,_T("修改日期"),LVCFMT_CENTER,100);
	m_listDirectory.InsertColumn(2,_T("大小"),LVCFMT_CENTER,200);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFtpClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFtpClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFtpClientDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Connect(m_strServerName,m_strUserName,m_strPassword))
	{
		DisplayContent(_T("*"));
		GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(FALSE);
	}else //连接失败
	{
		AfxMessageBox(_T("连接服务器失败！"),MB_OK|MB_ICONSTOP);
	}

}



void CFtpClientDlg::OnBnClickedButtonUpload()
{
	// TODO: 在此添加控件通知处理程序代码
	Upload();
}



void CFtpClientDlg::OnBnClickedButtonRename()
{
	// TODO: 在此添加控件通知处理程序代码
	Rename();
}


void CFtpClientDlg::OnBnClickedButtonQuery()
{
	// TODO: 在此添加控件通知处理程序代码

	DisplayContent(_T("*"));
}


void CFtpClientDlg::OnBnClickedButtonDownload()
{
	// TODO: 在此添加控件通知处理程序代码
	Download();
}
//退出
void CFtpClientDlg::OnBnClickedButtonLogout()
{
	// TODO: 在此添加控件通知处理程序代码
	delete m_pFTPSession;
	delete m_pConnection;
	delete m_pFileFind;
	m_pFTPSession=NULL;
	m_pConnection = NULL;
	m_pFileFind = NULL;
	DestroyWindow();
}

//显示服务器当前目下的所有文件与子目录
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
		AfxMessageBox(_T("没有找到文件!"),MB_OK | MB_ICONSTOP);
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
			//如果是目录用<子目录>代替
			strFileLength = "<子目录>";
		}	
		else
		{
			//得到文件大小
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



//下载
void CFtpClientDlg::Download(void)
{
	int index=m_listDirectory.GetNextItem(-1,LVNI_SELECTED); 
	if (index==-1)
	{
        AfxMessageBox(_T("请首先选择要下载的文件!"),MB_OK | MB_ICONQUESTION);
	}
	else
	{
        CString strType=m_listDirectory.GetItemText(index,2);   //得到选择项的类型
		if (strType!="<子目录>")   //选择的是文件
		{
			CString strDestName;
			CString strSourceName;
			strSourceName = m_listDirectory.GetItemText(index,0);//得到所要下载的文件名
			
			CFileDialog dlg(FALSE,_T(""),strSourceName);		
			if (dlg.DoModal()==IDOK)
			{
				//获得下载文件在本地机上存储的路径和名称
				strDestName=dlg.GetPathName();		
				//调用CFtpConnect类中的GetFile函数下载文件
				if (m_pConnection->GetFile(strSourceName,strDestName))
					AfxMessageBox(_T("下载成功！"),MB_OK|MB_ICONINFORMATION);
				else
					AfxMessageBox(_T("下载失败！"),MB_OK|MB_ICONSTOP);
			}
		}
		else
		{
			//选择的是目录
			AfxMessageBox(_T("不能下载目录!\n请重选!"),MB_OK|MB_ICONSTOP);
		}
	}
}

//上传
void CFtpClientDlg::Upload(void)
{
	CString strSourceName;
	CString strDestName;
	CFileDialog dlg(TRUE,_T(""),_T("*.*"));
	if (dlg.DoModal()==IDOK)
	{
		//获得待上传的本地文件路径和文件名
		strSourceName = dlg.GetPathName();
		strDestName = dlg.GetFileName();
		
		//调用CFtpConnect类中的PutFile函数上传文件
		if (m_pConnection->PutFile(strSourceName,strDestName))
			AfxMessageBox(_T("上传成功"),MB_OK|MB_ICONINFORMATION);
		else
			AfxMessageBox(_T("上传失败"),MB_OK|MB_ICONSTOP);
	}
    DisplayContent(_T("*"));
}


//文件改名
void CFtpClientDlg::Rename(void)
{
	CString strNewName;
	CString strOldName;
	
	int index=m_listDirectory.GetNextItem(-1,LVNI_SELECTED); //得到CListCtrl被选中的项
	if (index==-1)
	{
        AfxMessageBox(_T("没有选择文件!"),MB_OK | MB_ICONQUESTION);
	}
	else
	{
       	strOldName = m_listDirectory.GetItemText(index,0);//得到所选择的文件名
		CNewNameDlg dlg;		
		if (dlg.DoModal()==IDOK)
		{
			strNewName=dlg.m_NewFileName;
			if (m_pConnection->Rename(strOldName,strNewName))
				AfxMessageBox(_T("重命名成功！"),MB_OK|MB_ICONINFORMATION);
			else
				AfxMessageBox(_T("无法重命名！"),MB_OK|MB_ICONSTOP);
		}
	}	
	DisplayContent(_T("*"));//显示目录
}


void CFtpClientDlg::OnBnClickedButtonSubdir()
{
	// TODO: 在此添加控件通知处理程序代码
	DisplaySubDir();
}


void CFtpClientDlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	DeleteFile();
}


void CFtpClientDlg::OnBnClickedButtonParentdir()
{
	// TODO: 在此添加控件通知处理程序代码
	DisplayParentDir();
}

//删除文件
void CFtpClientDlg::DeleteFile(void)
{
	int index=m_listDirectory.GetNextItem(-1,LVNI_SELECTED); 
	if (index==-1)
	{
        AfxMessageBox(_T("没有选择文件!"),MB_OK | MB_ICONQUESTION);
	}
	else
	{
		CString  strFileName;
		strFileName = m_listDirectory.GetItemText(index,0);
		if (_T("<子目录>")==m_listDirectory.GetItemText(index,2))
		{
			AfxMessageBox(_T("不能删除目录!"),MB_OK | MB_ICONSTOP);
		}
		else
		{
			if (m_pConnection->Remove(strFileName))
				AfxMessageBox(_T("删除成功！"),MB_OK|MB_ICONINFORMATION);
			else
				AfxMessageBox(_T("无法删除！"),MB_OK|MB_ICONSTOP);
		}
	}
	DisplayContent(_T("*"));
}

//显示下级子目录
void CFtpClientDlg::DisplaySubDir(void)
{
	static CString  strCurrentDirectory,strSub;
	
    m_pConnection->GetCurrentDirectory(strCurrentDirectory);
	strCurrentDirectory.Format(_T("%s/"),(strCurrentDirectory));
	
	//得到所选择的文本
	int index=m_listDirectory.GetNextItem(-1,LVNI_SELECTED); 
	strSub = m_listDirectory.GetItemText(index,0);

	if (index==-1)
	{
        AfxMessageBox(_T("没有选择目录!"),MB_OK | MB_ICONQUESTION);
	}
	else
	{   //判断是不是目录
		if (_T("<子目录>")!=m_listDirectory.GetItemText(index,2))
		{
			AfxMessageBox(_T("不是子目录!"),MB_OK | MB_ICONSTOP);
		}
		else
		{
            //设置当前目录
			strCurrentDirectory.Format(_T("%s%s"),strCurrentDirectory,strSub);
			m_pConnection->SetCurrentDirectory(strCurrentDirectory);
			//对当前目录进行查询
			DisplayContent(_T("*"),strCurrentDirectory);
		}
	}	
}

//返回上一级目录的字符串表示
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

//显示父级目录
void CFtpClientDlg::DisplayParentDir(void)
{
	static CString  strCurrentDirectory;
    m_pConnection->GetCurrentDirectory(strCurrentDirectory);
	if (strCurrentDirectory ==_T("/"))
	{
		AfxMessageBox(_T("已经是根目录了!"),MB_OK | MB_ICONSTOP);
	}
	else
	{
        strCurrentDirectory=GetParentDirectory(strCurrentDirectory);
        //设置当前目录
       	m_pConnection->SetCurrentDirectory(strCurrentDirectory);
		//对当前目录进行查询
        DisplayContent(_T("*"),strCurrentDirectory);
	}
}


BOOL CFtpClientDlg::Connect(CString serverName, CString userName, CString password)
{
	m_pFTPSession=new CInternetSession(AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS);		
	try
	{
		//试图建立FTP连接
		m_pConnection=m_pFTPSession->GetFtpConnection(serverName,userName,password);      
	}
	catch (CInternetException* e)
	{
		//错误处理
		e->Delete();
		m_pFTPSession=NULL;
		m_pConnection=NULL;
		return FALSE;
	}
	return TRUE;
}
