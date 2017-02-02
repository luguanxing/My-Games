
// MazeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Maze.h"
#include "MazeDlg.h"
#include "afxdialogex.h"
#define WM_UPDATEDATA WM_USER+1

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


// CMazeDlg 对话框




CMazeDlg::CMazeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMazeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMazeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIME, cs_timectrl);
	DDX_Control(pDX, IDC_STATIC_HINT, cs_hintctrl);
}

BEGIN_MESSAGE_MAP(CMazeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
//	ON_STN_CLICKED(IDC_STATIC1, &CMazeDlg::OnStnClickedStatic1)
ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


// CMazeDlg 消息处理程序


#define MY_TIMER 1234
CStatic *pcs_timectrl;
CStatic *pcs_hintctrl;
VOID CALLBACK showtime(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime) {		time_t t;
		time(&t);
		tm *timeinfo=localtime(&t);		WCHAR wtime[500];		swprintf(wtime, L"%02d/%02d/%02d %02d:%02d:%02d\n",timeinfo->tm_year+1900,timeinfo->tm_mon,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);		pcs_timectrl->SetWindowText(wtime);		AfxGetApp()->m_pMainWnd->SendMessage(WM_UPDATEDATA,0,0);}
BOOL CMazeDlg::OnInitDialog()
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
	pcs_hintctrl = &cs_hintctrl;
	pcs_timectrl = &cs_timectrl;
	::SetTimer(NULL, MY_TIMER, 1000, showtime);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMazeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMazeDlg::OnPaint()
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
HCURSOR CMazeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LRESULT CMazeDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (message == WM_UPDATEDATA) {
		this->UpdateData(false);
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}

bool isstart = false;
bool isfail = true;
bool ischeat = false;

void start() {
	if (!isstart) {	//开始游戏
		pcs_hintctrl->SetWindowText(L"游戏开始(๑•̀ㅂ•́)و✧");
		TRACE("开始了\n");
		AfxGetApp()->m_pMainWnd->SendMessage(WM_UPDATEDATA,0,0);
		isstart = true;
		isfail = false;
		ischeat = false;
	}
}

void fail() {
	if (!isfail) {	//游戏结束
		pcs_hintctrl->SetWindowText(L"游戏失败╮(๑•́ ₃•̀๑)╭");
		TRACE("失败了\n");
		AfxGetApp()->m_pMainWnd->SendMessage(WM_UPDATEDATA,0,0);
		isfail = true;
		isstart = false;
		ischeat = false;
	}
}

void cheat() {
	if (!ischeat && isstart) {
		ischeat = true;
		TRACE("离开了\n");
	}
}

void checkwin() {
	if (isstart && !isfail) {
		if (ischeat) {
			pcs_hintctrl->SetWindowText(L"不要作弊٩(๑´0`๑)۶");
			TRACE("作弊了\n");
		} else {
			pcs_hintctrl->SetWindowText(L"游戏胜利(●'◡'●)ﾉ♥");
			TRACE("胜利了\n");
		}
		AfxGetApp()->m_pMainWnd->SendMessage(WM_UPDATEDATA,0,0);
		isfail = true;
		isstart = false;
		ischeat = false;
	}
}

BOOL CMazeDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pos;   
	GetCursorPos(&pos);  //获取当前鼠标位置   

	CRect rc;
	CWnd *cwndstart=GetDlgItem(IDC_STATIC_S);
	CWnd *cwndend=GetDlgItem(IDC_STATIC_E);
	cwndstart->GetWindowRect(&rc);
	if (rc.PtInRect(pos)) 
	{   
		SetCursor(LoadCursor(NULL, IDC_HAND));
		start();
		return true;
	}   
	cwndend->GetWindowRect(&rc);
	if (rc.PtInRect(pos)) 
	{   
		SetCursor(LoadCursor(NULL, IDC_HAND));
		checkwin();
		return true;
	}  



	CWnd *cwnds[10] = {0};
	cwnds[0]=GetDlgItem(IDC_STATIC1);
	cwnds[1]=GetDlgItem(IDC_STATIC2);
	cwnds[2]=GetDlgItem(IDC_STATIC3);
	cwnds[3]=GetDlgItem(IDC_STATIC4);
	cwnds[4]=GetDlgItem(IDC_STATIC5);

	cwnds[5]=GetDlgItem(IDC_STATIC6);
	cwnds[6]=GetDlgItem(IDC_STATIC7);
	cwnds[7]=GetDlgItem(IDC_STATIC8);
	cwnds[8]=GetDlgItem(IDC_STATIC9);
	cwnds[9]=GetDlgItem(IDC_STATIC10);

	for (int i=0; i<5; i++) {	//鼠标碰墙  
		cwnds[i]->GetWindowRect(&rc);
		if (rc.PtInRect(pos)) 
		{   
			SetCursor(LoadCursor(NULL, IDC_CROSS));
			fail();
			return true;
		}   
	}
	
	for (int i=5; i<10; i++) {	//鼠标在路上  
		cwnds[i]->GetWindowRect(&rc);
		if (rc.PtInRect(pos))
		{   
			return true;
		}   
	}

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CMazeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pos;   
	GetCursorPos(&pos);  //获取当前鼠标位置   

	TRACKMOUSEEVENT TrackMouseEvent;  //检测鼠标离开
	TrackMouseEvent.cbSize = sizeof(TrackMouseEvent);
	TrackMouseEvent.dwFlags = TME_LEAVE;
	TrackMouseEvent.hwndTrack = GetSafeHwnd();
	TrackMouseEvent.dwHoverTime = HOVER_DEFAULT;
	_TrackMouseEvent(&TrackMouseEvent);

	CDialogEx::OnMouseMove(nFlags, point);
}




void CMazeDlg::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	cheat();
	CDialogEx::OnMouseLeave();
}
