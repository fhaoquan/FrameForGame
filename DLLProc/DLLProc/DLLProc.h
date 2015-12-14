// DLLProc.h : DLLProc DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


//主窗口类声明
class CMainWndDlg;

//线程回调函数声明
DWORD WINAPI CreateMainWnd(LPARAM lpData);

// CDLLProcApp
// 有关此类实现的信息，请参阅 DLLProc.cpp
//

class CDLLProcApp : public CWinApp
{
public:
	CDLLProcApp();

// 重写
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()


private:
	//CMainWndDlg* p_mainDlg; //主窗口
};
