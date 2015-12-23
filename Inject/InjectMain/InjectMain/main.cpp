#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        101
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
#include <stdio.h>
#include <Windows.h>
#include <Imm.h>
#pragma comment(lib,"IMM32.lib")

void ImedeleteReg();

TCHAR ImeSymbol[255];
HKL InputHandle = NULL;
HWND hWnd = NULL;
HKL oldInputHandle = NULL;
HWND hTopWnd = NULL;
HANDLE hModule = NULL;
void GetExePath(CHAR* pExePath);

int main()
{
	// 获取DLL路径
	CHAR dllPath[MAX_PATH] = { 0 };
	CHAR InjectdllPath[MAX_PATH] = { 0 };
	GetExePath(dllPath);
	strcat_s(dllPath, "\\");
	memcpy(InjectdllPath, dllPath, MAX_PATH);
	strcat_s(dllPath, "IMEInjectDLL.dll");
	strcat_s(InjectdllPath, "dll.dll");

	// 保存原始键盘布局
	SystemParametersInfo(SPI_GETDEFAULTINPUTLANG, 0, &oldInputHandle, 0);
	// 复制文件到目录
	CopyFile(dllPath, "C:\\WINDOWS\\SYSTEM32\\IMEInjectDLL.ime", FALSE);
	CopyFile(InjectdllPath, "C:\\WINDOWS\\SYSTEM32\\Game.dll", FALSE);

	// 加载输入法
	InputHandle = ImmInstallIME("C:\\WINDOWS\\SYSTEM32\\IMEInjectDLL.ime", "三号v1.0");
	// 判断输入法句柄是否有效
	if (!ImmIsIME(InputHandle))
	{
		printf("输入法加载失败！");
	}

	//激活新输入法键盘布局
	ActivateKeyboardLayout(InputHandle, 0);
	//获取输入法键盘布局名称，用于最后删除注册表
	GetKeyboardLayoutName(ImeSymbol);

	// 获取窗口句柄
	hWnd = FindWindow(NULL, "1.txt - 记事本");

	// 激活指定窗口输入法
	if (InputHandle != NULL)
	{
		PostMessage(hWnd, WM_INPUTLANGCHANGEREQUEST, 0x1, (LPARAM)InputHandle);
	}

	// 等待一下，加载
	Sleep(3000);

	// 还原键盘布局
	SystemParametersInfo(SPI_SETDEFAULTINPUTLANG, 0, &oldInputHandle, SPIF_SENDWININICHANGE);

	// 顶层窗口的输入法换回去，不换回的话可能下面卸载不掉
	do
	{
		hTopWnd = FindWindowEx(NULL, hTopWnd, NULL, NULL);
		if (hTopWnd != NULL)
		{
			PostMessage(hTopWnd, WM_INPUTLANGCHANGEREQUEST, 0x1, (LPARAM)&oldInputHandle);
		}
	} while (hTopWnd == NULL);

	// 卸载输入法
	if (InputHandle != NULL)
	{
		UnloadKeyboardLayout(InputHandle);
	}

	// 删除注册表信息
	ImedeleteReg();

	// 删除输入法文件
	DeleteFile("C:\\WINDOWS\\SYSTEM32\\IMEInjectDLL.ime");
	system("pause");
	return 0;
}

void ImedeleteReg()
{
	HKEY phkResult;
	int i = 0;
	TCHAR ValueName[255];  //存储得到的键值名
	TCHAR lpData[255];     //存储得到的键值数据
	DWORD lenValue = 255;  //存储键值的数据长度
	DWORD lenData = 255;   //存储键值的数据长度

	//打开注册表项目，获取句柄
	RegOpenKey(HKEY_CURRENT_USER, "Keyboard Layout\\Preload", &phkResult);
	//枚举注册表项目
	while (RegEnumValue(phkResult, i, ValueName, &lenValue, NULL, NULL, (LPBYTE)lpData, &lenData) != ERROR_NO_MORE_ITEMS)
	{
		if (lenData != 0)
		{
			if (strcmp(ImeSymbol, lpData) == 0)
			{
				//删除项目数值
				RegDeleteValue(phkResult, ValueName);
				break;
			}
		}

		memset(lpData, 0, 255);
		memset(ValueName, 0, 255);
		lenValue = 255;
		lenData = 255;
		i++;
	}
}


void GetExePath(char* pExePath)
{
	int  pathlen = GetModuleFileName(NULL, pExePath, MAX_PATH);
	while (1)
	{
		if (pExePath[pathlen--] == '\\')
			break;
	}
	pExePath[++pathlen] = 0;
}