// CClientSocket����
#pragma once
class CServerDlg;
class CMessage;

class CClientSocket : public CSocket
{
public:
	CClientSocket(CServerDlg* pDlg);//Ϊ���캯��������ڲ���
	virtual ~CClientSocket();
	//���ػص��������׽����յ�����ʱ���Զ����ô˺���
	virtual void OnReceive(int nErrorCode);
	CServerDlg* m_pDlg;//����ָ�����Ի������ָ��
	CSocketFile* m_pFile; //����ָ��CSocketFile�����ָ��
	CArchive* m_pArchiveIn;//����ָ������CArchive�����ָ��
	CArchive* m_pArchiveOut;//����ָ�����CArchive�����ָ��
	void SendMessage(CMessage* pMsg);//������Ϣ
	void ReceiveMessage(CMessage* pMsg);//������Ϣ
	void Init(void);//��ʼ��
};


