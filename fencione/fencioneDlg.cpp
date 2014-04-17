
// fencioneDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "fencione.h"
#include "fencioneDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CfencioneDlg 对话框




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


// CfencioneDlg 消息处理程序

BOOL CfencioneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	pSeg = new CSegment(6);

	//instance = this;
	isDialogShow = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CfencioneDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CfencioneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



/************************************************************************/
/* 最大正向匹配                                                                     */
/************************************************************************/
void CfencioneDlg::OnBnClickedpositive()
{
	// TODO: 在此添加控件通知处理程序代码
	
	/*CString result = pSeg->doCut(_T("一把青菜啊"));*/
	pSeg->init();
	CString str = NULL;
	inputEdit.GetWindowText(str);
	CString result = pSeg->MMPositive(str);
	outputEdit.SetWindowTextW(result);

	CString pDetail = _T("");
	pDetail.Format(_T("正向匹配 单词数：%d, 非字典词数:%d 总共词数:%d 耗时：%d ms"), 
		(pSeg->pResult.singleWords.size()),
		(pSeg->pResult.nullWords.size()),
		(pSeg->pResult.sumWords.size()),
		(pSeg->pTime)
		);


	resultDetail.SetWindowTextW(pDetail+"\n");

}

/************************************************************************/
/* 最大逆向匹配                                                                     */
/************************************************************************/
void CfencioneDlg::OnBnClickednegative()
{
	// TODO: 在此添加控件通知处理程序代码
	pSeg->init();
	CString str = NULL;
	inputEdit.GetWindowTextW(str);
	CString result = pSeg->MMNegative(str);
	outputEdit.SetWindowTextW(result);
	
	CString nDetail = _T("");
	nDetail.Format(_T("逆向匹配 单词数：%d, 非字典词数:%d 总共词数:%d 耗时：%d ms"), 
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
	pDetail.Format(_T("正向匹配 单词数：%d, 非字典词数:%d 总共词数:%d 耗时：%d ms"), 
		(pSeg->pResult.singleWords.size()),
		(pSeg->pResult.nullWords.size()),
		(pSeg->pResult.sumWords.size()),
		(pSeg->pTime)
		);

	CString nDetail = _T("");
	nDetail.Format(_T("逆向匹配 单词数：%d, 非字典词数:%d 总共词数:%d 耗时：%d ms"), 
		(pSeg->nResult.singleWords.size()),
		(pSeg->nResult.nullWords.size()),
		(pSeg->nResult.sumWords.size()),
		(pSeg->nTime)
		);
	resultDetail.SetWindowTextW(pDetail+"\n"+nDetail);

}


void CfencioneDlg::OnBnClickedloaddict()
{
	// TODO: 在此添加控件通知处理程序代码
	//pSeg->init(6);

	CFileDialog fileDialog(TRUE);
	fileDialog.m_ofn.lpstrInitialDir = _T("E:\\");
	if (fileDialog.DoModal() == IDOK)
	{
		CString filePathName = fileDialog.GetPathName();
		pSeg->loadDict(filePathName);
		CString str;
		str.Format(_T("字典已经加载完成，可以开始分词!/n 耗时：%d ms"),(pSeg->dictTime));
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
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	this->SendMessage(WM_CLOSE);
}
