#pragma once
#include "CstatisticSeg.h"
#include "resource.h"
#include "afxwin.h"


// CstatisticFenciDialog 对话框

class CstatisticFenciDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CstatisticFenciDialog)

public:
	CstatisticFenciDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CstatisticFenciDialog();

// 对话框数据
	enum { IDD = IDD_statistic_dialog };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CstatisticSeg *pSeg;
	bool isLoadedDict;

public:
	afx_msg void Onmachine();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedloaddict();
	afx_msg void OnBnClickedstatistic();
	CEdit inputEdit;
	CEdit outputEdit;
	CStatic resultText;
};
