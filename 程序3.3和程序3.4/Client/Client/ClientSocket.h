// CClientSocket����
#pragma once
class CClientDlg;  //�Ի������������ֶ����
class CClientSocket : public CSocket
{
public:
	CClientSocket(CClientDlg* pDlg);//Ϊ���캯�������ڲ������ֶ����
	virtual ~CClientSocket();
	//������������������
	CClientDlg* m_pDlg;//��Ա����
	virtual void OnReceive(int nErrorCode);
};


