// CstatisticFenciDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "fencione.h"
#include "CstatisticFenciDialog.h"
#include "afxdialogex.h"
#include "fencioneDlg.h"


// CstatisticFenciDialog 对话框

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


// CstatisticFenciDialog 消息处理程序

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
	// TODO: 在此添加命令处理程序代码
	this->ShowWindow(SW_HIDE);
	CfencioneDlg dialog;
	dialog.DoModal();
	this->ShowWindow(SW_SHOW);
	this->EndDialog(0);
}


void CstatisticFenciDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(false);
	//CDialogEx::OnOK();
	this->SendMessage(WM_CLOSE);
}


void CstatisticFenciDialog::OnBnClickedloaddict()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDialog(TRUE);
	fileDialog.m_ofn.lpstrInitialDir = _T("E:\\WordFrequency.txt");
	if (fileDialog.DoModal() == IDOK)
	{
		CString filePathName = fileDialog.GetPathName();
		pSeg->loadDict(filePathName);
		CString str;
		str.Format(_T("字典已经加载完成，可以开始分词!/n 耗时：%d ms"),(pSeg->dictTime));
		AfxMessageBox(str,MB_YESNO|MB_ICONQUESTION);
		isLoadedDict = true;
	}
}


void CstatisticFenciDialog::OnBnClickedstatistic()
{
	// TODO: 在此添加控件通知处理程序代码
	//inputEdit.SetWindowTextW(_T("结合成分子时"));
	if (isLoadedDict == false)
	{
		CString str;
		str.Format(_T("正在加载词典，请稍后"),(pSeg->dictTime));
		AfxMessageBox(str,MB_YESNO|MB_ICONQUESTION);
		return;
	}
	CString inputStr = _T("");
	inputEdit.GetWindowTextW(inputStr);
	pSeg->init();
	CString outputStr = pSeg->doCut(inputStr);
	outputEdit.SetWindowTextW(outputStr);

	CString detail = _T("");
	detail.Format(_T("耗时：%d"), (pSeg->cutTime));
	resultText.SetWindowTextW(detail);
}
