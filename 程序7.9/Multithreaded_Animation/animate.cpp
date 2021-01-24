# include <afxwin.h>
# include <afxext.h>
# include <stdio.h>
# include "resource.h"

CWinThread *pThread1,*pThread2,*pThread3,*pThread4,*pThread5,*pThread6,*pThread7,*pThread8,*pThread9,*pThread10;

int posx,posy;
UINT Thread1(LPVOID lp)
{
			CBitmap bmp;
			BITMAP bit;
			CDC cMemdc;
			CDC *dc;
			dc=CDC::FromHandle((HDC)LOWORD(lp));
			int col;
			col=HIWORD(lp);
			CClientDC cdc(AfxGetApp()->m_pMainWnd);
			bmp.LoadBitmap(IDB_BITMAP1);
			bmp.GetObject(sizeof(BITMAP),&bit);
			cMemdc.CreateCompatibleDC(&cdc);
			cMemdc.SelectObject(&bmp);
			
			for(int posx=10, posy=4;posx<=510;posx++)
			{


			cdc.BitBlt(posx,posy,bit.bmWidth,bit.bmHeight,&cMemdc,0,0,SRCCOPY);
			Sleep(2);
			}

			return 0;
		}

UINT Thread2(LPVOID lp)
	{
			CBitmap bmp;
			BITMAP bit;
			CDC cMemdc;
			CDC *dc;
			dc=CDC::FromHandle((HDC)LOWORD(lp));
			int col;

			col=HIWORD(lp);

			CClientDC cdc(AfxGetApp()->m_pMainWnd);
			bmp.LoadBitmap(IDB_BITMAP2);
			bmp.GetObject(sizeof(BITMAP),&bit);
			cMemdc.CreateCompatibleDC(&cdc);
			cMemdc.SelectObject(&bmp);
			for(posx=10,posy=44;posx<=540;posx++)
			{

			cdc.BitBlt(posx,posy,bit.bmWidth,bit.bmHeight,&cMemdc,0,0,SRCCOPY);
			Sleep(7);
			}

			return 0;
	}

UINT Thread3(LPVOID lp)
	{
			CBitmap bmp;
			BITMAP bit;
			CDC cMemdc;
			CDC *dc;
			dc=CDC::FromHandle((HDC)LOWORD(lp));
			int col;

			col=HIWORD(lp);

			CClientDC cdc(AfxGetApp()->m_pMainWnd);
			bmp.LoadBitmap(IDB_BITMAP3);
			bmp.GetObject(sizeof(BITMAP),&bit);
			cMemdc.CreateCompatibleDC(&cdc);
			cMemdc.SelectObject(&bmp);
		
			for(int posx=10,posy=84;posx<=510;posx++)
			{

			cdc.BitBlt(posx,posy,bit.bmWidth,bit.bmHeight,&cMemdc,0,0,SRCCOPY);
			Sleep(5);
			}

			
		return 0;
	}
UINT Thread4(LPVOID lp)
	{
			CBitmap bmp;
			BITMAP bit;
			CDC cMemdc;
			CDC *dc;
			dc=CDC::FromHandle((HDC)LOWORD(lp));
			int col;

			col=HIWORD(lp);

			CClientDC cdc(AfxGetApp()->m_pMainWnd);
			bmp.LoadBitmap(IDB_BITMAP4);
			bmp.GetObject(sizeof(BITMAP),&bit);
			cMemdc.CreateCompatibleDC(&cdc);
			cMemdc.SelectObject(&bmp);
			for(int posx=10,posy=125;posx<=580;posx++)
			{

			cdc.BitBlt(posx,posy,bit.bmWidth,bit.bmHeight,&cMemdc,0,0,SRCCOPY);
			Sleep(7);
			}

			return 0;
	}
UINT Thread5(LPVOID lp)
	{
			CBitmap bmp;
			BITMAP bit;
			CDC cMemdc;
			CDC *dc;
			dc=CDC::FromHandle((HDC)LOWORD(lp));
			int col;
			
			col=HIWORD(lp);

			CClientDC cdc(AfxGetApp()->m_pMainWnd);
			bmp.LoadBitmap(IDB_BITMAP5);
			bmp.GetObject(sizeof(BITMAP),&bit);
			cMemdc.CreateCompatibleDC(&cdc);
			cMemdc.SelectObject(&bmp);
			for(int posx=10,posy=165;posx<=570;posx++)
			{

			cdc.BitBlt(posx,posy,bit.bmWidth,bit.bmHeight,&cMemdc,0,0,SRCCOPY);
			Sleep(9);
			}

			return 0;
	}


UINT Thread6(LPVOID lp)
	{
			CBitmap bmp;
			BITMAP bit;
			CDC cMemdc;
			CDC *dc;
			dc=CDC::FromHandle((HDC)LOWORD(lp));
			int col;

			col=HIWORD(lp);

			CClientDC cdc(AfxGetApp()->m_pMainWnd);
			bmp.LoadBitmap(IDB_BITMAP6);
			bmp.GetObject(sizeof(BITMAP),&bit);
			cMemdc.CreateCompatibleDC(&cdc);
			cMemdc.SelectObject(&bmp);
			for(int posx=10,posy=205;posx<=530;posx++)
			{

			cdc.BitBlt(posx,posy,bit.bmWidth,bit.bmHeight,&cMemdc,0,0,SRCCOPY);
			Sleep(4);
			}

			return 0;
	}


