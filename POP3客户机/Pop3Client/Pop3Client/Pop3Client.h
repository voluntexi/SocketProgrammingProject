
// Pop3Client.h : PROJECT_NAME 应用程序的主头文件

#pragma once

#include "resource.h"		// 主符号


// CPop3ClientApp:
// 有关此类的实现，请参阅 Pop3Client.cpp
//

class CPop3ClientApp : public CWinApp
{
public:
	CPop3ClientApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CPop3ClientApp theApp;