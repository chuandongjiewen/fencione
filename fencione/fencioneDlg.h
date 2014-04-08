
// fencioneDlg.h : 头文件
//

#pragma once

#include "Segment.h"
#include "afxwin.h"
#include "CstatisticFenciDialog.h"

// CfencioneDlg 对话框
class CfencioneDlg : public CDialogEx
{
// 构造
public:
	CfencioneDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FENCIONE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
private:
	//CSegment segment;

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedpositive();
	CString inputString;
	CString outputString;
	CEdit inputEdit;
	CEdit outputEdit;
	afx_msg void OnBnClickednegative();
	afx_msg void OnBnClickeddouble();
	CStatic resultDetail;
	CstatisticFenciDialog dialog;
	bool isDialogShow;

private:
	CSegment *pSeg;
public:
	afx_msg void OnBnClickedloaddict();
	afx_msg void Onstatistic();
	afx_msg void OnUpdatestatistic(CCmdUI *pCmdUI);
};
