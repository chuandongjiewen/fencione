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
	DDX_Control(pDX, IDC_EDIT_M, est_m_edit);
	DDX_Control(pDX, IDC_EDIT_P, est_p_edit);
	DDX_Control(pDX, IDC_STATIC_DETAIL, detail_Static);
}


BEGIN_MESSAGE_MAP(CHMMSegDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CHMMSegDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BEGEIN, &CHMMSegDlg::OnBnClickedBegein)
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

	est_m_edit.SetWindowTextW(_T("10"));
	est_p_edit.SetWindowTextW(_T("0.000001"));
	return TRUE;
}



void CHMMSegDlg::OnBnClickedBegein()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CString mStr;
	est_m_edit.GetWindowTextW(mStr);

	CString pStr;
	est_p_edit.GetWindowTextW(pStr);

	double m = _ttoi(mStr);
	double p = _tstof(pStr);

	if (m <=0)
	{
		AfxMessageBox(_T("m��ֵ����Ϊ����0��С��"),MB_YESNO|MB_ICONQUESTION);
		return;
	}

	if (p<=0 || p > 1)
	{
		AfxMessageBox(_T("p��ֵ����Ϊ���ڵ���0��С��1��С��"),MB_YESNO|MB_ICONQUESTION);
		return;
	}
	int beginTime = GetTickCount();

	CString sourceStr;
	inputEdit.GetWindowTextW(sourceStr);
	seg->init();
	CString tmpStr = seg->doCut(sourceStr);

	vector<CString> wordsVector = seg->resultVect;

	
	if (wordsVector.size() == 0)
	{
		AfxMessageBox(_T("��������ȷ�ľ���"),MB_YESNO|MB_ICONQUESTION);
		return;
	}
	
	hmm->setEstimate(m,p);
	hmm->setWords(wordsVector);
	hmm->calculate();
	CString resultStr = hmm->output();
	outputEdit.SetWindowTextW(resultStr);

	int endTime = GetTickCount();

	int time = endTime - beginTime;
	CString detailStr;
	detailStr.Format(_T("�ܹ���ʱ��%d ms"), time);
	detail_Static.SetWindowTextW(detailStr);
}




void CHMMSegDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//delete seg;
	CDialogEx::OnOK();
	this->SendMessage(WM_CLOSE);
}
