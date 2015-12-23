// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Windows.h>
#include <process.h>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	CHAR FileName[MAX_PATH + 1] = { 0 };
	DWORD dwLen = 0;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		dwLen = GetModuleFileName(hModule, FileName, MAX_PATH);
		while (1)
		{
			if (FileName[dwLen--] == '\\')
				break;
		}

		FileName[++dwLen] = 0;
		strcat_s(FileName, "\\");
		strcat_s(FileName, "Game.dll");
		LoadLibrary(FileName);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

