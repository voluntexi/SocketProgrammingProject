#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

// 第2个线程函数
void ThreadProc(void *param);

// 第1个线程函数
int main()
{
	int n;
	int i;
	int val = 0;
	HANDLE handle;

	printf("\t C语言多线程演示\n");
	printf("请输入希望开启的线程数 : ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		val = i+1;
		handle = (HANDLE) _beginthread( ThreadProc,0,&val); //创建线程
		WaitForSingleObject(handle,INFINITE);	
	}
	return 0;
}

void ThreadProc(void *param)
{
	int h=*((int*)param);
	printf("第 %d 个线程正在运行......\n",h);
	_endthread();
}

