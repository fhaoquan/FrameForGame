// DLLProc.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "DLLProc.h"
#include "MainWndDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMainWndDlg* p_mainDlg; //������
//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CDLLProcApp

BEGIN_MESSAGE_MAP(CDLLProcApp, CWinApp)
END_MESSAGE_MAP()





// CDLLProcApp ����

CDLLProcApp::CDLLProcApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDLLProcApp ����

CDLLProcApp theApp;


// CDLLProcApp ��ʼ��
BOOL CDLLProcApp::InitInstance()
{
	CWinApp::InitInstance();

	::CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(CreateMainWnd), NULL, NULL, NULL);

	return TRUE;
}


//����������
DWORD WINAPI CreateMainWnd(LPARAM lpData){
	p_mainDlg = new CMainWndDlg;
	p_mainDlg->DoModal();
	delete p_mainDlg;
	FreeLibraryAndExitThread(theApp.m_hInstance, 1);
	return TRUE;
}