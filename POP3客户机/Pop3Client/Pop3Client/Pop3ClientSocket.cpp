// m_pop3ClientSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Pop3ClientDlg.h" //�ֶ���Ӱ������

// CPop3ClientSocket
#define MAX_BUFF 20000
CPop3ClientSocket::CPop3ClientSocket()
{
	m_pDlg = NULL;
	state=FIRST;
	error="���ӷ���������\r\n";
}

CPop3ClientSocket::~CPop3ClientSocket()
{
	m_pDlg = NULL;
}


// CPop3ClientSocket ��Ա����


void CPop3ClientSocket::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnConnect(nErrorCode);
	if(nErrorCode==0)  m_pDlg->DisplayInfo(S_CONNECT);
}


void CPop3ClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnReceive(nErrorCode);
	if(nErrorCode==0) 
	{
		char buff[MAX_BUFF];            //���ջ�����
		int rec=Receive(buff,MAX_BUFF); //���շ���������������
		

		buff[rec]=_T('\0');
		CString szTemp(buff);

		lastMsg=szTemp;
		AnalyzeMsg();                      //�����յ������ݣ�����ͬ�Ĵ���
	}  else  {
		error="�ڽ�������ʱ�����˴���!\r\n";
		m_pDlg->DisplayInfo(S_CLOSE);   //��ʾ��Ϣ
	}
}


void CPop3ClientSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnClose(nErrorCode);
	if(nErrorCode==0)  m_pDlg->DisplayInfo(S_CLOSE);
}



void CPop3ClientSocket::SetParentDlg(CPop3ClientDlg* pDlg)
{
	m_pDlg = pDlg;
}
//��õ� i ���ż��ı�����Ϣ
CString CPop3ClientSocket::GetMsgStuff(int i)
{
	CString ret;
CString s;
	int where=msgs[i].text.Find(_T("From:"));

s.Format(_T("From:λ�ã�%d\r\n"),where);
m_pDlg->m_mailInfo+=s;
	
	if (where!=-1)
	{
		ret+=ReadLn(where,msgs[i].text);
		ret+="\r\n";
	}

	where=msgs[i].text.Find(_T("To:"));

s.Format(_T("To:λ�ã�%d\r\n"),where);
m_pDlg->m_mailInfo+=s;
	
	if (where!=-1)
	{
		ret+=ReadLn(where,msgs[i].text);
		ret+="\r\n";
	}
	
	where=msgs[i].text.Find(_T("Date:"));

s.Format(_T("Date:λ�ã�%d\r\n"),where);
m_pDlg->m_mailInfo+=s;
	
	if (where!=-1)
	{
		ret+=ReadLn(where,msgs[i].text);	
		ret+="\r\n";
	}
	ret+=GetMsgSubject(i);
	ret+="\r\n";
	return ret;

}

//��õ� i ���ż����ż���
CString CPop3ClientSocket::GetMsgBody(int i)
{
	CString ret;
	int where=msgs[i].text.Find(_T("\r\n\r\n"));
	if(where!=-1) where+=4;
	else          where=0;
	ret=msgs[i].text.Right(msgs[i].text.GetLength()-where);
	ret=ret.Left(ret.GetLength()-3);
	return ret;
}

//��õ� i ���ż��ı���
CString CPop3ClientSocket::GetMsgSubject(int i)
{
//	CString s;
//	s.Format("%s",msgs[i].text);
//	int where=s.Find("Subject:");
	
	CString ret;
	int where=msgs[i].text.Find(_T("Subject:"));
	if (where!=-1) 	ret=ReadLn(where,msgs[i].text);
	else ret.Format(_T("�Ҳ���Subject:"));
	return ret;
}

//��õ� i ���������ŵ�����
CString CPop3ClientSocket::GetMsg(int i)
{
	return msgs[i].text;
}

