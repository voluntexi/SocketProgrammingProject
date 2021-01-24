#pragma once
#include "SmtpSocket.h" //手动添加包含语句
#include "Base64.h" //手动添加包含语句
#include <vector>
#include <strstream>
#include <string>

using namespace std;
//表示显示信息的标志
#define S_CLOSE 1
#define S_CONNECT 2
#define S_RECEIVE 3
#define S_GETNUMMSGS 4 
#define S_GETSIZEMSGS 5 
#define S_ENDRETR 6 

//表示smtp会话状态的枚举类型
typedef enum {FIRST=0,EHLO,AUTH,USER,PASS,MAIL,RCPT,DATA,QUIT} STATE;
// CSmtpSocket定义
class CSmtpClientDlg;//手动添加的声明语句

class CSmtpSocket : public CAsyncSocket
{
public:
	CSmtpSocket();
	virtual ~CSmtpSocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	CSmtpClientDlg* m_pDlg;
	void setParentDlg(CSmtpClientDlg* p_Dlg);   //指向主对话框的指针
public:
	CString lastMsg;
	CString error;
private:
	void AnalyzeMsg();   //分析从服务器发来的数据，做出响应的响应
	STATE state;         //smtp会话的状态
	CBase64 coder;
};



