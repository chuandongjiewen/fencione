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
	hmm = new CHmm();
	hmm->loadInit(_T("../dict/init.txt"));
	hmm->loadEmission(_T("../dict/emission.txt"));
	hmm->loadTransition(_T("../dict/tran.txt"))	;

	seg = new CstatisticSeg();
	seg->loadDict(_T("../dict/WordFrequency.txt"));
	return TRUE;
}

void CHMMSegDlg::OnBnClickedProcess()
{
	

}



void CHMMSegDlg::OnBnClickedBegein()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//seg->loadInit(_T("../dict/init.txt"));
	CString sourceStr;
	inputEdit.GetWindowTextW(sourceStr);
	seg->init();
	CString tmpStr = seg->doCut(sourceStr);

	vector<CString> wordsVector = seg->resultVect;

	
	if (wordsVector.size() == 0)
	{
		return;
	}
	std::reverse(wordsVector.begin(), wordsVector.end());
	hmm->setWords(wordsVector);
	hmm->calculate();
	CString resultStr = hmm->output();
	outputEdit.SetWindowTextW(resultStr);
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
	
}
