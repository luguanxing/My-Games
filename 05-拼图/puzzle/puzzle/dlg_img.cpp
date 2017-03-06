// dlg_img.cpp : 实现文件
//

#include "stdafx.h"
#include "puzzle.h"
#include "dlg_img.h"
#include "afxdialogex.h"


// dlg_img 对话框

IMPLEMENT_DYNAMIC(dlg_img, CDialogEx)

dlg_img::dlg_img(CWnd* pParent /*=NULL*/)
	: CDialogEx(dlg_img::IDD, pParent)
{

}

dlg_img::~dlg_img()
{
}

void dlg_img::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dlg_img, CDialogEx)
END_MESSAGE_MAP()


// dlg_img 消息处理程序
