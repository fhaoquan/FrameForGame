#pragma once
#include <Windows.h>
#include <iostream>
//�����̵߳����߳��У���ֹ���������ݷ��ʳ�ͻ
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
	DWORD HookMainThread();   //���ص����߳�
	DWORD UnHookMainThread(); //���߳�ж��


	//�������Ϣ�ӿ�
	DWORD SendMessageToCallBack(char* szpName);  //���ڲ��Ե���Ϣ
private:
	HWND m_hwnd;   //��ǰ���ھ��
	HHOOK m_hhkGame; //��������setwindowsHook�ķ���ֵ
	MSGTYPES msg;
};

