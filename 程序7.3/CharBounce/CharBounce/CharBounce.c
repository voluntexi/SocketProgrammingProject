//程序7.3字符飘移线程完整代码

// CharBounce.c字符飘移
#include <windows.h>
#include <process.h>    /* _beginthread, _endthread */
#include <stddef.h>
#include <stdlib.h>
#include <conio.h>

void Bounce( void *ch );
void CheckKey( void *dummy );

/* 返回一个介于min和max之间的随机数 */
#define GetRandom( min, max ) ((rand() % (int)(((max) + 1) - (min))) + (min))

BOOL repeat = TRUE;     /*全局变量，重复执行标志 */
HANDLE hStdOut;         /* 控制台窗口句柄 */
CONSOLE_SCREEN_BUFFER_INFO csbi;    /*控制台的信息结构 */

int main()
{
    CHAR    ch = 'A';

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );

    /* 显示屏幕的文本行和列的信息。 */
   GetConsoleScreenBufferInfo( hStdOut, &csbi );

    /* 创建启动CheckKey线程，检查按键，终止程序。*/
    _beginthread( CheckKey, 0, NULL );

    /* 循环直到CheckKey线程终止程序。 */
    while( repeat )
    {
        /* On first loops, launch character threads. */
        _beginthread( Bounce, 0, (void *) (ch++)  );

        /* Wait one second between loops. */
        Sleep( 1000L );
    }
}

/* CheckKey - 线程等待一个按键，然后重复标志置0。*/
void CheckKey( void *dummy )
{
    _getch();
    repeat = 0;    /* 执行_endthread的条件*/

}

/* 弹跳 - 线程创建和控制的彩色字母在屏幕上四处飘移
 * 参数: ch - 飘移的字母 */
void Bounce( void *ch )
{
    /* 字母和颜色属性 */
    char    blankcell = 0x20;
    char    blockcell = (char) ch;
    BOOL    first = TRUE;
    COORD   oldcoord, newcoord;
    DWORD   result;


    /* 设置随机数发生器种子和字母初始位置。 */
    srand( _threadid );
    newcoord.X = GetRandom( 0, csbi.dwSize.X - 1 );
    newcoord.Y = GetRandom( 0, csbi.dwSize.Y - 1 );
    while( repeat )
    {
        /* 暂停循环时间 */
        Sleep( 100L );

        /* 清空原位置字母，在新位置绘制字母 */
        if( first )
            first = FALSE;
        else
         WriteConsoleOutputCharacter( hStdOut, &blankcell, 1, oldcoord, &result );
         WriteConsoleOutputCharacter( hStdOut, &blockcell, 1, newcoord, &result );

        /* 下一个位置的坐标值*/
        oldcoord.X = newcoord.X;
        oldcoord.Y = newcoord.Y;
        newcoord.X += GetRandom( -1, 1 );
        newcoord.Y += GetRandom( -1, 1 );

        /* 如果字母离开控制台窗口，响一声（哔） */
        if( newcoord.X < 0 )
            newcoord.X = 1;
        else if( newcoord.X == csbi.dwSize.X )
            newcoord.X = csbi.dwSize.X - 2;
        else if( newcoord.Y < 0 )
            newcoord.Y = 1;
        else if( newcoord.Y == csbi.dwSize.Y )
            newcoord.Y = csbi.dwSize.Y - 2;

        /* 如果在窗口内部，继续移动下去，否则响声*/
        else
            continue;
        Beep( ((char) ch - 'A') * 100, 175 );
    }
    /* 调用终止线程函数 */
    _endthread();
}
