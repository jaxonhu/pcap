
// MFCpacpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCpacp.h"
#include "MFCpacpDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern void Butten1();
extern void Butten2();
extern void Butten3();
extern void Butten4();
extern int Filepath(char str[260], char str1[260]);


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
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCpacpDlg 对话框



CMFCpacpDlg::CMFCpacpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCpacpDlg::IDD, pParent)
	, m_pfile(_T(""))
	, m_path(_T(""))
	, m_jindu(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCpacpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OPEN_EDIT, m_pfile);
	DDX_Text(pDX, IDC_SAVE_EDIT, m_path);
	DDX_Text(pDX, IDC_EDIT1, m_jindu);
	DDV_MaxChars(pDX, m_jindu, 100);
}

BEGIN_MESSAGE_MAP(CMFCpacpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BUTTON, &CMFCpacpDlg::OnBnClickedOpenButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CMFCpacpDlg::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDOK, &CMFCpacpDlg::OnBnClickedOk)
//	ON_EN_CHANGE(IDC_EDIT1, &CMFCpacpDlg::OnEnChangeEdit1)
//ON_EN_CHANGE(IDC_EDIT2, &CMFCpacpDlg::OnEnChangeEdit2)
ON_BN_CLICKED(IDC_WU_BUTTON, &CMFCpacpDlg::OnBnClickedWuButton)
ON_BN_CLICKED(IDC_BUTTON2, &CMFCpacpDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &CMFCpacpDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON4, &CMFCpacpDlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON6, &CMFCpacpDlg::OnBnClickedButton6)
ON_BN_CLICKED(IDC_BUTTON5, &CMFCpacpDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMFCpacpDlg 消息处理程序

BOOL CMFCpacpDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCpacpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCpacpDlg::OnPaint()
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
HCURSOR CMFCpacpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCpacpDlg::OnBnClickedOpenButton()
{
	// TODO:  在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("pcap(*.pcap)|*.pcap|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("pcap"), NULL, 0, szFilter, this);
	CString strFilePath;
	
	// 显示打开文件对话框   
	if (fileDlg.DoModal() == IDOK)
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		m_pfile = strFilePath;
		SetDlgItemText(IDC_OPEN_EDIT, strFilePath);
		//SetDlgItemText(IDC_EDIT2, strFilePath);
		
	}
}


void CMFCpacpDlg::OnBnClickedSaveButton()
{
	CFolderPickerDialog folderDlg(NULL, 0, this, 0);

	if (folderDlg.DoModal() == IDOK)
	{
		m_path = folderDlg.GetFolderPath();
		SetDlgItemText(IDC_SAVE_EDIT, m_path);
	}
	
	
	/*TCHAR szPath[MAX_PATH];     //存放选择的目录路径 
	CString str;
	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = _T("请选择文件夹：");
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框

	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp)
	{
		//str.Format(_T("%s"), szPath);
		//AfxMessageBox(str);
		SHGetPathFromIDList(lp, szPath);
		m_path = szPath;
		SetDlgItemText(IDC_SAVE_EDIT, szPath);
	}
	/*else
		MessageBox(_T("无效的目录，请重新选择"));*/
}


void CMFCpacpDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMFCpacpDlg::OnBnClickedWuButton()
{
	// TODO:  在此添加控件通知处理程序代码
	char p1[260] = "", p2[260] = "";
	int i = 0;
	int len1 = WideCharToMultiByte(CP_ACP, 0, m_pfile, -1, NULL, 0, NULL, NULL);
	int len2 = WideCharToMultiByte(CP_ACP, 0, m_path, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, m_pfile, -1, p1, len1, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, m_path, -1, p2, len2, NULL, NULL);
	
	//SetDlgltemText(IDC_EDIT1, m_jindu, "正在解析文件...");
	m_jindu = "正在解析文件...";
	UpdateData(false);
	UpdateWindow();
	i = Filepath(p1, p2);
	if (i==0)
		MessageBox(_T("打开文件失败"));
	m_jindu = "按钮1正进行中...";
	UpdateData(false);
	UpdateWindow();
	Butten1();
	m_jindu = "按钮1已完成";
	UpdateData(false);
	UpdateWindow();
}





void CMFCpacpDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	m_jindu = "按钮2正进行中...";
	UpdateData(false);
	UpdateWindow();
	Butten2();
	m_jindu = "按钮2已完成";
	UpdateData(false);
	UpdateWindow();
}


void CMFCpacpDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	m_jindu = "按钮3正进行中...";
	UpdateData(false);
	UpdateWindow();
	Butten3();
	m_jindu = "按钮3已完成";
	UpdateData(false);
	UpdateWindow();
}


void CMFCpacpDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	m_jindu = "按钮4正进行中...";
	UpdateData(false);
	UpdateWindow();
	Butten4();
	m_jindu = "按钮4已完成";
	UpdateData(false);
	UpdateWindow();
}




void CMFCpacpDlg::OnBnClickedButton6()
{

	CMFCpacpDlg::OnBnClickedWuButton();
	CMFCpacpDlg::OnBnClickedButton2();
	CMFCpacpDlg::OnBnClickedButton3();
	CMFCpacpDlg::OnBnClickedButton4();
	CMFCpacpDlg::OnBnClickedButton5();
	MessageBox(_T("一键解析成功"));
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCpacpDlg::OnBnClickedButton5()
{
	m_jindu = "按钮5正进行中...";
	UpdateData(false);
	UpdateWindow();
	Butten4();
	m_jindu = "按钮5已完成";
	UpdateData(false);
	UpdateWindow();
	// TODO:  在此添加控件通知处理程序代码
}
