//程序7.4 多线程同步实例之一完整代码
// Counter.cpp计数器线程演示
#include <windows.h>
#include <stdio.h>
#include <process.h>

unsigned Counter; 
//定义一个计数器线程
unsigned __stdcall SecondThreadFunc( void* pArguments )
{
	printf( "线程#2开始工作...接下来要循环1百万次\n" );

    while ( Counter < 1000000 )
        Counter++;

    _endthreadex( 0 );
    return 0;
} 

int main()
{ 
    HANDLE hThread;
    unsigned threadID;

    printf( "创建线程#2...\n" );
    // 创建第二个线程
    hThread = (HANDLE)_beginthreadex( NULL, 0, &SecondThreadFunc, NULL, 0, &threadID );

    // 等待，直到第二个线程终止。如果注释掉下面的行，
    // 计数器将不能正确工作，因为线程还没有终止。计数器将不能递增到1000000
    WaitForSingleObject( hThread, INFINITE );
    printf( "计数器最后输出结果应该是1000000; 真实的输出结果是-> %d\n", Counter );
    // 销毁线程对象
    CloseHandle( hThread );
}
