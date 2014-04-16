// HMMSeg.cpp : 实现文件
//

#include "stdafx.h"
#include "fencione.h"
#include "HMMSegDlg.h"
#include "afxdialogex.h"


// CHMMSeg 对话框

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


// CHMMSeg 消息处理程序

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
	// TODO: 在此添加控件通知处理程序代码

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
	// TODO: 在此添加控件通知处理程序代码
	//delete seg;
	CDialogEx::OnOK();
}

void CHMMSegDlg::OnBnClickedloadDict()
{
	// TODO: 在此添加控件通知处理程序代码
	//seg->loadTransition(_T("../dict/tran.txt"))	;
	
}
