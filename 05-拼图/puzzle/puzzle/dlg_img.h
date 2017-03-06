#pragma once


// dlg_img 对话框

class dlg_img : public CDialogEx
{
	DECLARE_DYNAMIC(dlg_img)

public:
	dlg_img(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~dlg_img();

// 对话框数据
	enum { IDD = IDD_DIALOG_IMG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
