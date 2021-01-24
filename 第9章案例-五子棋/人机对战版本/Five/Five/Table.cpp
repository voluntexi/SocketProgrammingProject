#include "stdafx.h"
#include "Five.h"
#include "Table.h"
#include "Message.h"
#include "Resource.h"

// ���캯������ʼ�����������Լ�ͼ������
CTable::CTable()
{
    // ��ʼ���������
    TCHAR str[10];
    CFiveApp *pApp = (CFiveApp *)AfxGetApp();
    ::GetPrivateProfileString( _T("Options"), _T("Name"), _T("���"), str, 15, pApp->m_szIni );
    m_strMe = str;
    // ��ʼ��ͼ���б�
    m_iml.Create( 24, 24, ILC_COLOR24 | ILC_MASK, 0, 2 );
    // ����ڡ�����������λͼ
    CBitmap bmpBlack, bmpWhite;
    bmpBlack.LoadBitmap( IDB_BMP_BLACK );
    m_iml.Add( &bmpBlack, 0xff00ff );
    bmpWhite.LoadBitmap( IDB_BMP_WHITE );
    m_iml.Add( &bmpWhite, 0xff00ff );
    // ��ʼ����Ϸģʽ
    m_pGame = NULL;
}

// �����������ͷ�m_pGameָ��
CTable::~CTable()
{
    // д���������
    CFiveApp *pApp = (CFiveApp *)AfxGetApp();
    ::WritePrivateProfileString( _T("Options"), _T("Name"), m_strMe, pApp->m_szIni );
    // д��ս��ͳ��
    TCHAR str[10];
    wsprintf( str, _T("%d"), pApp->m_nWin );
    ::WritePrivateProfileString( _T("Stats"), _T("Win"), str, pApp->m_szIni );
    wsprintf( str, _T("%d"), pApp->m_nDraw );
    ::WritePrivateProfileString( _T("Stats"), _T("Draw"), str, pApp->m_szIni );
    wsprintf( str, _T("%d"), pApp->m_nLost );
    ::WritePrivateProfileString( _T("Stats"), _T("Lost"), str, pApp->m_szIni );
    if ( NULL != m_pGame )
        delete m_pGame;
}

// ��ָ���������괦����ָ����ɫ������
void CTable::Draw( int x, int y, int color )
{
    POINT pt;
    pt.x = 54 + 25 * x;
    pt.y = 101 + 25 * y;
    CDC *pDC = GetDC();
    CPen pen;
    pen.CreatePen( PS_SOLID, 1, 0xff );
    pDC->SelectObject( &pen );
    pDC->SetROP2( R2_NOTXORPEN );
    m_iml.Draw( pDC, color, pt, ILD_TRANSPARENT );
    STEP step;
    // ����R2_NOTXORPEN������ǰ�����ľ���
    if ( !m_pGame->m_StepList.empty() )
    {
        // ��ȡ���һ����
        step = *( m_pGame->m_StepList.begin() );
        pDC->MoveTo( 54 + 25 * step.x, 101 + 25 * step.y );
        pDC->LineTo( 79 + 25 * step.x, 101 + 25 * step.y );
        pDC->LineTo( 79 + 25 * step.x, 126 + 25 * step.y );
        pDC->LineTo( 54 + 25 * step.x, 126 + 25 * step.y );
        pDC->LineTo( 54 + 25 * step.x, 101 + 25 * step.y );
    }
    // ������������������ݣ����µľ���
    step.color = color;
    step.x = x;
    step.y = y;
    m_pGame->m_StepList.push_front( step );
    pDC->MoveTo( 54 + 25 * step.x, 101+ 25 * step.y );
    pDC->LineTo( 79 + 25 * step.x, 101 + 25 * step.y );
    pDC->LineTo( 79 + 25 * step.x, 126 + 25 * step.y );
    pDC->LineTo( 54 + 25 * step.x, 126 + 25 * step.y );
    pDC->LineTo( 54 + 25 * step.x, 101 + 25 * step.y );
    ReleaseDC( pDC );
}

// �������
void CTable::Clear( BOOL bWait )
{
    int x, y;
    for ( y = 0; y < 15; y++ )
    {
        for ( x = 0; x < 15; x++ )
        {
            m_data[x][y] = -1;
        }
    }
    // ���õȴ���־
    m_bWait = bWait;
    Invalidate();
    // ɾ����Ϸ
    if ( m_pGame != NULL )
    {
        delete m_pGame;
        m_pGame = NULL;
    }
}

