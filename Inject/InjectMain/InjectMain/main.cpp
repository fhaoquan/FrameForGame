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
	// ��ȡDLL·��
	CHAR dllPath[MAX_PATH] = { 0 };
	CHAR InjectdllPath[MAX_PATH] = { 0 };
	GetExePath(dllPath);
	strcat_s(dllPath, "\\");
	memcpy(InjectdllPath, dllPath, MAX_PATH);
	strcat_s(dllPath, "IMEInjectDLL.dll");
	strcat_s(InjectdllPath, "dll.dll");

	// ����ԭʼ���̲���
	SystemParametersInfo(SPI_GETDEFAULTINPUTLANG, 0, &oldInputHandle, 0);
	// �����ļ���Ŀ¼
	CopyFile(dllPath, "C:\\WINDOWS\\SYSTEM32\\IMEInjectDLL.ime", FALSE);
	CopyFile(InjectdllPath, "C:\\WINDOWS\\SYSTEM32\\Game.dll", FALSE);

	// �������뷨
	InputHandle = ImmInstallIME("C:\\WINDOWS\\SYSTEM32\\IMEInjectDLL.ime", "����v1.0");
	// �ж����뷨����Ƿ���Ч
	if (!ImmIsIME(InputHandle))
	{
		printf("���뷨����ʧ�ܣ�");
	}

	//���������뷨���̲���
	ActivateKeyboardLayout(InputHandle, 0);
	//��ȡ���뷨���̲������ƣ��������ɾ��ע���
	GetKeyboardLayoutName(ImeSymbol);

	// ��ȡ���ھ��
	hWnd = FindWindow(NULL, "1.txt - ���±�");

	// ����ָ���������뷨
	if (InputHandle != NULL)
	{
		PostMessage(hWnd, WM_INPUTLANGCHANGEREQUEST, 0x1, (LPARAM)InputHandle);
	}

	// �ȴ�һ�£�����
	Sleep(3000);

	// ��ԭ���̲���
	SystemParametersInfo(SPI_SETDEFAULTINPUTLANG, 0, &oldInputHandle, SPIF_SENDWININICHANGE);

	// ���㴰�ڵ����뷨����ȥ�������صĻ���������ж�ز���
	do
	{
		hTopWnd = FindWindowEx(NULL, hTopWnd, NULL, NULL);
		if (hTopWnd != NULL)
		{
			PostMessage(hTopWnd, WM_INPUTLANGCHANGEREQUEST, 0x1, (LPARAM)&oldInputHandle);
		}
	} while (hTopWnd == NULL);

	// ж�����뷨
	if (InputHandle != NULL)
	{
		UnloadKeyboardLayout(InputHandle);
	}

	// ɾ��ע�����Ϣ
	ImedeleteReg();

	// ɾ�����뷨�ļ�
	DeleteFile("C:\\WINDOWS\\SYSTEM32\\IMEInjectDLL.ime");
	system("pause");
	return 0;
}

void ImedeleteReg()
{
	HKEY phkResult;
	int i = 0;
	TCHAR ValueName[255];  //�洢�õ��ļ�ֵ��
	TCHAR lpData[255];     //�洢�õ��ļ�ֵ����
	DWORD lenValue = 255;  //�洢��ֵ�����ݳ���
	DWORD lenData = 255;   //�洢��ֵ�����ݳ���

	//��ע�����Ŀ����ȡ���
	RegOpenKey(HKEY_CURRENT_USER, "Keyboard Layout\\Preload", &phkResult);
	//ö��ע�����Ŀ
	while (RegEnumValue(phkResult, i, ValueName, &lenValue, NULL, NULL, (LPBYTE)lpData, &lenData) != ERROR_NO_MORE_ITEMS)
	{
		if (lenData != 0)
		{
			if (strcmp(ImeSymbol, lpData) == 0)
			{
				//ɾ����Ŀ��ֵ
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