// mfcieDoc.h : CMfcieDoc��Ķ���
#pragma once
class CMfcieDoc : public CDocument
{
protected: //�������л�����
	CMfcieDoc();
	DECLARE_DYNCREATE(CMfcieDoc)

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

public:
	virtual ~CMfcieDoc();
	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};
