// CMessage∂®“Â
#pragma once

class CMessage : public CObject
{
public:
	CMessage();
	virtual ~CMessage();
	CString m_strMessage;
	BOOL m_bClosed;
	virtual void Serialize(CArchive& ar);
};


