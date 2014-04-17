#pragma once
#include "afxwin.h"
#include "Hmm.h"
#include "CstatisticSeg.h"
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
	CHmm *hmm;
	CstatisticSeg *seg;

public:
	CEdit outputEdit;
	CEdit inputEdit;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBegein();
	// //m估计的m默认为10
	CEdit est_m_edit;
	// //m估计的p默认为0.000001
	CEdit est_p_edit;
	CStatic detail_Static;
};
