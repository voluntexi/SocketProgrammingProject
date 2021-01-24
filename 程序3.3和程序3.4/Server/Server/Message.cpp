// Message.cpp : 实现文件
#include "stdafx.h"
#include "Server.h"
#include "Message.h"

CMessage::CMessage()
{
	m_strMessage = _T("");//类向导自动添加
	m_bClosed=FALSE;//手动添加
}
CMessage::~CMessage()
{}

// CMessage 成员函数
//类向导自动添加
void CMessage::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// 发送数据代码，手动添加
		ar<<(WORD)m_bClosed;
		ar<<m_strMessage;
	}
	else
	{	// 接收数据代码，手动添加
		WORD wd;
		ar>>wd;
		m_bClosed=(BOOL)wd;
		ar>>m_strMessage;
	}
}
