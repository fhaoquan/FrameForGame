// MainWndDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DLLProc.h"
#include "MainWndDlg.h"
#include "afxdialogex.h"


// CMainWndDlg �Ի���

IMPLEMENT_DYNAMIC(CMainWndDlg, CDialogEx)

CMainWndDlg::CMainWndDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainWndDlg::IDD, pParent)
{
	p_handleDataExchange = new CHandleDataExChange(getGamehwnd());
	//Ȼ���ٹ��ص����߳���
	p_handleDataExchange->HookMainThread();
}

CMainWndDlg::~CMainWndDlg()
{
	p_handleDataExchange->UnHookMainThread();
	delete p_handleDataExchange;
}

void CMainWndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainWndDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTNTEST, &CMainWndDlg::OnBnClickedBtntest)
END_MESSAGE_MAP()


// CMainWndDlg ��Ϣ�������


void CMainWndDlg::OnBnClickedBtntest()
{
	// TODO: ���԰�ť����Ϣ������
	p_handleDataExchange->SendMessageToCallBack(NULL);
}
