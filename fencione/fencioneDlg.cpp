
// fencioneDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "fencione.h"
#include "fencioneDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CfencioneDlg �Ի���




CfencioneDlg::CfencioneDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CfencioneDlg::IDD, pParent)
	, inputString(_T(""))
	, outputString(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfencioneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_input, inputString);
	DDX_Text(pDX, IDC_output, outputString);
	DDX_Control(pDX, IDC_input, inputEdit);
	DDX_Control(pDX, IDC_output, outputEdit);
	DDX_Control(pDX, IDC_detail, resultDetail);
}

BEGIN_MESSAGE_MAP(CfencioneDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_positive, &CfencioneDlg::OnBnClickedpositive)
	ON_BN_CLICKED(IDC_negative, &CfencioneDlg::OnBnClickednegative)
	ON_BN_CLICKED(IDC_double, &CfencioneDlg::OnBnClickeddouble)
	ON_BN_CLICKED(IDC_loadDict, &CfencioneDlg::OnBnClickedloaddict)
	//ON_COMMAND(ID_statistic, &CfencioneDlg::Onstatistic)
	//ON_UPDATE_COMMAND_UI(ID_statistic, &CfencioneDlg::OnUpdatestatistic)
END_MESSAGE_MAP()


// CfencioneDlg ��Ϣ�������

BOOL CfencioneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	pSeg = new CSegment(6);

	//instance = this;
	isDialogShow = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CfencioneDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CfencioneDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CfencioneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



/************************************************************************/
/* �������ƥ��                                                                     */
/************************************************************************/
void CfencioneDlg::OnBnClickedpositive()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	/*CString result = pSeg->doCut(_T("һ����˰�"));*/
	pSeg->init();
	CString str = NULL;
	inputEdit.GetWindowText(str);
	CString result = pSeg->MMPositive(str);
	outputEdit.SetWindowTextW(result);

	CString pDetail = _T("");
	pDetail.Format(_T("����ƥ�� ��������%d, ���ֵ����:%d �ܹ�����:%d ��ʱ��%d ms"), 
		(pSeg->pResult.singleWords.size()),
		(pSeg->pResult.nullWords.size()),
		(pSeg->pResult.sumWords.size()),
		(pSeg->pTime)
		);


	resultDetail.SetWindowTextW(pDetail+"\n");

}

/************************************************************************/
/* �������ƥ��                                                                     */
/************************************************************************/
void CfencioneDlg::OnBnClickednegative()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pSeg->init();
	CString str = NULL;
	inputEdit.GetWindowTextW(str);
	CString result = pSeg->MMNegative(str);
	outputEdit.SetWindowTextW(result);
	
	CString nDetail = _T("");
	nDetail.Format(_T("����ƥ�� ��������%d, ���ֵ����:%d �ܹ�����:%d ��ʱ��%d ms"), 
		(pSeg->nResult.singleWords.size()),
		(pSeg->nResult.nullWords.size()),
		(pSeg->nResult.sumWords.size()),
		(pSeg->nTime)
		);

	resultDetail.SetWindowTextW(nDetail);
}


void CfencioneDlg::OnBnClickeddouble()
{
	pSeg->init();
	CString str = NULL;
	inputEdit.GetWindowTextW(str);
	CString result = pSeg->MMDouble(str);
	outputEdit.SetWindowTextW(result);


	CString pDetail = _T("");
	pDetail.Format(_T("����ƥ�� ��������%d, ���ֵ����:%d �ܹ�����:%d ��ʱ��%d ms"), 
		(pSeg->pResult.singleWords.size()),
		(pSeg->pResult.nullWords.size()),
		(pSeg->pResult.sumWords.size()),
		(pSeg->pTime)
		);

	CString nDetail = _T("");
	nDetail.Format(_T("����ƥ�� ��������%d, ���ֵ����:%d �ܹ�����:%d ��ʱ��%d ms"), 
		(pSeg->nResult.singleWords.size()),
		(pSeg->nResult.nullWords.size()),
		(pSeg->nResult.sumWords.size()),
		(pSeg->nTime)
		);
	resultDetail.SetWindowTextW(pDetail+"\n"+nDetail);

}


void CfencioneDlg::OnBnClickedloaddict()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//pSeg->init(6);

	CFileDialog fileDialog(TRUE);
	fileDialog.m_ofn.lpstrInitialDir = _T("E:\\");
	if (fileDialog.DoModal() == IDOK)
	{
		CString filePathName = fileDialog.GetPathName();
		pSeg->loadDict(filePathName);
		CString str;
		str.Format(_T("�ֵ��Ѿ�������ɣ����Կ�ʼ�ִ�!/n ��ʱ��%d ms"),(pSeg->dictTime));
		AfxMessageBox(str,MB_YESNO|MB_ICONQUESTION);
	}
}


void CfencioneDlg::Onstatistic()
{
	
	//CstatisticFenciDialog dialog;
	//bool visible = dialog.IsWindowVisible();
	//dialog.OnBnClickedOk();
	if (!isDialogShow)
	{
		this->ShowWindow(SW_HIDE);
		isDialogShow = true;
		dialog.DoModal();
		this->ShowWindow(SW_SHOW);
		isDialogShow = false;
	}
	this->EndDialog(0);
	
	
}


void CfencioneDlg::OnUpdatestatistic(CCmdUI *pCmdUI)
{
	/*this->ShowWindow(SW_HIDE);
	CstatisticFenciDialog dialog;
	dialog.DoModal();
	this->ShowWindow(SW_SHOW);*/
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	this->SendMessage(WM_CLOSE);
}
