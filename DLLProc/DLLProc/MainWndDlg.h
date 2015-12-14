#pragma once

#include "HandleDataExChange.h"
#include "utils.h"

// CMainWndDlg �Ի���

class CMainWndDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainWndDlg)

public:
	CMainWndDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainWndDlg();

// �Ի�������
	enum { IDD = IDD_DLGMAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


private:
	CHandleDataExChange *p_handleDataExchange;
public:
	afx_msg void OnBnClickedBtntest();
};