// ���������ɫ
void CTable::SetColor( int color )
{
    m_color = color;
}

// ��ȡ�����ɫ
int CTable::GetColor() const
{
    return m_color;
}

// ���õȴ���־��������ǰ�ĵȴ���־
BOOL CTable::SetWait( BOOL bWait )
{
    m_bOldWait = m_bWait;
    m_bWait = bWait;
    return m_bOldWait;
}

// �����������ݣ�����������
void CTable::SetData( int x, int y, int color )
{
    m_data[x][y] = color;
    Draw( x, y, color );
}

// �ж�ָ����ɫ�Ƿ�ʤ��
BOOL CTable::Win( int color ) const
{
    int x, y;
    // �жϺ���
    for ( y = 0; y < 15; y++ )
    {
        for ( x = 0; x < 11; x++ )
        {
            if ( color == m_data[x][y] && color == m_data[x + 1][y] &&
                color == m_data[x + 2][y] && color == m_data[x + 3][y] &&
                color == m_data[x + 4][y] )
            {
                return TRUE;
            }
        }
    }
    // �ж�����
    for ( y = 0; y < 11; y++ )
    {
        for ( x = 0; x < 15; x++ )
        {
            if ( color == m_data[x][y] && color == m_data[x][y + 1] &&
                color == m_data[x][y + 2] && color == m_data[x][y + 3] &&
                color == m_data[x][y + 4] )
            {
                return TRUE;
            }
        }
    }
    // �жϡ�\������
    for ( y = 0; y < 11; y++ )
    {
        for ( x = 0; x < 11; x++ )
        {
            if ( color == m_data[x][y] && color == m_data[x + 1][y + 1] &&
                color == m_data[x + 2][y + 2] && color == m_data[x + 3][y + 3] &&
                color == m_data[x + 4][y + 4] )
            {
                return TRUE;
            }
        }
    }
    // �жϡ�/������
    for ( y = 0; y < 11; y++ )
    {
        for ( x = 4; x < 15; x++ )
        {
            if ( color == m_data[x][y] && color == m_data[x - 1][y + 1] &&
                color == m_data[x - 2][y + 2] && color == m_data[x - 3][y + 3] &&
                color == m_data[x - 4][y + 4] )
            {
                return TRUE;
            }
        }
    }
    // ������ʤ������
    return FALSE;
}

// ������Ϸģʽ�������ս�����ô˺���
void CTable::SetGameMode( int nGameMode )
{
       m_pGame = new COneGame( this );//�����˻���Ϸ����
       m_pGame->Init();//�˻���սģʽ��ʼ��
}

// ����
void CTable::Back()
{
    m_pGame->Back();
}

// �����������Ӻ�Ĺ���
void CTable::StepOver()
{
    // �жϼ�����Ƿ�ʤ��
    if ( Win( 1 - m_color ) )
    {
        CFiveApp *pApp = (CFiveApp *)AfxGetApp();
        pApp->m_nLost++;
        CDialog *pDlg = (CDialog *)GetParent();
        PlaySound( MAKEINTRESOURCE( IDR_WAVE_LOST ), NULL, SND_RESOURCE | SND_SYNC );
        pDlg->MessageBox( _T("�����ˣ�������Ҫ���ģ�ʧ���˳ɹ�֮ĸŶ��"), _T("ʧ��"), MB_ICONINFORMATION );
        pDlg->GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
        return;
    }
    m_bWait = FALSE;
}

// �������ӣ������ս�����ô˺���
void CTable::Accept( int nGameMode )
{
    SetColor( 0 );//���õ������巽������ɫ
    Clear( FALSE );//������̣��ȴ���־m_bWait=FALSE
    SetGameMode( nGameMode );//������ϷģʽΪ1
}

// �������ԶԷ������ݣ������ս���Դ˺�����չ������������Ϣ
void CTable::Receive()
{
    MSGSTRUCT msgRecv;
    m_pGame->ReceiveMsg( &msgRecv );
    // �Ը�����Ϣ�ֱ���д���
    switch ( msgRecv.uMsg )
    {
    case MSG_DROPDOWN:
        {
            PlaySound( MAKEINTRESOURCE( IDR_WAVE_PUT ), NULL, SND_RESOURCE | SND_SYNC );
            SetData( msgRecv.x, msgRecv.y, msgRecv.color );
            // ����1�����ܻ���
            GetParent()->GetDlgItem( IDC_BTN_BACK )->EnableWindow( m_pGame->m_StepList.size() > 1 );
            StepOver();
        }
        break;
	//�����ս���ڴ˴�����������Ϣ	
	}
}
// ��Ϣӳ���
BEGIN_MESSAGE_MAP( CTable, CWnd )
	//{{AFX_MSG_MAP(CTable)
    ON_WM_PAINT()
    ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ����WM_PAINT��Ϣ
