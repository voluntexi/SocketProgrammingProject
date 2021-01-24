// mfcieDoc.h : CMfcieDoc类的定义
#pragma once
class CMfcieDoc : public CDocument
{
protected: //仅从序列化创建
	CMfcieDoc();
	DECLARE_DYNCREATE(CMfcieDoc)

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

public:
	virtual ~CMfcieDoc();
	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};
