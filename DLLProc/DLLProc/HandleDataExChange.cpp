#include "stdafx.h"
#include "HandleDataExChange.h"
#include <Windows.h>
#include "utils.h"


//ȫ�ֱ���
HHOOK g_hhkGame = NULL;
HWND g_hwnd = NULL;
const DWORD  MyMsgCode = RegisterWindowMessageA("MyMsgCode"); //ע����Ϣ  

////�ص�����  
static LRESULT CALLBACK GameWndProc(int nCode,
	WPARAM wParam,
	LPARAM lParam
	);

CHandleDataExChange::CHandleDataExChange(HWND hwnd){
	m_hwnd = hwnd;
	g_hwnd = hwnd;
	m_hhkGame = NULL;
}

CHandleDataExChange::~CHandleDataExChange()
{

}
DWORD CHandleDataExChange::HookMainThread()  //���ص����߳�
{
	DWORD ndThreadID = GetWindowThreadProcessId(m_hwnd, NULL);
	if (ndThreadID != 0){
		m_hhkGame = SetWindowsHookEx(WH_CALLWNDPROC, GameWndProc, NULL, ndThreadID);
		g_hhkGame = m_hhkGame;
	}
	return 1;
}
DWORD CHandleDataExChange::UnHookMainThread() //���߳�ж��
{
	UnhookWindowsHookEx(m_hhkGame);
	return 1;
}


LRESULT CALLBACK GameWndProc(int nCode,
	WPARAM wParam,
	LPARAM lParam
	){

	//���ص����߳��еĻص�����
	CWPSTRUCT *lpArg = (CWPSTRUCT*)lParam; //���ݽṹ��������ȡlparam�����е�����  

	if (nCode == HC_ACTION)
	{
		if (lpArg->hwnd == g_hwnd && lpArg->message == MyMsgCode)
		{
			//�ж�ִ�е����Լ�����Ϣ�����Ҿ���ǵ�ǰ��Ϸ���ڵľ��
			switch (lpArg->wParam) //����Ϣ���ͽ��й���
			{

			//lpArg->lParam  ����Ĳ���
			case MSG_TEST:
				debugMessageOutput("%s %d", "Test............", 5);
				break;
			default:
				break;
			}

		}
	}


	return CallNextHookEx(g_hhkGame, nCode, wParam, lParam);
}


DWORD CHandleDataExChange::SendMessageToCallBack(char* szpName){
	//������Ϣ
	::SendMessageA(m_hwnd, MyMsgCode, MSGTYPES::MSG_TEST, (LPARAM)szpName);
	return 1;
}