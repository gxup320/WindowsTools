#pragma once
#include "DlalogWindowControl.h"
#include "DlalogEditControl.h"

// DialogControl 对话框

class DlalogControl : public CDialogEx
{
	DECLARE_DYNAMIC(DlalogControl)

public:
	DlalogControl(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlalogControl();
	HWND OperateHWND = NULL;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	tag_WINDOW_TYPE_LIST ControlType = { 0 };
	DlalogWindowControl m_ControlCommon;
	DlalogEditControl m_ControlEdit;
	CEdit EditHwnd;
	CTabCtrl TabControl;
	afx_msg void OnEnChangeControlEditHwnd();
	void OnTcnSelchangeTabControlShowTab();
	afx_msg void OnTcnSelchangeTabControl(NMHDR* pNMHDR, LRESULT* pResult);
};
