//����7.4 ���߳�ͬ��ʵ��֮һ��������
// Counter.cpp�������߳���ʾ
#include <windows.h>
#include <stdio.h>
#include <process.h>

unsigned Counter; 
//����һ���������߳�
unsigned __stdcall SecondThreadFunc( void* pArguments )
{
	printf( "�߳�#2��ʼ����...������Ҫѭ��1�����\n" );

    while ( Counter < 1000000 )
        Counter++;

    _endthreadex( 0 );
    return 0;
} 

int main()
{ 
    HANDLE hThread;
    unsigned threadID;

    printf( "�����߳�#2...\n" );
    // �����ڶ����߳�
    hThread = (HANDLE)_beginthreadex( NULL, 0, &SecondThreadFunc, NULL, 0, &threadID );

    // �ȴ���ֱ���ڶ����߳���ֹ�����ע�͵�������У�
    // ��������������ȷ��������Ϊ�̻߳�û����ֹ�������������ܵ�����1000000
    WaitForSingleObject( hThread, INFINITE );
    printf( "���������������Ӧ����1000000; ��ʵ����������-> %d\n", Counter );
    // �����̶߳���
    CloseHandle( hThread );
}
