// CServerSocket����
#pragma once
class CServerDlg; //�����������Ի�����
class CServerSocket : public CSocket
{
public:
	CServerSocket(CServerDlg* pDlg);//�����ڲ���
	virtual ~CServerSocket();
	//�ص��������׽����յ���������ʱ���Զ����ô˺���
	virtual void OnAccept(int nErrorCode);
	CServerDlg* m_pDlg; //ָ��������Ի������ָ��
};


