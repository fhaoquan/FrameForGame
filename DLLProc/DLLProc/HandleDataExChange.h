#pragma once
#include <Windows.h>
#include <iostream>
//挂载线程到主线程中，防止程序中数据访问冲突
//
using namespace std;


namespace{
	enum MSGTYPES
	{
		MSG_TEST,
	};

}

class CHandleDataExChange
{
public:
	CHandleDataExChange(HWND hwnd);
	~CHandleDataExChange();
	DWORD HookMainThread();   //挂载到主线程
	DWORD UnHookMainThread(); //从线程卸载


	//具体的消息接口
	DWORD SendMessageToCallBack(char* szpName);  //用于测试的消息
private:
	HWND m_hwnd;   //当前窗口句柄
	HHOOK m_hhkGame; //用来保存setwindowsHook的返回值
	MSGTYPES msg;
};

