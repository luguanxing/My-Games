// motaExDlg.h : 头文件
//
#pragma once
#include "MyGame.h"
#include "afxwin.h"

// CmotaExDlg 对话框
class CmotaExDlg : public CDialogEx
{
// 构造
public:
	CmotaExDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MOTAEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	MyGame mygame;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_solider;
	CStatic m_knight;
};
