// CstatisticFenciDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "fencione.h"
#include "CstatisticFenciDialog.h"
#include "afxdialogex.h"
#include "fencioneDlg.h"


// CstatisticFenciDialog �Ի���

IMPLEMENT_DYNAMIC(CstatisticFenciDialog, CDialogEx)

CstatisticFenciDialog::CstatisticFenciDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CstatisticFenciDialog::IDD, pParent)
{

}

CstatisticFenciDialog::~CstatisticFenciDialog()
{
}

void CstatisticFenciDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_input_edit, inputEdit);
	DDX_Control(pDX, IDC_output_edit, outputEdit);
	DDX_Control(pDX, IDC_result, resultText);
}


BEGIN_MESSAGE_MAP(CstatisticFenciDialog, CDialogEx)
	/*ON_COMMAND(ID_machine, &CstatisticFenciDialog::Onmachine)*/
	ON_BN_CLICKED(IDOK, &CstatisticFenciDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_loadDict, &CstatisticFenciDialog::OnBnClickedloaddict)
	ON_BN_CLICKED(IDC_statistic, &CstatisticFenciDialog::OnBnClickedstatistic)
END_MESSAGE_MAP()


// CstatisticFenciDialog ��Ϣ�������

BOOL CstatisticFenciDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pSeg = new CstatisticSeg();
	isLoadedDict = false;
	pSeg->loadDict(_T("../dict/WordFrequency.txt"));
	isLoadedDict = true;

	return TRUE;
}

void CstatisticFenciDialog::Onmachine()
{
	// TODO: �ڴ���������������
	this->ShowWindow(SW_HIDE);
	CfencioneDlg dialog;
	dialog.DoModal();
	this->ShowWindow(SW_SHOW);
	this->EndDialog(0);
}


void CstatisticFenciDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(false);
	//CDialogEx::OnOK();
	this->SendMessage(WM_CLOSE);
}


void CstatisticFenciDialog::OnBnClickedloaddict()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fileDialog(TRUE);
	fileDialog.m_ofn.lpstrInitialDir = _T("E:\\WordFrequency.txt");
	if (fileDialog.DoModal() == IDOK)
	{
		CString filePathName = fileDialog.GetPathName();
		pSeg->loadDict(filePathName);
		CString str;
		str.Format(_T("�ֵ��Ѿ�������ɣ����Կ�ʼ�ִ�!/n ��ʱ��%d ms"),(pSeg->dictTime));
		AfxMessageBox(str,MB_YESNO|MB_ICONQUESTION);
		isLoadedDict = true;
	}
}


void CstatisticFenciDialog::OnBnClickedstatistic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//inputEdit.SetWindowTextW(_T("��ϳɷ���ʱ"));
	if (isLoadedDict == false)
	{
		CString str;
		str.Format(_T("���ڼ��شʵ䣬���Ժ�"),(pSeg->dictTime));
		AfxMessageBox(str,MB_YESNO|MB_ICONQUESTION);
		return;
	}
	CString inputStr = _T("");
	inputEdit.GetWindowTextW(inputStr);
	pSeg->init();
	CString outputStr = pSeg->doCut(inputStr);
	outputEdit.SetWindowTextW(outputStr);

	CString detail = _T("");
	detail.Format(_T("��ʱ��%d"), (pSeg->cutTime));
	resultText.SetWindowTextW(detail);
}
