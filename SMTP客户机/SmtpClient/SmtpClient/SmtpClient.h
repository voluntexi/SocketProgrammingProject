
// SmtpClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSmtpClientApp:
// �йش����ʵ�֣������ SmtpClient.cpp
//

class CSmtpClientApp : public CWinApp
{
public:
	CSmtpClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSmtpClientApp theApp;