#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

// ��2���̺߳���
void ThreadProc(void *param);

// ��1���̺߳���
int main()
{
	int n;
	int i;
	int val = 0;
	HANDLE handle;

	printf("\t C���Զ��߳���ʾ\n");
	printf("������ϣ���������߳��� : ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		val = i+1;
		handle = (HANDLE) _beginthread( ThreadProc,0,&val); //�����߳�
		WaitForSingleObject(handle,INFINITE);	
	}
	return 0;
}

void ThreadProc(void *param)
{
	int h=*((int*)param);
	printf("�� %d ���߳���������......\n",h);
	_endthread();
}