UINT Thread7(LPVOID lp)
	{
			CBitmap bmp;
			BITMAP bit;
			CDC cMemdc;
			CDC *dc;
			dc=CDC::FromHandle((HDC)LOWORD(lp));
			int col;

			col=HIWORD(lp);

			CClientDC cdc(AfxGetApp()->m_pMainWnd);
			bmp.LoadBitmap(IDB_BITMAP7);
			bmp.GetObject(sizeof(BITMAP),&bit);
			cMemdc.CreateCompatibleDC(&cdc);
			cMemdc.SelectObject(&bmp);
			for(int posx=10,posy=245;posx<=540;posx++)
			{

			cdc.BitBlt(posx,posy,bit.bmWidth,bit.bmHeight,&cMemdc,0,0,SRCCOPY);
			Sleep(3);
			}

			return 0;
	}

UINT Thread8(LPVOID lp)
	{
			CBitmap bmp;
			BITMAP bit;
			CDC cMemdc;
			CDC *dc;
			dc=CDC::FromHandle((HDC)LOWORD(lp));
			int col;

			col=HIWORD(lp);

			CClientDC cdc(AfxGetApp()->m_pMainWnd);
			bmp.LoadBitmap(IDB_BITMAP8);
			bmp.GetObject(sizeof(BITMAP),&bit);
			cMemdc.CreateCompatibleDC(&cdc);
			cMemdc.SelectObject(&bmp);
			for(int posx=10,posy=300;posx<=500;posx++)
			{

			cdc.BitBlt(posx,posy,bit.bmWidth,bit.bmHeight,&cMemdc,0,0,SRCCOPY);
			Sleep(8);
			}

			return 0;
	}


UINT Thread9(LPVOID lp)
	{
			CBitmap bmp;
			BITMAP bit;
			CDC cMemdc;
			CDC *dc;
			dc=CDC::FromHandle((HDC)LOWORD(lp));
			int col;

			col=HIWORD(lp);

			CClientDC cdc(AfxGetApp()->m_pMainWnd);
			bmp.LoadBitmap(IDB_BITMAP9);
			bmp.GetObject(sizeof(BITMAP),&bit);
			cMemdc.CreateCompatibleDC(&cdc);
			cMemdc.SelectObject(&bmp);
			for(int posx=10,posy=340;posx<=500;posx++)
			{

			cdc.BitBlt(posx,posy,bit.bmWidth,bit.bmHeight,&cMemdc,0,0,SRCCOPY);
			Sleep(10);
			}

			return 0;
	}


UINT Thread10(LPVOID lp)
{
			CBitmap bmp;
			BITMAP bit;
			CDC cMemdc;
			CDC *dc;
			dc=CDC::FromHandle((HDC)LOWORD(lp));
			int col;

			col=HIWORD(lp);

			CClientDC cdc(AfxGetApp()->m_pMainWnd);
			bmp.LoadBitmap(IDB_BITMAP11);
			bmp.GetObject(sizeof(BITMAP),&bit);
			cMemdc.CreateCompatibleDC(&cdc);
			cMemdc.SelectObject(&bmp);
			
			for(int posx=30 , posy=450;posx<=600;posx++)
			{


			cdc.BitBlt(posx,posy,bit.bmWidth,bit.bmHeight,&cMemdc,0,0,SRCCOPY);
			Sleep(12);
			}

			return 0;
		}


CMenu cm;
class MyWindow:public CFrameWnd
{
public:
MyWindow()
{	
	Create(0,"Threads of MFC");
	cm.LoadMenu(IDR_MENU1);
	SetMenu(&cm);

}
void q()
{
	PostQuitMessage(0);
}

void Threads()
{
	AfxMessageBox("Starting..........");
}

DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(MyWindow,CFrameWnd)
ON_COMMAND(ID_Q,q)
END_MESSAGE_MAP()


class MyWin:public CWinApp
{
public:
	BOOL InitInstance()
	{
		
		MyWindow *x;
		x=new MyWindow;
		m_pMainWnd=x;
		//创建并启动9名运动员线程
		pThread1=AfxBeginThread(Thread1,x);
		pThread2=AfxBeginThread(Thread2,x);
		pThread3=AfxBeginThread(Thread3,x);
		pThread4=AfxBeginThread(Thread4,x);
		pThread5=AfxBeginThread(Thread5,x);
		pThread6=AfxBeginThread(Thread6,x);
		pThread7=AfxBeginThread(Thread7,x);
		pThread8=AfxBeginThread(Thread8,x);
		pThread9=AfxBeginThread(Thread9,x);
		//创建并启动裁判员线程
		pThread10=AfxBeginThread(Thread10,x);	
		
		x->ShowWindow(SW_SHOWMAXIMIZED);
		return 1;
	}

};
MyWin App;

