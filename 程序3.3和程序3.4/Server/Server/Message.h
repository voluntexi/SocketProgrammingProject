// CMessage����
#pragma once
class CMessage : public CObject
{
public:
	CMessage();
	virtual ~CMessage();
	CString m_strMessage;//�ַ�����Ϣ
	BOOL m_bClosed;//�Ƿ�ر�
	virtual void Serialize(CArchive& ar);//���ػ������л�����
};


