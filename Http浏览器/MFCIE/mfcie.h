// mfcie.h£¨CMfcieApp¿‡∂®“Â
#pragma once
#include "resource.h"  

class CMfcieApp : public CWinApp
{
public:
	CMfcieApp();
	virtual BOOL InitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};
