#pragma once
#include "afxwin.h"
#include "Hmm.h"
#include "CstatisticSeg.h"
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
	CHmm *hmm;
	CstatisticSeg *seg;

public:
	CEdit outputEdit;
	CEdit inputEdit;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBegein();
	// //m���Ƶ�mĬ��Ϊ10
	CEdit est_m_edit;
	// //m���Ƶ�pĬ��Ϊ0.000001
	CEdit est_p_edit;
	CStatic detail_Static;
};
