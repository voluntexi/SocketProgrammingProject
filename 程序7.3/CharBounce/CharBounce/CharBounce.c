//����7.3�ַ�Ʈ���߳���������

// CharBounce.c�ַ�Ʈ��
#include <windows.h>
#include <process.h>    /* _beginthread, _endthread */
#include <stddef.h>
#include <stdlib.h>
#include <conio.h>

void Bounce( void *ch );
void CheckKey( void *dummy );

/* ����һ������min��max֮�������� */
#define GetRandom( min, max ) ((rand() % (int)(((max) + 1) - (min))) + (min))

BOOL repeat = TRUE;     /*ȫ�ֱ������ظ�ִ�б�־ */
HANDLE hStdOut;         /* ����̨���ھ�� */
CONSOLE_SCREEN_BUFFER_INFO csbi;    /*����̨����Ϣ�ṹ */

int main()
{
    CHAR    ch = 'A';

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );

    /* ��ʾ��Ļ���ı��к��е���Ϣ�� */
   GetConsoleScreenBufferInfo( hStdOut, &csbi );

    /* ��������CheckKey�̣߳���鰴������ֹ����*/
    _beginthread( CheckKey, 0, NULL );

    /* ѭ��ֱ��CheckKey�߳���ֹ���� */
    while( repeat )
    {
        /* On first loops, launch character threads. */
        _beginthread( Bounce, 0, (void *) (ch++)  );

        /* Wait one second between loops. */
        Sleep( 1000L );
    }
}

/* CheckKey - �̵߳ȴ�һ��������Ȼ���ظ���־��0��*/
void CheckKey( void *dummy )
{
    _getch();
    repeat = 0;    /* ִ��_endthread������*/

}

/* ���� - �̴߳����Ϳ��ƵĲ�ɫ��ĸ����Ļ���Ĵ�Ʈ��
 * ����: ch - Ʈ�Ƶ���ĸ */
void Bounce( void *ch )
{
    /* ��ĸ����ɫ���� */
    char    blankcell = 0x20;
    char    blockcell = (char) ch;
    BOOL    first = TRUE;
    COORD   oldcoord, newcoord;
    DWORD   result;


    /* ������������������Ӻ���ĸ��ʼλ�á� */
    srand( _threadid );
    newcoord.X = GetRandom( 0, csbi.dwSize.X - 1 );
    newcoord.Y = GetRandom( 0, csbi.dwSize.Y - 1 );
    while( repeat )
    {
        /* ��ͣѭ��ʱ�� */
        Sleep( 100L );

        /* ���ԭλ����ĸ������λ�û�����ĸ */
        if( first )
            first = FALSE;
        else
         WriteConsoleOutputCharacter( hStdOut, &blankcell, 1, oldcoord, &result );
         WriteConsoleOutputCharacter( hStdOut, &blockcell, 1, newcoord, &result );

        /* ��һ��λ�õ�����ֵ*/
        oldcoord.X = newcoord.X;
        oldcoord.Y = newcoord.Y;
        newcoord.X += GetRandom( -1, 1 );
        newcoord.Y += GetRandom( -1, 1 );

        /* �����ĸ�뿪����̨���ڣ���һ�����٣� */
        if( newcoord.X < 0 )
            newcoord.X = 1;
        else if( newcoord.X == csbi.dwSize.X )
            newcoord.X = csbi.dwSize.X - 2;
        else if( newcoord.Y < 0 )
            newcoord.Y = 1;
        else if( newcoord.Y == csbi.dwSize.Y )
            newcoord.Y = csbi.dwSize.Y - 2;

        /* ����ڴ����ڲ��������ƶ���ȥ����������*/
        else
            continue;
        Beep( ((char) ch - 'A') * 100, 175 );
    }
    /* ������ֹ�̺߳��� */
    _endthread();
}
