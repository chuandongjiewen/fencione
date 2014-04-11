// HMMSeg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "fencione.h"
#include "HMMSegDlg.h"
#include "afxdialogex.h"


// CHMMSeg �Ի���

IMPLEMENT_DYNAMIC(CHMMSegDlg, CDialogEx)

CHMMSegDlg::CHMMSegDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHMMSegDlg::IDD, pParent)
{

}

CHMMSegDlg::~CHMMSegDlg()
{
}

void CHMMSegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_output, outputEdit);
	DDX_Control(pDX, IDC_input, inputEdit);
}


BEGIN_MESSAGE_MAP(CHMMSegDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PROCESS, &CHMMSegDlg::OnBnClickedProcess)
	ON_BN_CLICKED(IDOK, &CHMMSegDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHMMSeg ��Ϣ�������

BOOL CHMMSegDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	seg = new CHMMSeg();
	return TRUE;
}

void CHMMSegDlg::OnBnClickedProcess()
{
	seg->processTransition(_T("../dict/199801.txt"));
	seg->calTransition(10, 0.5);
	seg->writeTransition(_T("../dict/transition.txt"));

	seg->processEmission(_T("../dict/199801.txt"));
	seg->calEmission(10,0.5);
	seg->writeEmission(_T("../dict/emission.txt"));
	
}


void CHMMSegDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//delete seg;
	CDialogEx::OnOK();
}
