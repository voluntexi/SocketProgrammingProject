
// FtpClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFtpClientApp:
// �йش����ʵ�֣������ FtpClient.cpp
//

class CFtpClientApp : public CWinApp
{
public:
	CFtpClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFtpClientApp theApp;