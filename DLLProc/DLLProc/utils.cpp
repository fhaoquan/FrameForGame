#include "stdafx.h"
#include "utils.h"
#include "baseAddr.h"

HWND getGamehwnd(){
	HWND hwnd = NULL;
	__try{
		hwnd = *(HWND*)base_WndHwndAddr;
	}
	__except (1){
		hwnd = NULL;
	}


	return hwnd;
}



void debugMessageOutput(char* szpFormatName, ...){
	//���Ժ���,ֻ����DEBUGģʽ�²Ż���ʾ������Ϣ
#ifdef _DEBUG
	va_list argList;
	char buffer[0x500];
	char szBuffer_Game[0x500] = "Game:";
	va_start(argList, szpFormatName);
	vsprintf_s(buffer, szpFormatName, argList);
	strcat_s(szBuffer_Game, buffer);
	OutputDebugStringA(szBuffer_Game);
	va_end(argList);
#endif

}