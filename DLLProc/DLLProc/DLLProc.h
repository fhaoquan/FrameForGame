// DLLProc.h : DLLProc DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


//������������
class CMainWndDlg;

//�̻߳ص���������
DWORD WINAPI CreateMainWnd(LPARAM lpData);

// CDLLProcApp
// �йش���ʵ�ֵ���Ϣ������� DLLProc.cpp
//

class CDLLProcApp : public CWinApp
{
public:
	CDLLProcApp();

// ��д
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()


private:
	//CMainWndDlg* p_mainDlg; //������
};
