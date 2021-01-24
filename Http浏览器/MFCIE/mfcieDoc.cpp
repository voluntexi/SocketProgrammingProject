// mfcieDoc.cpp : CMfcieDoc 的实现

#include "stdafx.h"
#include "mfcie.h"

#include "mfcieDoc.h"

IMPLEMENT_DYNCREATE(CMfcieDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcieDoc, CDocument)
END_MESSAGE_MAP()

CMfcieDoc::CMfcieDoc()
{ }

CMfcieDoc::~CMfcieDoc()
{ }

BOOL CMfcieDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

// CMfcieDoc序列化
void CMfcieDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

