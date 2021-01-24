// Message.cpp : ʵ���ļ�
#include "stdafx.h"
#include "Client.h"
#include "Message.h"

CMessage::CMessage()
{
	m_strMessage = _T("");
	m_bClosed=FALSE;
}

CMessage::~CMessage()
{}

// CMessage ��Ա����
void CMessage::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// ��������
		ar<<(WORD)m_bClosed;
		ar<<m_strMessage;
	}
	else
	{	// ��������
		WORD wd;
		ar>>wd;
		m_bClosed=(BOOL)wd;
		ar>>m_strMessage;
	}
}
