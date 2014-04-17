
// fencione.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "fencione.h"
//#include "fencioneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CfencioneApp

BEGIN_MESSAGE_MAP(CfencioneApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
	ON_COMMAND(ID_HMM, &CfencioneApp::OnHmm)
	ON_COMMAND(ID_statistic, &CfencioneApp::Onstatistic)
	ON_COMMAND(ID_machine, &CfencioneApp::Onmachine)
END_MESSAGE_MAP()


// CfencioneApp ����

CfencioneApp::CfencioneApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CfencioneApp ����

CfencioneApp theApp;


// CfencioneApp ��ʼ��

BOOL CfencioneApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	/*CfencioneDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();*/
	fencioneDlg = new CfencioneDlg();
	m_pMainWnd = fencioneDlg;
	INT_PTR nResponse = fencioneDlg->DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

void CfencioneApp::Onmachine()
{
	// TODO: �ڴ���������������
	if (statisticDlg != NULL) 
	{
		statisticDlg->ShowWindow(SW_HIDE);
	}
	if (hmmSegDlg != NULL)
	{
		hmmSegDlg->ShowWindow(SW_HIDE);
	}
	fencioneDlg->ShowWindow(SW_SHOW);

}

void CfencioneApp::Onstatistic()
{
	// TODO: �ڴ���������������
	if (statisticDlg == NULL)
	{
		statisticDlg = new CstatisticFenciDialog();
		INT_PTR response = statisticDlg->DoModal();
		if (response == IDOK)
		{
			PostQuitMessage(0);
		}
	}else{
		if (hmmSegDlg != NULL)
		{
			hmmSegDlg->ShowWindow(SW_HIDE);
		}
		fencioneDlg->ShowWindow(SW_HIDE);
		statisticDlg->ShowWindow(SW_SHOW);
	}
	
	
}


void CfencioneApp::OnHmm()
{
	// TODO: �ڴ���������������
	if (hmmSegDlg == NULL)
	{
		hmmSegDlg = new CHMMSegDlg();
		INT_PTR response = hmmSegDlg->DoModal();
		if (response == IDOK)
		{
			PostQuitMessage(0);
		}
	}else{
		if (statisticDlg != NULL) 
		{
			statisticDlg->ShowWindow(SW_HIDE);
		}
		fencioneDlg->ShowWindow(SW_HIDE);
		hmmSegDlg->ShowWindow(SW_SHOW);
	}
}





