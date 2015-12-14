#pragma once

#include "HandleDataExChange.h"
#include "utils.h"

// CMainWndDlg 对话框

class CMainWndDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainWndDlg)

public:
	CMainWndDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainWndDlg();

// 对话框数据
	enum { IDD = IDD_DLGMAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


private:
	CHandleDataExChange *p_handleDataExchange;
public:
	afx_msg void OnBnClickedBtntest();
};
