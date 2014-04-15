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
	ON_BN_CLICKED(IDC_BEGEIN, &CHMMSegDlg::OnBnClickedBegein)
	ON_BN_CLICKED(IDC_lOAD_DICT, &CHMMSegDlg::OnBnClickedloadDict)
END_MESSAGE_MAP()


// CHMMSeg ��Ϣ�������

BOOL CHMMSegDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	seg = new CHmm();
	seg->loadInit(_T("../dict/init.txt"));
	seg->loadEmission(_T("../dict/emission.txt"));
	seg->loadTransition(_T("../dict/tran.txt"))	;

	return TRUE;
}

void CHMMSegDlg::OnBnClickedProcess()
{
	

}



void CHMMSegDlg::OnBnClickedBegein()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//seg->loadInit(_T("../dict/init.txt"));
	
}




void CHMMSegDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//delete seg;
	CDialogEx::OnOK();
}

void CHMMSegDlg::OnBnClickedloadDict()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//seg->loadTransition(_T("../dict/tran.txt"))	;
	seg->init();
	seg->calculate();
}
