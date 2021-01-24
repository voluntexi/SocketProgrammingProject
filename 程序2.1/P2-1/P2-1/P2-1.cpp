#include <windows.h>

INT WINAPI wWinMain(HINSTANCE hInst,
			HINSTANCE hPrevInst,
			LPWSTR lpCmdLine,
			INT nShowCmd)

{
	int nResult=MessageBox(NULL,
			"这个消息框包含了终止、重试、忽略按钮和一个错误图标",
			"消息框用法演示!",
			MB_ICONERROR|MB_ABORTRETRYIGNORE);
	
	switch(nResult)
	{
		case IDABORT:
			// 点击了“终止”按钮
			break;
		case IDRETRY:
			// 点击了“重试”按钮
			break;
		case IDIGNORE:
			// 点击了“忽略”按钮
			break;
	}

	return 0;
}
