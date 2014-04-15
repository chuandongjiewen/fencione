#pragma once
#include "afxwin.h"
#include "Hmm.h"
#include "resource.h"


// CHMMSeg 对话框

class CHMMSegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHMMSegDlg)

public:
	CHMMSegDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHMMSegDlg();

// 对话框数据
	enum { IDD = IDD_HMM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CHmm *seg;

public:
	CEdit outputEdit;
	CEdit inputEdit;
	afx_msg void OnBnClickedProcess();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBegein();
	afx_msg void OnBnClickedloadDict();
};