//��src���У���index��ָ��λ�ÿ�ʼ��ȡ���ִ���ֱ����ĩ��"\r"Ϊֹ��
//dst��һ�����ĵ�ַ��ȡ������׷���ڸô���ԭ����֮��
CString CPop3ClientSocket::ReadLn(int index,CString src)
{
//	CString comp;
//	CString dst;
//	comp=src[index];
//	while(comp!="\r")
//	{
//		dst+=comp;
//		comp=src[++index];
//	}
//	return dst;

	CString ret;
	CString s;
	
	ret=src.Right(src.GetLength()-index);
	int where=ret.Find(_T("\r"));
//	s.Format("�����ڵ�λ�ã�%d",where);
//	m_pDlg->m_mailInfo+=s;
//	m_pDlg->UpdateData(FALSE);
	if(where!=-1) where+=1;
	else          where=0;
//	s.Format("�����ڵ�λ�ã�%d, Length=%d ",where,ret.GetLength());
//	m_pDlg->m_mailInfo+=s;
//	m_pDlg->UpdateData(FALSE);
	
	ret=ret.Left(where);
	return ret;

}

 
 //�˳�������
void CPop3ClientSocket::Close()
{
	CString str;
	str.Format(_T("quit%c%c"),13,10);
	Send((LPCSTR)str,str.GetLength());
	m_pDlg->DisplayInfo(S_CLOSE);
	state=FIRST;
	CAsyncSocket::Close();
	error="ִ��CPop3ClientSocket::Close()���Not connected to server\r\n";
}

