// mfcieDoc.cpp : CMfcieDoc ��ʵ��

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

// CMfcieDoc���л�
void CMfcieDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

