
// Pop3Client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�

#pragma once

#include "resource.h"		// ������


// CPop3ClientApp:
// �йش����ʵ�֣������ Pop3Client.cpp
//

class CPop3ClientApp : public CWinApp
{
public:
	CPop3ClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPop3ClientApp theApp;