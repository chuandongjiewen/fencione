#pragma once
#include "afxwin.h"
#include "HMMSeg.h"
#include "resource.h"


// CHMMSeg �Ի���

class CHMMSegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHMMSegDlg)

public:
	CHMMSegDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHMMSegDlg();

// �Ի�������
	enum { IDD = IDD_HMM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CHMMSeg *seg;

public:
	CEdit outputEdit;
	CEdit inputEdit;
	afx_msg void OnBnClickedProcess();
	afx_msg void OnBnClickedOk();
};
