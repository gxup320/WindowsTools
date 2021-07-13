#pragma once


// DlalogWindowStyle 对话框

class DlalogWindowStyle : public CDialogEx
{
	DECLARE_DYNAMIC(DlalogWindowStyle)

public:
	DlalogWindowStyle(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlalogWindowStyle();
	HWND OperateHWND;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WINDOW_STYLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	tag_WINDOW_TYPE_LIST ControlType;

	afx_msg void OnIdok();
	virtual BOOL OnInitDialog();
	CEdit EditHwnd;
	CStatic StaticWindowHandle;
	CStatic StaticWindowClassName;
	CStatic StaticWindowType;
	CComboBox ComboWindowType;
	CEdit EditClassName;
	afx_msg void OnCbnSelchangeStyleComboWindowType();
	//CListBox ListStyle;
	//CListCtrl ListStyle;
	CCheckListBox ListStyle;
	CCheckListBox ListStyleEx;
	afx_msg void OnEnChangeStyleEditHwnd();
	CEdit EditStyle;
	CEdit EditStyleEx;
	BOOL OnEnChangeStyleEditStyleIng = FALSE;
	BOOL OnEnChangeStyleEditStyleExIng = FALSE;
	afx_msg void OnBnClickedStyleButtonStyleGet();
	afx_msg void OnEnKillfocusStyleEditStyle();
//	afx_msg void OnLbnSelchangeSytleListSytle();
	afx_msg void OnCheckChangeSytleListSytle();
	afx_msg void OnBnClickedStyleButtonStyleSet();
	afx_msg void OnBnClickedStyleButtonStyleExGet();
	afx_msg void OnEnKillfocusStyleEditStyleEx();
	afx_msg void OnCheckChangeSytleListSytleEx();
	afx_msg void OnBnClickedStyleButtonStyleExSet();
	afx_msg void OnEnChangeStyleEditStyle();
	afx_msg void OnEnChangeStyleEditStyleEx();
};
