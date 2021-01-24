// Five.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#include "resource.h"		// 主符号
// CFiveApp:
// 有关此类的实现，请参阅 Five.cpp

class CFiveApp : public CWinApp
{
public:
	CFiveApp();
	TCHAR m_szIni[MAX_PATH];
    int m_nWin;
    int m_nDraw;
    int m_nLost;

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CFiveApp theApp;