// MainWndDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DLLProc.h"
#include "MainWndDlg.h"
#include "afxdialogex.h"


// CMainWndDlg 对话框

IMPLEMENT_DYNAMIC(CMainWndDlg, CDialogEx)

CMainWndDlg::CMainWndDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainWndDlg::IDD, pParent)
{
	p_handleDataExchange = new CHandleDataExChange(getGamehwnd());
	//然后再挂载到主线程中
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


// CMainWndDlg 消息处理程序


void CMainWndDlg::OnBnClickedBtntest()
{
	// TODO: 测试按钮的消息处理函数
	p_handleDataExchange->SendMessageToCallBack(NULL);
}
