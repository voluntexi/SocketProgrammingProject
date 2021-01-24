//CTable类定义
#pragma once
#include "Game.h"
#include "FiveSocket.h" //手动添加
class CTable : public CWnd
{
    CImageList m_iml; // 棋子图像
    int m_color; // 玩家颜色
    BOOL m_bWait; // 等待标志
    void Draw(int x, int y, int color);
    CGame *m_pGame; // 游戏基类指针
public:
	//--以下九项是网络对战增加部分--
	CFiveSocket m_serverSocket;//服务器套接字
    CFiveSocket m_clientSocket;//客户机套接字
	// 是否连接网络（客户端使用）
    BOOL m_bConnected;
	void PlayAgain();
	void GiveUp();
	void Chat( LPCTSTR lpszMsg );
	void DrawGame();
    void Connect( int nGameMode );
	void SetMenuState( BOOL bEnable );
	//-----------------------------------
    
    void RestoreWait();
    BOOL m_bOldWait; // 先前的等待标志
    CString m_strMe;// 玩家名字
    CString m_strAgainst;// 对方名字
    int m_data[15][15]; // 棋盘数据
    CTable();
    ~CTable();
    void Clear( BOOL bWait );
    void SetColor(int color);
    int GetColor() const;
    BOOL SetWait( BOOL bWait );
    void SetData( int x, int y, int color );
    BOOL Win(int color) const;
    void SetGameMode( int nGameMode );
    void Back();
    void StepOver();
    void Accept( int nGameMode );
    void Receive();
protected:
    afx_msg void OnPaint();
    afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
    DECLARE_MESSAGE_MAP()
};
