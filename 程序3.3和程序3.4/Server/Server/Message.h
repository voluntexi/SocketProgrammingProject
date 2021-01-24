// CMessage定义
#pragma once
class CMessage : public CObject
{
public:
	CMessage();
	virtual ~CMessage();
	CString m_strMessage;//字符串消息
	BOOL m_bClosed;//是否关闭
	virtual void Serialize(CArchive& ar);//重载基类序列化函数
};


