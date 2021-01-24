// Message.cpp : 实现文件
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

// CMessage 成员函数
void CMessage::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// 发送数据
		ar<<(WORD)m_bClosed;
		ar<<m_strMessage;
	}
	else
	{	// 接收数据
		WORD wd;
		ar>>wd;
		m_bClosed=(BOOL)wd;
		ar>>m_strMessage;
	}
}
