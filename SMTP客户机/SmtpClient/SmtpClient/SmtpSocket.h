#pragma once
#include "SmtpSocket.h" //�ֶ���Ӱ������
#include "Base64.h" //�ֶ���Ӱ������
#include <vector>
#include <strstream>
#include <string>

using namespace std;
//��ʾ��ʾ��Ϣ�ı�־
#define S_CLOSE 1
#define S_CONNECT 2
#define S_RECEIVE 3
#define S_GETNUMMSGS 4 
#define S_GETSIZEMSGS 5 
#define S_ENDRETR 6 

//��ʾsmtp�Ự״̬��ö������
typedef enum {FIRST=0,EHLO,AUTH,USER,PASS,MAIL,RCPT,DATA,QUIT} STATE;
// CSmtpSocket����
class CSmtpClientDlg;//�ֶ���ӵ��������

class CSmtpSocket : public CAsyncSocket
{
public:
	CSmtpSocket();
	virtual ~CSmtpSocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	CSmtpClientDlg* m_pDlg;
	void setParentDlg(CSmtpClientDlg* p_Dlg);   //ָ�����Ի����ָ��
public:
	CString lastMsg;
	CString error;
private:
	void AnalyzeMsg();   //�����ӷ��������������ݣ�������Ӧ����Ӧ
	STATE state;         //smtp�Ự��״̬
	CBase64 coder;
};



