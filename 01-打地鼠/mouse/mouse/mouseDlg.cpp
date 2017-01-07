
// mouseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mouse.h"
#include "mouseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////全局变量与功能函数////////////////////////
#include <iostream>
#include <time.h>
#define ID_TIMER 3

BOOL *pbuttons_value;
bool isplaying = false;
int mytime = 30;
int myscore = 0;
int currentradio = -1;
CButton *buttons[9];
CmouseDlg *dlg;
CString *pscore, *ptime;

int random() {
	srand((unsigned)time(NULL));
	return rand()%(8-0+1)+0;  //生成[a,b]之间的随机整数的方法：rand()%(b-a+1)+a;
}

void newradio() {
	currentradio = random();
	*pbuttons_value = currentradio;
}

void WINAPI count(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime) {	//每隔1s加一
	if (isplaying) {
		mytime--;
		WCHAR buf[5];
		wsprintf(buf, _T("%d"), mytime);
		*ptime = buf;
		dlg->UpdateData(false);
		if (mytime == 0) {
			dlg->OnBnClickedStart();
		}
	}
}

void check(int n) {
	if (isplaying) {
		if (n == currentradio) {
			myscore++;
			newradio();
		} else {
			myscore--;
		}
		WCHAR buf[5];
		wsprintf(buf, _T("%d"), myscore);
		*pscore = buf;
	}
	dlg->UpdateData(false);
}


/////////////////////////////////////////////////////////////////

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


// CmouseDlg 对话框




CmouseDlg::CmouseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmouseDlg::IDD, pParent)
	, m_buttons_value(FALSE)
	, m_time(_T(""))
	, m_score(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START, m_start);
	DDX_Control(pDX, IDC_RADIO1, m_buttons);
	DDX_Radio(pDX, IDC_RADIO1, m_buttons_value);
	DDX_Text(pDX, IDC_TIME, m_time);
	DDX_Text(pDX, IDC_SCORE, m_score);
}

BEGIN_MESSAGE_MAP(CmouseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CmouseDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_END, &CmouseDlg::OnBnClickedEnd)
	ON_BN_CLICKED(IDC_RADIO1, &CmouseDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CmouseDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CmouseDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CmouseDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CmouseDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CmouseDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CmouseDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CmouseDlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CmouseDlg::OnBnClickedRadio9)
END_MESSAGE_MAP()


// CmouseDlg 消息处理程序

BOOL CmouseDlg::OnInitDialog()
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

	//////////////////////////////////////////////////////////////////////////////////
	// TODO: 在此添加额外的初始化代码
	m_buttons_value = -1;
	pbuttons_value = &m_buttons_value;
	pscore = &m_score;
	ptime = &m_time;
	UpdateData(false);
	dlg = this;
	buttons[0] = (CButton*)GetDlgItem(IDC_RADIO1);
	buttons[1] = (CButton*)GetDlgItem(IDC_RADIO2);
	buttons[2] = (CButton*)GetDlgItem(IDC_RADIO3);
	buttons[3] = (CButton*)GetDlgItem(IDC_RADIO4);
	buttons[4] = (CButton*)GetDlgItem(IDC_RADIO5);
	buttons[5] = (CButton*)GetDlgItem(IDC_RADIO6);
	buttons[6] = (CButton*)GetDlgItem(IDC_RADIO7);
	buttons[7] = (CButton*)GetDlgItem(IDC_RADIO8);
	buttons[8] = (CButton*)GetDlgItem(IDC_RADIO9);
	//////////////////////////////////////////////////////////////////////////////////

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmouseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmouseDlg::OnPaint()
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
HCURSOR CmouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmouseDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!isplaying) {
		mytime = 31;
		myscore = 0;
		m_time = _T("30");
		m_score = _T("0");
		UpdateData(false);
		m_start.SetWindowTextW(_T("结束"));
		newradio();
		::SetTimer(this->m_hWnd, ID_TIMER, 1000, count);
	} else {
		::KillTimer(this->m_hWnd, ID_TIMER);
		currentradio = -1;
		m_buttons_value = -1;
		UpdateData(false);
		m_start.SetWindowTextW(_T("开始"));
		WCHAR buf2[50];
		wsprintf(buf2, _T("你的得分是%d"), myscore);
		::MessageBox(NULL, buf2, _T("游戏结束"), MB_ICONINFORMATION);
	}
	isplaying = !isplaying;
}


void CmouseDlg::OnBnClickedEnd()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CmouseDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(0);
}


void CmouseDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(1);
}


void CmouseDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(2);
}


void CmouseDlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(3);
}


void CmouseDlg::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(4);
}


void CmouseDlg::OnBnClickedRadio6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(5);
}


void CmouseDlg::OnBnClickedRadio7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(6);
}


void CmouseDlg::OnBnClickedRadio8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(7);
}


void CmouseDlg::OnBnClickedRadio9()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(8);
}