void CTable::OnPaint()
{
	CPaintDC dc( this );
    // װ������
    CBitmap bmp;
    CPen pen;
    bmp.LoadBitmap(IDB_BMP_TABLE);
	
	CDC dcMem;
    dcMem.CreateCompatibleDC( &dc );
	
    pen.CreatePen( PS_SOLID, 1, 0xff );
    dcMem.SelectObject( &bmp );
    dcMem.SelectObject( &pen );
    dcMem.SetROP2( R2_NOTXORPEN );
    // �����������ݻ�������
   int x, y;
    POINT pt;
    for ( y = 0; y < 15; y++ )
    {
        for ( x = 0; x < 15; x++ )
        {
            if ( -1 != m_data[x][y] )
            {
                pt.x = 54 + 25 * x;
                pt.y = 101 + 25 * y;
                m_iml.Draw( &dcMem, m_data[x][y], pt, ILD_TRANSPARENT );
            }
        }
    }
    // ����������ӵ�ָʾ����
    if ( NULL != m_pGame && !m_pGame->m_StepList.empty() )
    {
        STEP step = *( m_pGame->m_StepList.begin() );
        dcMem.MoveTo( 54 + 25 * step.x, 101 + 25 * step.y );
        dcMem.LineTo( 79 + 25 * step.x, 101 + 25 * step.y );
        dcMem.LineTo( 79 + 25 * step.x, 126 + 25 * step.y );
        dcMem.LineTo( 54 + 25 * step.x, 126 + 25 * step.y );
        dcMem.LineTo( 54 + 25 * step.x, 101 + 25 * step.y );
    }
    // ��ɻ���
   dc.BitBlt( 0, 0, 480, 509, &dcMem,0, 0,SRCCOPY);
    dcMem.SelectObject(bmp);
}

// �������������Ϣ��Ϊ�������֮��
void CTable::OnLButtonUp( UINT nFlags, CPoint point )
{
    STEP stepPut;
    if ( m_bWait )
    {
        MessageBeep( MB_OK );
        return;
    }
    int x, y;
    x = ( point.x - 54 ) / 25;
    y = ( point.y - 101 ) / 25;
    // �����(0, 0)��(14, 14)��Χ�ڣ��Ҹ�����û�����ӣ��������ڴˣ����������沢�˳�����
    if ( x < 0 || x > 14 || y < 0 || y > 14 || m_data[x][y] != -1 )
    {
        MessageBeep( MB_OK );
        return;
    }
    else
    {
        // ���λ�úϷ���������
        SetData( x, y, m_color );
        stepPut.color = m_color;
        stepPut.x = x;
        stepPut.y = y;
        // ����1�����ܻ���
        GetParent()->GetDlgItem( IDC_BTN_BACK )->EnableWindow( m_pGame->m_StepList.size() > 1 );
    }
    // �ж�ʤ�������
    if ( Win( m_color ) )
    {
        CFiveApp *pApp = (CFiveApp *)AfxGetApp();
        pApp->m_nWin++;
        m_pGame->Win( stepPut );
        CDialog *pDlg = (CDialog *)GetParent();
        PlaySound( MAKEINTRESOURCE( IDR_WAVE_WIN ), NULL, SND_SYNC | SND_RESOURCE );
        pDlg->MessageBox( _T("��ϲ���������ʤ����"), _T("ʤ��"), MB_ICONINFORMATION );
   
        pDlg->GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
		
        m_bWait = TRUE;
        return;
    }
    else
    {
        // ��ʼ�ȴ�
        m_bWait = TRUE;
        // ����������Ϣ
        PlaySound( MAKEINTRESOURCE( IDR_WAVE_PUT ), NULL, SND_SYNC | SND_RESOURCE );
        m_pGame->SendStep( stepPut );
    }
}

// ����������ǰ�ĵȴ���־
void CTable::RestoreWait()
{
    SetWait( m_bOldWait );
}
