
// puzzleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "puzzle.h"
#include "puzzleDlg.h"
#include "afxdialogex.h"
#include "MyPuzzle.h"
#include "dlg_img.h"

#define MY_TIMER 123

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


// CpuzzleDlg 对话框




CpuzzleDlg::CpuzzleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CpuzzleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpuzzleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICBK, img_bk);
}

BEGIN_MESSAGE_MAP(CpuzzleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CpuzzleDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_DIFF, &CpuzzleDlg::OnBnClickedButtonDiff)
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_START, &CpuzzleDlg::OnBnClickedButtonStart)
	ON_WM_TIMER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


// CpuzzleDlg 消息处理程序
MyPuzzle mp;
BOOL CpuzzleDlg::OnInitDialog()
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
	mp.SetDlg(this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CpuzzleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CpuzzleDlg::OnPaint()
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
HCURSOR CpuzzleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CpuzzleDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}

dlg_img imgdlg;
void CpuzzleDlg::OnBnClickedButtonDiff()
{
	// TODO: 在此添加控件通知处理程序代码
	if (imgdlg.m_hWnd == NULL)
		imgdlg.Create(IDD_DIALOG_IMG, this);
	imgdlg.ShowWindow(SW_SHOW);
}


void CpuzzleDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint   p;
	GetCursorPos(&p);
	ScreenToClient(&p);

	if (16 <= p.y && 25 <= p.x) {
		int y = (p.y - 16)/90;
		int x = (p.x - 25)/90;
		if (0 <= x && x <= 3 && 0 <= y && y <= 3) {
			if (!mp.IsSamePoint(x, y)) {
				mp.EraseFrame();
				::Sleep(20);
				mp.DrawFrame(x,y);
			}
		}
	}

	TRACKMOUSEEVENT TrackMouseEvent;  //检测鼠标离开
	TrackMouseEvent.cbSize = sizeof(TrackMouseEvent);
	TrackMouseEvent.dwFlags = TME_LEAVE;
	TrackMouseEvent.hwndTrack = GetSafeHwnd();
	TrackMouseEvent.dwHoverTime = HOVER_DEFAULT;
	_TrackMouseEvent(&TrackMouseEvent);

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CpuzzleDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pos;   
	GetCursorPos(&pos);  //获取当前鼠标位置   
  
	for (int i = 0; i < 15; i++) {
		CRect rc;
		mp.pics[i]->GetWindowRect(&rc); 
		if (rc.PtInRect(pos)) {   
			SetCursor(LoadCursor(NULL, IDC_HAND)); 
			return TRUE; 
		}   
	}
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CpuzzleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint   p;
	GetCursorPos(&p);
	ScreenToClient(&p);

	if (16 <= p.y && 25 <= p.x ) {
		int y = (p.y - 16)/90;
		int x = (p.x - 25)/90;
		if (0 <= x && x <= 3 && 0 <= y && y <= 3) {
			mp.MovePic(x,y);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
					TRACE("%2d ", mp.puzzles[i][j]);
				TRACE("\n");
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CpuzzleDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	mp.israndom = true;
	SetTimer(MY_TIMER,200,NULL);
}

#define RANDOMTIMES 50
int clicksum = 0;
void CpuzzleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == MY_TIMER) {
		mp.RandomMove();
		clicksum++;
	}
	if (clicksum > RANDOMTIMES) {
		clicksum = 0;
		KillTimer(MY_TIMER);
		mp.israndom = false;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CpuzzleDlg::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	mp.EraseFrame();
	CDialogEx::OnMouseLeave();
}
