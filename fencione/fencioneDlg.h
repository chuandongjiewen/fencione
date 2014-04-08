
// fencioneDlg.h : ͷ�ļ�
//

#pragma once

#include "Segment.h"
#include "afxwin.h"
#include "CstatisticFenciDialog.h"

// CfencioneDlg �Ի���
class CfencioneDlg : public CDialogEx
{
// ����
public:
	CfencioneDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FENCIONE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
private:
	//CSegment segment;

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
