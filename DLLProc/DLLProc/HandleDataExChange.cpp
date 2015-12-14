#include "stdafx.h"
#include "HandleDataExChange.h"
#include <Windows.h>
#include "utils.h"


//全局变量
HHOOK g_hhkGame = NULL;
HWND g_hwnd = NULL;
const DWORD  MyMsgCode = RegisterWindowMessageA("MyMsgCode"); //注册消息  

////回调函数  
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
DWORD CHandleDataExChange::HookMainThread()  //挂载到主线程
{
	DWORD ndThreadID = GetWindowThreadProcessId(m_hwnd, NULL);
	if (ndThreadID != 0){
		m_hhkGame = SetWindowsHookEx(WH_CALLWNDPROC, GameWndProc, NULL, ndThreadID);
		g_hhkGame = m_hhkGame;
	}
	return 1;
}
DWORD CHandleDataExChange::UnHookMainThread() //从线程卸载
{
	UnhookWindowsHookEx(m_hhkGame);
	return 1;
}


LRESULT CALLBACK GameWndProc(int nCode,
	WPARAM wParam,
	LPARAM lParam
	){

	//挂载到主线程中的回调函数
	CWPSTRUCT *lpArg = (CWPSTRUCT*)lParam; //数据结构，用来获取lparam参数中的数据  

	if (nCode == HC_ACTION)
	{
		if (lpArg->hwnd == g_hwnd && lpArg->message == MyMsgCode)
		{
			//判断执行的是自己的消息，并且句柄是当前游戏窗口的句柄
			switch (lpArg->wParam) //对消息类型进行过滤
			{

			//lpArg->lParam  具体的参数
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
	//发送消息
	::SendMessageA(m_hwnd, MyMsgCode, MSGTYPES::MSG_TEST, (LPARAM)szpName);
	return 1;
}