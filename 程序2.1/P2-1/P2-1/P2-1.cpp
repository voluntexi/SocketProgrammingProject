#include <windows.h>

INT WINAPI wWinMain(HINSTANCE hInst,
			HINSTANCE hPrevInst,
			LPWSTR lpCmdLine,
			INT nShowCmd)

{
	int nResult=MessageBox(NULL,
			"�����Ϣ���������ֹ�����ԡ����԰�ť��һ������ͼ��",
			"��Ϣ���÷���ʾ!",
			MB_ICONERROR|MB_ABORTRETRYIGNORE);
	
	switch(nResult)
	{
		case IDABORT:
			// ����ˡ���ֹ����ť
			break;
		case IDRETRY:
			// ����ˡ����ԡ���ť
			break;
		case IDIGNORE:
			// ����ˡ����ԡ���ť
			break;
	}

	return 0;
}
