// Message.cpp : ʵ���ļ�
#include "stdafx.h"
#include "Server.h"
#include "Message.h"

CMessage::CMessage()
{
	m_strMessage = _T("");//�����Զ����
	m_bClosed=FALSE;//�ֶ����
}
CMessage::~CMessage()
{}

// CMessage ��Ա����
//�����Զ����
void CMessage::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// �������ݴ��룬�ֶ����
		ar<<(WORD)m_bClosed;
		ar<<m_strMessage;
	}
	else
	{	// �������ݴ��룬�ֶ����
		WORD wd;
		ar>>wd;
		m_bClosed=(BOOL)wd;
		ar>>m_strMessage;
	}
}
