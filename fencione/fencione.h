
// fencione.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "fencioneDlg.h"
#include "CstatisticFenciDialog.h"


// CfencioneApp:
// �йش����ʵ�֣������ fencione.cpp
//

class CfencioneApp : public CWinApp
{
public:
	CfencioneApp();

private:
	CfencioneDlg *fencioneDlg;
	CstatisticFenciDialog *statisticDlg;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnHmm();
	afx_msg void Onstatistic();
	afx_msg void Onmachine();
};

extern CfencioneApp theApp;