void CPop3ClientSocket::AnalyzeMsg()
{
	int  ix;
	CString temp1;
	CString temp2;

	CString s;
	strstream str;
	string check;
	str<<(LPCSTR)lastMsg; //���յ�����Ϣ�������ַ���������  
	str>>check;           //��ȡ���յ���Ϣ�ĵ�һ�δ���
	if(check=="-ERR")     //����д���
	{
		error="Received -ERR from server :"+lastMsg;
		Close(); //�Ͽ����ӣ�Ȼ��ر�
		return;
	}
	
	//���û�д�������ݲ�ͬ�ĻỰ�׶���Ӧ������
	switch(state) 
	{
	case FIRST: //����Ѿ����ӳɹ������ʼ����ʱ��stateΪFIRST
		msgs.clear();
		//��ʾ���ӳɹ�����������ص���Ϣ
		m_pDlg->DisplayInfo(S_RECEIVE); 
		//���� user �û��� ����
		s.Format("user %s%c%c",m_pDlg->m_strMailBox,13,10);
		Send((LPCSTR)s,s.GetLength()); //�����û��ʺ�
		state=USER;
		break;

	case USER:
		//��ʾ����������user�������Ӧ
		m_pDlg->DisplayInfo(S_RECEIVE);
		//���� pass ���� �����������
		s.Format(_T("pass %s%c%c"),m_pDlg->m_strPassword,13,10); 
		Send((LPCSTR)s,s.GetLength()); 
		state=PASS;
		break;

	case PASS:
		//��ʾ�������� pass �������Ӧ
		m_pDlg->DisplayInfo(S_RECEIVE);
		//���� stat ����������������������
		//�ʼ�����������ռ�ռ�Ĵ�С
		s.Format(_T("stat%c%c"),13,10);
		Send((LPCSTR)s,s.GetLength());
		state=STAT; 
		break;

	case STAT:
	{
		string s1;
		str.seekg(0);  //���ַ����ĵ�ǰָ����Ϊ0
		str>>s1>>numMsg>>sizeMsg; //��������ʹ�С
		flush(str);
		m_pDlg->DisplayInfo(S_GETNUM);
		m_pDlg->DisplayInfo(S_GETSIZE);
		if(numMsg>0) //������ʼ�������RETR����ʼ���Ϣ
		{
			retrMsg=1;        //Ҫȡ��һ����
			MESSAGEPROP prop; //׼������ż��ĵط�
			prop.msgSize=0;   //��Ա�ó�ֵ
			prop.retrSize=0;
			prop.text="";
			msgs.push_back(prop); //ѹ��������
			s.Format(_T("retr 1%c%c"),13,10);
			Send((LPCSTR)s,s.GetLength()); 
			state=RETR;
		}
		else //���û���ʼ�����Ͽ�
		{
			error="No new messages\r\n";
			Close();
		}
	}
	break;

	case RETR:
	{
		//��ʾȡ�������ż��ı�

s.Format(_T("numMsg= %d  retrMsg =%d"),numMsg,retrMsg);	
m_pDlg->m_mailInfo+=s;
s.Format(_T("�ż���%d: ,�ż���С%d, �ż����ݣ� %s   �ż�����%c%c"),
		 retrMsg-1,lastMsg.GetLength(),lastMsg,13,10);
m_pDlg->m_mailInfo+=s;
m_pDlg->UpdateData(FALSE);		

		m_pDlg->DisplayInfo(S_RECEIVE);
		//һ���ŵ����ݿ��ܶ�β��ܽ��ܻ��������Ƕ���һ���ţ���һ��
		//���յ����ݵ�ʱ�򣬶�Ӧ�����ṹ��msgSize��Ա����Ϊ0
		//if(msgs[retrMsg-1].msgSize==0) 
		//{
//			string temp;
//			str.seekg(0);
			//�����ż��Ĵ�С��ŵ���Ա������
//			str>>temp>>msgs[retrMsg-1].msgSize; 
//		}
		//ix=lastMsg.Find("\r\n.\r\n");
		//if (ix == -1)
		//{
		//	msgs[retrMsg-1].text+=lastMsg;
		//	msgs[retrMsg-1].retrSize+=lastMsg.GetLength();
		//} else  {
		//	temp1=lastMsg.Left(ix+5);
		//	temp2=lastMsg.Right(lastMsg.GetLength()-ix-5);
		//	msgs[retrMsg-1].text+=temp1;
		//	msgs[retrMsg-1].retrSize +=temp1.GetLength();
		//}


		//������׷�ӱ��浽text��Ա������
		msgs[retrMsg-1].text+=lastMsg; 
		//�����ݴ�С�ۼӵ�retrSize��Ա�����У������Ѿ�ȡ����������
		msgs[retrMsg-1].retrSize+=lastMsg.GetLength();
		//�ж��Ƿ���������ŵ���������
		//if(msgs[retrMsg-1].retrSize>=msgs[retrMsg-1].msgSize)
		//{  //����Ƿ��������ʼ�
	
		ix=lastMsg.Find(_T("\r\n.\r\n"));
		if (ix != -1)	//�ҵ�������ŵĽ�β
		{	
			//����Ƿ��������ʼ�
			if(retrMsg<numMsg) //������У����������retr����
			{
				MESSAGEPROP prop;
				prop.msgSize=0;
				prop.retrSize=0;
				prop.text="";
				msgs.push_back(prop);
				retrMsg++;
				//��retr����ȡ��һ����
				s.Format(_T("retr %d%c%c"),retrMsg,13,10);
				Send((LPCSTR)s,s.GetLength());
			}  else	{
				//���ȫ���ż�������ϣ��ж��Ƿ�Ҫɾ��
				
				if(m_pDlg->m_bDelMail && numMsg>0) 
				{
					state=DELE;
					delMsg=1;
					s.Format("dele %d%c%c",delMsg,13,10);
					Send((LPCSTR)s,s.GetLength());
				}  else {                      //�����˳�
					state=ENDRETR;
					m_pDlg->DisplayInfo(S_ENDRETR);
					error="�ż�������,��ɾ�ʼ����Ự����\r\n";
					s.Format(_T("quit%c%c"),13,10);
					Send((LPCSTR)s,s.GetLength());
					Close();

					for(int i=0;i<retrMsg;i++)
					{
						s.Format(_T("%d:  %s"),i,GetMsgSubject(i));
			//m_pDlg->m_mailInfo+=s;

						m_pDlg->m_comboTitle.AddString(s);
				//		m_pDlg->m_ctrList.AddString((LPCSTR)GetMsgSubject(i));
					}
			//m_pDlg->UpdateData(FALSE);
					m_pDlg->m_comboTitle.SetCurSel(0);
				}
			}
		}  //DEBUG 
		//}
	}
	break;

	case DELE:
	{
		//ɾ��ʣ���ʼ�
		if(delMsg<numMsg)
		{
			delMsg++;
			s.Format(_T("dele %d%c%c"),delMsg,13,10);
			Send((LPCSTR)s,s.GetLength());
		}
		else //����Ѿ�ɾ�����
		{
			m_pDlg->DisplayInfo(S_ENDRETR);
			state=GOON;
			error="Deleted all messages\r\n";
			s.Format(_T("quit%c%c"),13,10);
			Send((LPCSTR)s,s.GetLength());
			Close();
		}
	}
	break;
	
	case GOON:
	
	default:
		m_pDlg->DisplayInfo(S_RECEIVE);
		break;
	}
}