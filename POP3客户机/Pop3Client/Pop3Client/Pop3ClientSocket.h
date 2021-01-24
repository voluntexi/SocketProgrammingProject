#pragma once
#include <vector>
#include <strstream>
#include <string>
using namespace std;

class  CPop3ClientDlg;

// CPop3ClientSocket����
//��ʾ��ͬ��Ϣ�ı�־
#define S_CLOSE   1  //���ر�����ʱ����ʾ�ر���Ϣ
#define S_CONNECT 2  //�����ӳɹ�ʱ����ʾ������Ϣ
#define S_RECEIVE 3  //���յ���������������Ϣʱ����ʾ����Ϣ
#define S_GETNUM  4 //�������ż�������Ϻ���ʾ�����е��ż�����
#define S_GETSIZE 5 //�������ż�������Ϻ���ʾ�����е��ż��ܴ�С
#define S_ENDRETR 6 //�������ż�������Ϻ���ʾ�����Ϣ

//����pop3�Ự״̬��ö������
typedef enum {FIRST=0,USER,PASS,STAT,LIST,RETR,ENDRETR,DELE,GOON} STATE;

//��������һ���ż���Ϣ�Ľṹ
typedef struct 
{
	CString text;  //�洢�ż����ı�
	int msgSize;   //�ż��Ĵ�С
	int	retrSize;  //�ż�ʵ�����صĴ�С�������ع����ж�̬�仯
} MESSAGEPROP;


class CPop3ClientSocket : public CAsyncSocket
{
	public:
	CString lastMsg;
	CString error;
	int numMsg, sizeMsg, retrMsg;
	vector<MESSAGEPROP> msgs; //ʢ���ż���Ϣ������
		//��û������ʼ���ͷ�ֶ�: From, To, Date, Subject, Body
	CString GetMsgStuff(int i); 
	CString GetMsgBody(int i);     //����ż���
	CString GetMsgSubject(int i);  //����ż�����
	CString GetMsg(int i);         //��������ŵ�����
	CString ReadLn(int index,CString src);

	void Close();            //�˳�������
public:
	CPop3ClientSocket();
	virtual ~CPop3ClientSocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
//	void SetParentDlg(void);
private:
	void AnalyzeMsg();
	STATE state;
	int delMsg;
public:
	CPop3ClientDlg* m_pDlg;
	void SetParentDlg(CPop3ClientDlg* pDlg);
};


